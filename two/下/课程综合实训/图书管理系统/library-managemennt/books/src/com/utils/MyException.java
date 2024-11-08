package com.utils;
//自定义异常，用于处理借阅过程中发生的一些异常
//多种情况

public class MyException extends RuntimeException {

	private static final long serialVersionUID = 1L;

	private String message;
	
	
	public MyException() {
		super();
	}

	
	public MyException(String message) {
		super();
		this.message = message;
	}


	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}
	
	
}
