package com.example.wifi_locate.Internet;

import android.util.Log;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Collections;
import java.util.List;

import okhttp3.Cookie;

/**
 * 这个类用于更方便的修改服务器地址
 */
public class Internet_Global {
    public static final Internet_Global internetGlobal = new Internet_Global();

            public static final String Root ="http://119.3.163.32:8080";
//    public static final String Root = "http://192.168.35.68:8080";
    private List<Cookie> cookies;
    private final String TAG = "Internet_Global";

    private Internet_Global() {
        /**
         * read cookies from file
         */
    }

    public static Internet_Global getInstance() {
        return internetGlobal;
    }

    public synchronized void setCookies(List<Cookie> cookies) {
//        this.cookies = cookies;
        FileOutputStream fo = null;
        try {
            File f = new File("data/data/com.example.wifi_locate/Cookies");
            if (!f.exists()) f.createNewFile();
            fo = new FileOutputStream(f);
            fo.write(Cookie_Serializable.Cookie_toString(cookies).getBytes(StandardCharsets.UTF_8));
        } catch (FileNotFoundException e) {
            Log.e(TAG, "saveFromResponse: ", e);
            throw new RuntimeException(e);
        } catch (IOException e) {
            Log.e(TAG, "saveFromResponse: ", e);
            throw new RuntimeException(e);
        } finally {
            try {
                if (fo != null) fo.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    public synchronized void delete_cookie() {
        try {
            File f = new File("data/data/com.example.wifi_locate/Cookies");
            boolean flag = false;
            if (f.exists())
                flag = f.delete();
            if (!flag) throw new Exception("Failed to delete the cookie");
        } catch (Exception e) {
            Log.e(TAG, "delete_cookie: ", e);

        }


    }


    public List<Cookie> getCookies() {
//        return cookies;
        FileInputStream fi = null;
        ByteArrayOutputStream baos = null;
        try {
            File f = new File("data/data/com.example.wifi_locate/Cookies");
            if (!f.exists()) {
                return Collections.emptyList();
            }
            fi = new FileInputStream(f);
            byte[] bytes = new byte[50];
            int len;// 记录每次读取的字节的个数
            baos = new ByteArrayOutputStream();
            while ((len = fi.read(bytes)) != -1) {
                baos.write(bytes, 0, len);
            }
            Log.d(TAG, baos.toString());
            return Cookie_Serializable.Cookie_prase(baos.toString());
        } catch (IOException e) {
            Log.e(TAG, "loadForRequest: ", e);
            throw new RuntimeException(e);
        } finally {
            try {
                if (fi != null) fi.close();
            } catch (IOException e) {
                Log.e(TAG, "loadForRequest: ", e);
                throw new RuntimeException(e);
            }
        }
    }
}

