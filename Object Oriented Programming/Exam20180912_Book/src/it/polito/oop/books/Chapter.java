package it.polito.oop.books;

import java.util.List;

public abstract class Chapter {
	
	/*
	 * ATTRIBUTES
	 */
	private String title;
	private int numPages;
	
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public int getNumPages() {
		return numPages;
	}
	public void setNumPages(int numPages) {
		this.numPages = numPages;
	}
	
	public abstract List<Topic> getTopics();

}
