package com.example.wifi_locate;

import static android.content.Intent.FLAG_ACTIVITY_CLEAR_TASK;
import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.example.wifi_locate.Internet.Internet_Global;
import com.example.wifi_locate.Internet.MyCookieJar;
import com.example.wifi_locate.MyException.EmptyEditTextException;

import java.util.Arrays;
import java.util.Timer;
import java.util.TimerTask;

import okhttp3.Call;
import okhttp3.FormBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class  launch_activity extends AppCompatActivity {

    private Button skip_launch;
    private String TAG = "launch";
    private Intent intent;
    private Boolean isclick;
    private int count;
    private Timer timer;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_launch);

        skip_launch = findViewById(R.id.lunch_button);
        intent = null;
        isclick = false;
        count = 10;
        is_login();
        timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                if (count <= 0 || isclick) {
                    if (intent != null) {
                        startActivity(intent);
                        this.cancel();
                    } else if(count<=0){
                        intent = new Intent(launch_activity.this, LoginActivity.class);
                        startActivity(intent);
                        this.cancel();
                    }
                } else {
                    skip_launch.setText("跳过 " + count);
                }
                count--;
            }
        }, 0, 1000);
    }

    private void is_login() {
        new Thread(() -> {
            Response response = null;
            try {
                Log.d(TAG, "发送请求");
                OkHttpClient okHttpClient = new OkHttpClient.Builder()
                        .cookieJar(new MyCookieJar())
                        .build();
                //2.获取request对象
                Request request = new Request.Builder()
                        .url(Internet_Global.Root + "/is_login_in")
                        .get()
                        .build();
                //3.获取call对象
                Call call = okHttpClient.newCall(request);
                //4.执行网络操作（同步）
                //同步执行网络操作
                 response = call.execute();
                String result = response.body().string();
                Log.d(TAG, "result"+result);
                switch (result) {
                    case "100":
                        intent = new Intent(launch_activity.this, HomePage4Activity.class);
                        intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);

                        break;
                    case "205":
                        intent = new Intent(launch_activity.this, LoginActivity.class);
                        intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);

                        break;
                }
            } catch (Exception e) {
                Log.d(TAG, "网络请求失败" + e.getMessage() + Arrays.toString(e.getStackTrace()));
                Log.e(TAG, "is_login: ", e);
                intent = new Intent(launch_activity.this, LoginActivity.class);
                intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);

                MakeToast("网络请求失败:" + e.getMessage());
            } finally {
                if (response != null) response.close();
                Log.d(TAG, "finish");
            }
        }).start();
    }


    private void MakeToast(String massage) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(getApplicationContext(), massage, Toast.LENGTH_SHORT).show();
            }
        });
    }

    public void launch_skip(View view) {
        skip_launch.setEnabled(false);
        if (intent == null) MakeToast("登陆中...");
        else {
            startActivity(intent);
            timer.cancel();
        }
        isclick = true;
    }
}