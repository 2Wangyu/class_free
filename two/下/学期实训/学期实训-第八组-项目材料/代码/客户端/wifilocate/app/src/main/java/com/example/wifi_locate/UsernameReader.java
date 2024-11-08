package com.example.wifi_locate;
import android.content.SharedPreferences;

public class UsernameReader {

    public String getUsername(SharedPreferences sharedPreferences) {
        return sharedPreferences.getString("username", "defaultUsername");
    }

    public boolean isPremiumUser(SharedPreferences sharedPreferences) {
        return sharedPreferences.getBoolean("isPremiumUser", false);
    }
}
