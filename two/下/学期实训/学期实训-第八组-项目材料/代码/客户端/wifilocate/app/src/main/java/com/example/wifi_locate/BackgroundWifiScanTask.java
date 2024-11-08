package com.example.wifi_locate;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.IOException;
import java.util.List;
import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import android.os.Looper;
import android.os.Message;

public class BackgroundWifiScanTask implements Runnable {

    private static final String TAG = "BackgroundWifiScanTask";
    public static final String WIFI_SCAN_RESULT = "com.example.wifi_locate.WIFI_SCAN_RESULT";
    public static final String EXTRA_DIRECTION = "com.example.wifi_locate.EXTRA_DIRECTION";

    private Context context;
    private WifiManager wifiManager;
    private Handler handler;
    private Handler uiHandler;
    private Runnable wifiScanRunnable;
    private BroadcastReceiver wifiScanReceiver;

    public BackgroundWifiScanTask(Context context, Handler uiHandler) {
        this.context = context;
        this.uiHandler = uiHandler;
        wifiManager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        handler = new Handler(Looper.getMainLooper());
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
                handler.postDelayed(this, 3000); // Set delay to 3 seconds
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

            MediaType JSON = MediaType.parse("application/json; charset=utf-8");
            RequestBody requestBody = RequestBody.create(jsonArray.toString(), JSON);

            OkHttpClient client = new OkHttpClient();
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

                                // 使用Handler将数据发送到UI线程
                                Message message = uiHandler.obtainMessage();
                                message.obj = coordinates;
                                uiHandler.sendMessage(message);

                                // 发送广播
                                Intent intent = new Intent(WIFI_SCAN_RESULT);
                                intent.putExtra(EXTRA_DIRECTION, coordinates);
                                context.sendBroadcast(intent);
                            } else {
                                Log.e(TAG, "Server error1: " + responseJson.getString("message"));
                            }
                        } catch (JSONException e) {
                            Log.e(TAG, "Error parsing JSON: " +  e.getMessage());
                        }
                    } else {
                        Log.d(TAG, "Server error222: " + response.code());
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
