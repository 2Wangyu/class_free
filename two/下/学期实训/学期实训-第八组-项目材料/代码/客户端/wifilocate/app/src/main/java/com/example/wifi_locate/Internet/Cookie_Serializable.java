package com.example.wifi_locate.Internet;

import android.util.Log;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import okhttp3.Cookie;

public class Cookie_Serializable {
    private Cookie_Serializable() {
    }
    public static String Cookie_toString(Cookie cookie) {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder
//                .append("Cookie-name:")
                .append(cookie.name()).append(";")
//                .append(";Value:")
                .append(cookie.value()).append(";")
//                .append(";expiresAt:")
                .append(cookie.expiresAt()).append(";")
//                .append(";domain:")
                .append(cookie.domain()).append(";")
//                .append(";path:")
                .append(cookie.path()).append(";")
//                .append(";secure:")
                .append(cookie.secure()).append(";")
//                .append(";httpOnly:")
                .append(cookie.httpOnly()).append(";")
//                .append(";hostOnly:")
                .append(cookie.hostOnly()).append(";")
//                .append(";persistent:")
                .append(cookie.persistent()).append(";");
        String cs=stringBuilder.toString();
        Log.d("Cookie", "Save_Cookie: "+cs);
        return cs;
    }

    public static String Cookie_toString(List<Cookie> list){
        StringBuilder stringBuilder=new StringBuilder();
        for(Cookie cookie:list){
            stringBuilder.append(Cookie_Serializable.Cookie_toString(cookie));
        }
        String cs=stringBuilder.toString();
        Log.d("Cookie", "Save_Cookies: "+cs);
        return cs;
    }

    //private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
//        String name = (String) in.readObject();
//        String value = (String) in.readObject();
//        long expiresAt = in.readLong();
//        String domain = (String) in.readObject();
//        String path = (String) in.readObject();
//        boolean secure = in.readBoolean();
//        boolean httpOnly = in.readBoolean();
//        boolean hostOnly = in.readBoolean();
//        boolean persistent = in.readBoolean();
//        Cookie.Builder builder = new Cookie.Builder();
//        builder = builder.name(name);
//        builder = builder.value(value);
//        builder = builder.expiresAt(expiresAt);
//        builder = hostOnly ? builder.hostOnlyDomain(domain) : builder.domain(domain);
//        builder = builder.path(path);
//        builder = secure ? builder.secure() : builder;
//        builder = httpOnly ? builder.httpOnly() : builder;
//        clientCookies = builder.build();
//    }
    public static List<Cookie> Cookie_prase(String Cookies) {
        Log.d("Cookie", "Load_Cookie: "+Cookies);
        List<Cookie> list = new ArrayList<Cookie>();
        String[] strings = Cookies.split(";");
        if (strings.length < 9) return Collections.emptyList();


        for (int i = 0; i < (strings.length / 9); i++) {
            Cookie.Builder builder = new Cookie.Builder();
            Log.d("Cookie", "Cookie_prase: ");
            builder.name(strings[0 + i * 9])
                    .value(strings[1 + i * 9])
                    .expiresAt(Long.parseLong(strings[2 + i * 9]))
                    .domain(strings[3 + 9 * i])
                    .path(strings[4 + 9 * i]);
            if (Boolean.getBoolean(strings[4 + 9 * i])) builder.secure();
            if (Boolean.getBoolean(strings[4 + 9 * i])) builder.httpOnly();
            list.add(builder.build());
        }
        Log.d("Cookie","Cookie form Cookie_prase"+Cookie_Serializable.Cookie_toString(list));

        return list;
    }

}