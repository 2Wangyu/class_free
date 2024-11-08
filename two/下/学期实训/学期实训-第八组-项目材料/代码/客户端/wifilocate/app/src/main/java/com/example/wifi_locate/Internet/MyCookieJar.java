package com.example.wifi_locate.Internet;

import android.util.Log;

import androidx.annotation.NonNull;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;
import java.net.CookieStore;
import java.nio.charset.StandardCharsets;
import java.util.Collections;
import java.util.List;

import android.content.Context;

import okhttp3.Cookie;
import okhttp3.CookieJar;
import okhttp3.HttpUrl;

public class MyCookieJar implements CookieJar {
    private static final String TAG = "My_CookieJar";

    @Override
    public void saveFromResponse(@NonNull HttpUrl httpUrl, @NonNull List<Cookie> list) {
        Internet_Global.getInstance().setCookies(list);
//        for(Cookie c:list){
//            Log.d(TAG, Cookie_Serializable.Cookie_toString(c));
//        }

    }

    @NonNull
    @Override
    public List<Cookie> loadForRequest(@NonNull HttpUrl httpUrl) {
        List<Cookie> cookies = Internet_Global.getInstance().getCookies();
        if (cookies != null)
            return cookies;
        else return Collections.emptyList();
    }
}
