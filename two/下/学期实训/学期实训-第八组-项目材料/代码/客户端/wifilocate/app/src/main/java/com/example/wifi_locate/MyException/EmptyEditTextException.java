package com.example.wifi_locate.MyException;


public class EmptyEditTextException extends Exception {

    public static final int Empty_Username = 0;
    public static final int Empty_Password = 1;
    public static final int Null_EditText = 2;
    public int code;

    public EmptyEditTextException(String message, int code) {
        super(message);
        this.code = code;
    }
}
