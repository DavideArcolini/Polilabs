/**
 * @file solution.c
 * @author Davide Arcolini (davide.arcolini@studenti.polito.it)
 * @brief First solution of the exercise. Implemented as a sequential algorithm.
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

/**
 * @brief Enable random generation of data structure (zero identifies hard-coded data structure
 *        just for the purpose of checking results).
 */
#define OPT_RANDOM 1

/*
 *  + --------------- +
 *  |   DATA STRUCT   |
 *  + --------------- +
*/

/**
 * @brief Data structure used as thread's routine function argument
 * 
 */
typedef struct thread_struct_s {
    float *array1;
    float *array2;
    int size;
    float res;
    bool is_valid;
} thread_struct_t;

/*
 *  + ------------- +
 *  |   FUNCTIONS   |
 *  + ------------- +
*/

/**
 * @brief Create an array of size N and fill it with random values
 * 
 * @param N size of the array
 * @return float* the array
 */
float *array_init(int N) {

    /* ALLOCATING SOME SPACE */
    float *result = (float *) malloc(N * sizeof(float));
    if (result == NULL) {
        fprintf(stderr, "[ERROR] malloc() failed execution\n");
        return NULL;
    }

    /* RANDOM INITIALIZATON */
    for (int i = 0; i < N; i++) {
        result[i] = ((float) rand() / (float) RAND_MAX) - 0.5;
    }

    /* TASK COMPLETED SUCCESSFULLY */
    return result;
}

/**
 * @brief Create a square matrix of size N and fill it with random values
 * 
 * @param N size of the matrix
 * @return float** the matrix
 */
float **mat_init(int N) {

    /* ALLOCATING SOME SPACE */
    float **result = (float **) malloc(N * sizeof(float*));
    if (result == NULL) {
        fprintf(stderr, "[ERROR] malloc() failed execution\n");
        return NULL;
    }
    for (int i = 0; i < N; i++) {
        result[i] = (float *) malloc(N * sizeof(float));
        if (result[i] == NULL) {
            fprintf(stderr, "[ERROR] malloc() failed execution\n");
        return NULL;
        }
    }

    /* RANDOM INITIALIZATON */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = ((float) rand() / (float) RAND_MAX) - 0.5;
        }
    }


    /* TASK COMPLETED SUCCESSFULLY */
    return result;
}


/**
 * @brief Perform the multiplication between two arrays of size size
 * 
 * @param array1 first array
 * @param array2 second array
 * @param size size of the two arrays
 * @param retval result of the multiplication
 * @return zero on success, any other value on failure
 */
int array_mul(float *array1, float *array2, int size, float *retval) {
    
    float res = 0;

    /* SOME ASSERTIONS */
    if (array1 == NULL || array2 == NULL || retval == NULL) {
        fprintf(stderr, "[ERROR] invalid arguments for array_mul()\n");
        return -1;
    } else if (size <= 0) {
        fprintf(stderr, "[ERROR] invalid arguments for array_mul()\n");
        return -1;
    }

    /* PERFORMING MULTIPLICATION */
    for (int i = 0; i < size; i++) {
        res += array1[i] * array2[i];
    }

    /* TASK COMPLETED SUCCESSFULLY */
    *retval = res;
    return 0;
}

/**
 * @brief Thread's function routine
 * 
 * @param data the data structure passed as argument
 * @return void* 
 */
static void* routine (void *data) {

    /* CASTING INPUT DATA */
    thread_struct_t *thread_DATA = (thread_struct_t *) data;  

    /* PERFORMING MULTIPLICATION */
    int err = array_mul(thread_DATA->array1, thread_DATA->array2, thread_DATA->size, &thread_DATA->res);
    if (err) {
        fprintf(stderr, "[ERROR] array_mul() failed execution\n");
        thread_DATA->is_valid = false;
    }

    /* THREAD'S ROUTINE ENDS CORRECTLY */
    thread_DATA->is_valid = true;
    pthread_exit((void *) EXIT_SUCCESS);

}

/**
 * @brief Driver code to solve the exercise
 * 
 * @param N size of the arrays and matrices
 * @return zero on success
 */
