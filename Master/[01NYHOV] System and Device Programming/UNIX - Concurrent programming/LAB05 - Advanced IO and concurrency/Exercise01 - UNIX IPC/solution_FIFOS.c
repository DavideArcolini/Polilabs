#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>

extern int errno;

#define SHRMEM_SIZE 1024        // size of the shared memory region, in bytes
#define PATHNAME "/tmp"         // pathname used to generate the key of the shared memory
#define PATHFIFO "/tmp/myfifo"  // pathname used to generate the fifo
#define ID 3                    // identifier of the key
#define MAX_LENGTH 10           // max length of the generated text

/**
 * @brief Processes routine, used to communicate between P1 and P2
 * 
 * @param key key value of the shared memory
 * @param fd fifo file to communicate
 * @return 0 on success 
 */
int process_routine(key_t key, int fd, bool do_i_start);

/**
 * @brief Generate a random text at the location pointed by data
 * 
 * @param data pointer to the location of the generated text
 * @return size of the generated text
 */
int generate_text(char *data);

/**
 * @brief Convert to capital and show text in the shared region
 * 
 * @param data pointer to the shared region
 * @param length length of the text in the shared region
 * @return int 0 on success
 */
int showdata(char *data, int length);


/**
 * @brief DRIVER CODE
 * 
 * @param args number of arguments
 * @param argv list of arguments
 * @return 0 on success 
 */
int main (int args, char *argv[]) {

    /* CHECKING USER INPUT */
    if (args != 1) {
        fprintf(stderr, "[USAGE] ./exeA\n");
        exit(EXIT_FAILURE);
    }

    /* RANDOM SEED INITIALIZATION */
    srand(getpid());

    /* KEY GENERATION */
    key_t key = ftok(PATHNAME, ID);
    if (key == -1) {
        fprintf(stderr, "[ERROR] ftok() failed execution\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "key is: %d\n", key);

    /* FIFO GENERATION */
    int ret;
    if ((ret = mkfifo(PATHFIFO, 0666)) == -1) {
        fprintf(stderr, "[ERROR] mkfifo() failed execution: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    /* PROCESSES GENERATION */
    pid_t child = fork();
    if (child < 0) {
        fprintf(stderr, "[ERROR] fork() failed execution\n");
        exit(EXIT_FAILURE);
    } else if (child == 0) {

        /* P2 */
        int fd = open(PATHFIFO, O_RDWR);
        if (fd == -1) {
            fprintf(stderr, "[ERROR] open() failed execution\n");
            exit(EXIT_FAILURE);
        }
        if (process_routine(key, fd, true) != 0) {
            fprintf(stderr, "[ERROR] process_routine() failed execution\n");
            exit(EXIT_FAILURE);
        }
        close(fd);

    } else {

        /* P1 */
        int fd = open(PATHFIFO, O_RDWR);
        if (fd == -1) {
            fprintf(stderr, "[ERROR] open() failed execution\n");
            exit(EXIT_FAILURE);
        }
        if (process_routine(key, fd, false) != 0) {
            fprintf(stderr, "[ERROR] process_routine() failed execution\n");
            exit(EXIT_FAILURE);
        }

        /* CLOSING AND REMOVING FIFO */
        close(fd);
        char command[20];
        sprintf(command, "rm -rf %s", PATHFIFO);
        system(command);
    }

    
    /* PROGRAM TERMINATED SUCCESSFULLY */
    exit(EXIT_SUCCESS);
}

int process_routine(key_t key, int fd, bool do_i_start) {

    /* CREATING THE SEGMENT OF SHARED MEMORY */
    int shmid;
    if ((shmid = shmget(key, SHRMEM_SIZE, 0644 | IPC_CREAT)) == -1) {
        fprintf(stderr, "[ERROR] shmget() failed execution\n");
        return -1;
    }
    
    /* ATTACH THE PROCESS TO THAT SEGMENT */
    char *data = shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        fprintf(stderr, "[ERROR] shmat() failed execution\n");
        return -1;
    }

    /* COMMUNICATION ROUTINE */
    bool running = true;
    if (do_i_start) {

        /* P2 */
        while (running) {

            /* GENERATING TEXT */
            int length = generate_text(data);
            fprintf(stdout, "[!] writing %d bytes...\n", length);
            if (write(fd, &length, sizeof(int)) != sizeof(length)) {
                fprintf(stderr, "[ERROR] write() failed execution\n");
                return -1;
            }
            if (length == 0) {
                fprintf(stdout, "[!] time to stop...\n");
                break;
            }

            /* RECEIVING TEXT */
            if (read(fd, &length, sizeof(int)) == -1) {
                fprintf(stderr, "[ERROR] read() failed execution\n");
                return -1;
            }
            fprintf(stdout, "[!] reading %d bytes...\n", length);
            if (length != 0) {
                if (showdata(data, length) != 0) {
                    fprintf(stderr, "[ERROR] showdata() failed execution\n");
                    return -1;
                }
            } else {
                running = false;
            }

        }
    } else {

        /* P1 */
        while (running) {
            
            /* RECEIVING TEXT */
            int length;
            if (read(fd, &length, sizeof(int)) == -1) {
                fprintf(stderr, "[ERROR] read() failed execution\n");
                return -1;
            }
            fprintf(stdout, "[!] reading %d bytes...\n", length);
            if (length != 0) {
                if (showdata(data, length) != 0) {
                    fprintf(stderr, "[ERROR] showdata() failed execution\n");
                    return -1;
                }
            } else {
                break;
            }

            /* GENERATING TEXT */
            length = generate_text(data);
            fprintf(stdout, "[!] writing %d bytes...\n", length);
            if (write(fd, &length, sizeof(int)) != sizeof(length)) {
                fprintf(stderr, "[ERROR] write() failed execution\n");
                return -1;
            }
            if (length == 0) {
                fprintf(stdout, "[!] time to stop...\n");
                running = false;
            }
        }
    }
    

    /* DETACHING PROCESS FROM THE SEGMENT*/    
    if (shmdt(data) == -1) {
        fprintf(stderr, "[ERROR] shmdt() failed execution\n");
        return -1;
    }
    
    /* TASK COMPLETED SUCESSFULLY */
    return 0;
}

int generate_text(char *data) {

    /* GENERATE LENGTH OF THE TEXT */
    int length = rand() % MAX_LENGTH;
    
    fprintf(stdout, "[!] Generated text is: ");
    for (int i = 0; i < length; i++) {
        int val = rand() % 28;
        if (val == 26) {
            data[i] = (char) (' ');
        } else {
            data[i] = (val == 27) ? (char)('\n') : (char)('a'+val);
        }  
        fprintf(stdout, "%c", data[i]);
    }
    fprintf(stdout, "\n");

    /* NO MORE TEXT TO WRITE */
    return length; 
}

int showdata(char *data, int length) {
    for (int i = 0; i < length; i++) {
        if (data[i] >= 'a' && data[i] <= 'z') {
            fprintf(stdout, "%c", ((char) (data[i]+('A'-'a'))));
        } else {
            fprintf (stdout, "%c", data[i]);
        }
    }
    fprintf(stdout, "\n");

    return 0;
}