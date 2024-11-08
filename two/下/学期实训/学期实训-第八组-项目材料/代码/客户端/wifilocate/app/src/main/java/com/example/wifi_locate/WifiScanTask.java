package com.example.wifi_locate;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.os.Bundle;

import com.example.wifi_locate.Internet.MyCookieJar;
import android.util.Pair;
import java.util.ArrayList;
import java.util.List;


import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.IOException;
import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class WifiScanTask implements Runnable {

    private static final String TAG = "BackgroundWifiScanTask";
    public static final String WIFI_SCAN_RESULT = "com.example.wifi_locate.WIFI_SCAN_RESULT";
    public static final String EXTRA_DIRECTION = "com.example.wifi_locate.EXTRA_DIRECTION";
    private static final String EXTRA_KEY_VALUE_LIST = "extra_key_value_list";

    private Context context;
    private WifiManager wifiManager;
    private Handler handler;
    private Handler uiHandler;
    private Runnable wifiScanRunnable;
    private BroadcastReceiver wifiScanReceiver;
    private SharedPreferences sharedPreferences;
    private String  username;

    public WifiScanTask(Context context, Handler uiHandler) {
        this.context = context;
        this.uiHandler = uiHandler;
        wifiManager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        handler = new Handler(Looper.getMainLooper());

        sharedPreferences = context.getSharedPreferences("account", Context.MODE_PRIVATE);


       username = sharedPreferences.getString("username", "defaultUsername");
        Log.e(TAG,"username"+username);

    }

    @Override
    public void run() {
        startPeriodicWifiScan();
    }

    private void startPeriodicWifiScan() {
        wifiScanRunnable = new Runnable() {
            @Override
            public void run() {
                wifiManager.startScan();
                handler.postDelayed(this, 500); //
            }
        };

        // Start the initial scan
        handler.post(wifiScanRunnable);

        // BroadcastReceiver to handle scan results
        wifiScanReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                List<ScanResult> results = wifiManager.getScanResults();
                // Send the results to the backend
                sendResultsToBackend(results);
            }
        };

        // Register the receiver
        context.registerReceiver(wifiScanReceiver, new IntentFilter(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION));
    }

    private void sendResultsToBackend(List<ScanResult> results) {
        try {
            // Convert results to JSON
            JSONArray jsonArray = new JSONArray();
            for (ScanResult result : results) {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("BSSID", result.BSSID);
                jsonObject.put("RSSI", result.level);
                jsonArray.put(jsonObject);
            }
            JSONObject mainObject = new JSONObject();
            mainObject.put("username", username);
            mainObject.put("results", jsonArray);

            MediaType JSON = MediaType.parse("application/json; charset=utf-8");
            RequestBody requestBody = RequestBody.create(mainObject.toString(), JSON);

            OkHttpClient client = new OkHttpClient.Builder().cookieJar(new MyCookieJar()).build();
            Request request = new Request.Builder()
                    .url(MyURL.Root + "/locator")
                    .post(requestBody)
                    .build();

            Log.d(TAG, "Sending request");
            client.newCall(request).enqueue(new Callback() {
                @Override
                public void onFailure(Call call, IOException e) {
                    Log.e(TAG, "Request failed: " + e.getMessage());
                }

                @Override
                public void onResponse(Call call, Response response) throws IOException {
                    if (response.isSuccessful()) {
                        String responseData = response.body().string();
                        // 解析服务器返回的JSON数据
                        try {
                            JSONObject responseJson = new JSONObject(responseData);
                            String status = responseJson.getString("status");
                            if ("success".equals(status)) {



                                String coordinates = responseJson.getString("coordinates");
                                Log.d(TAG, "coordinates: " + coordinates);

                                // 获取 user_positions
                                JSONObject userPositions = responseJson.getJSONObject("user_positions");
                                Log.d(TAG, "user_positions: " + userPositions.toString());

                                // 使用Handler将数据发送到UI线程
                                Message message = uiHandler.obtainMessage();
                                Bundle bundle = new Bundle();
                                bundle.putString("coordinates", coordinates);
                                bundle.putString("user_positions", userPositions.toString());
                                message.setData(bundle);
                                uiHandler.sendMessage(message);

                                // 发送广播
                                Intent intent = new Intent(WIFI_SCAN_RESULT);
                                intent.putExtra(EXTRA_DIRECTION, coordinates);
                                intent.putExtra("user_positions", userPositions.toString());
                                context.sendBroadcast(intent);





                            } else {
                                Log.e(TAG, "Server error1: " + responseJson.getString("message"));
                            }
                        } catch (JSONException e) {
                            Log.e(TAG, "Error parsing JSON: " +  e.getMessage());
                        }
                    } else {
                        Log.e(TAG, "Server error2: " + response.code());
                    }
                }
            });
        } catch (Exception e) {
            Log.e(TAG, "Error: " + e.getMessage());
        }
    }

    public void stopScanTask() {
        // Remove the periodic scan callbacks
        handler.removeCallbacks(wifiScanRunnable);
        // Unregister the receiver
        context.unregisterReceiver(wifiScanReceiver);
    }
}