int solver(int N) {

    /* SOME ASSERTIONS */
    if (N <= 0) {
        fprintf(stderr, "[ERROR] non-positive size N\n");
        return -1;
    }

#if OPT_RANDOM

    /* INITIALIZATION OF THE DATA STRUCTURE */
    float *v1 = array_init(N);
    if (v1 == NULL) {
        fprintf(stderr, "[ERROR] array_init() failed execution\n");
        return -1;
    }
    float *v2 = array_init(N);
    if (v2 == NULL) {
        fprintf(stderr, "[ERROR] array_init() failed execution\n");
        return -1;
    }
    float **mat = mat_init(N);
    if (mat == NULL) {
        fprintf(stderr, "[ERROR] mat_init() failed execution\n");
        return -1;
    }

#else

    /* STATIC INIT JUST FOR CHECKING */
    float v1[] = {-0.0613, -0.1184, 0.2655, 0.2952, -0.3131};
    float v2[] = {-0.3235, 0.1948, -0.1829, 0.4502, -0.4656};
    float mat[5][5] = {
        {-0.3424, -0.3581, 0.1557, 0.2577, 0.2060},	
        {0.4706, -0.0782, -0.4643, 0.2431, -0.4682},
        {0.4572, 0.4157, 0.3491, 0.1078, -0.2231},
        {-0.0146, 0.2922, 0.4340, -0.1555, -0.4029},
        {0.3003, 0.4595, 0.1787, -0.3288, -0.4656}
    };

#endif

    /* ALLOCATING THREADS INFORMATION */
    pthread_t *threads_ID = (pthread_t *) malloc(N * sizeof(pthread_t));
    thread_struct_t *threads_DATA = (thread_struct_t *) malloc(N * sizeof(thread_struct_t));
    if (threads_ID == NULL || threads_DATA == NULL) {
        fprintf(stderr, "[ERROR] malloc() failed execution\n");
        return -1;
    }
    
    /* GENERATING THE THREADS */
    for (int id = 0; id < N; id++) {

        /* INITIALIZING THREADS_DATA */
        threads_DATA[id].size = N;
        threads_DATA[id].array1 = v1;
        threads_DATA[id].array2 = (float *) malloc(N * sizeof(float));
        if (threads_DATA[id].array2 == NULL) {
            fprintf(stderr, "[ERROR] malloc() failed execution\n");
            return -1;
        }
        for (int k = 0; k < N; k++) {
            threads_DATA[id].array2[k] = mat[k][id];
        }

        /* THREAD CRAATION */
        if (pthread_create(&threads_ID[id], NULL, routine, (void *) &threads_DATA[id]) != 0) {
            fprintf(stderr, "[ERROR] pthread_create() failed execution\n");
            return -1;
        }    
    }

    /* STORING RESULT */
    float *tmp = (float *) malloc(N * sizeof(float));
    if (tmp == NULL) {
        fprintf(stderr, "[ERROR] malloc() failed execution\n");
        return -1;
    }

    /* JOINING THREADS */
    int exit_status;
    for (int id = 0; id < N; id++) {
        if (pthread_join(threads_ID[id], (void *) &exit_status) != 0) {
            fprintf(stderr, "[ERROR] pthread_join() failed execution\n");
            return -1;
        }

        /* CHECKING EXITING STATUS */
        if (exit_status == EXIT_FAILURE) {
            fprintf(stderr, "[ERROR] thread %d ends with EXIT_FAILURE %d\n", id, exit_status);
            return -1;
        } else {
            tmp[id] = threads_DATA[id].res;
        }
    }
    
    /* FINAL RESULT */
    float res;
    int err = array_mul(tmp, v2, N, &res);
    if (err) {
        fprintf(stderr, "[ERROR] array_mul() failed execution\n");
        return -1;
    }
    fprintf(stdout, "[!] result is: %f\n", res);
    
    /* TASK COMPLETED SUCCESSFULLY */
    return 0;
}

/**
 * @brief MAIN
 * 
 * @param args number of arguments
 * @param argv list of arguments
 * @return zero on success
 */
int main(int args, char *argv[]) {

    /* CHECKING ARGUMENTS */
    if (args != 2) {
        fprintf(stderr, "[USAGE] ./exe03 N\n");
        exit(EXIT_FAILURE);
    }

    /* CONVERTING ARGUMENTS TO INTEGER */
    int N = atoi(argv[1]);

    /* TIME MANAGEMENT */
    srand(getpid());
    clock_t t = clock();

    /* DRIVER CODE */
    if (solver(N) != 0) {
        fprintf(stderr, "[DEBUG] solver() failed execution\n");
        exit(EXIT_FAILURE);
    }
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    fprintf(stdout, "The program took %f seconds to execute\n", time_taken);

    /* TASK COMPLETED SUCCESSFULLY */
    fprintf(stdout, "[!] Done!\n");
    exit(EXIT_SUCCESS);
}