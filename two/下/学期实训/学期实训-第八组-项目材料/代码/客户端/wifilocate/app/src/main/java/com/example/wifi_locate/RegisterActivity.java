package com.example.wifi_locate;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.example.wifi_locate.Internet.Internet_Global;
import com.example.wifi_locate.MyException.EmptyEditTextException;

import okhttp3.Call;
import okhttp3.FormBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class RegisterActivity extends AppCompatActivity {

    private EditText et_username;
    private EditText et_password;
    private static final String TAG = "Register";
//    private SharedPreferences sharedPreferences;


    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_register);

        //获取对象
//        sharedPreferences=getSharedPreferences("user",MODE_PRIVATE);


        //初始化控件
        et_username=findViewById(R.id.et_username);
        et_password=findViewById(R.id.et_password);


        //点击事件
        findViewById(R.id.toolbar).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //点击返回登录界面,不要做跳转登录页面
                finish();
            }
        });
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        //点击注册
        findViewById(R.id.register).setOnClickListener((View view)-> {
                register();

        });

    }

    private void register(){
        new Thread(new Runnable() {
            @Override
            public void run() {
                Response response = null;
                try {
                    if (et_username == null || et_password == null)
                        throw new EmptyEditTextException("EditText为null", EmptyEditTextException.Null_EditText);
                    String username=et_username.getText().toString();
                    String password=et_password.getText().toString();
                    if (username.isEmpty())
                        throw new EmptyEditTextException("空的用户名框", EmptyEditTextException.Empty_Username);
                    if (password.isEmpty())
                        throw new EmptyEditTextException("空的密码框", EmptyEditTextException.Empty_Password);

                    Log.d(TAG, "发送请求");
                    OkHttpClient okHttpClient = new OkHttpClient();
                    //2.获取request对象
                    RequestBody requestBody = new FormBody.Builder().add("username", username).add("password", password).build();
                    Request request = new Request.Builder()
                            .url(Internet_Global.Root + "/login/register")
                            .post(requestBody)
                            .build();

                    //3.获取call对象
                    Call call = okHttpClient.newCall(request);
                    //4.执行网络操作（同步）
                    //同步执行网络操作
                    response = call.execute();
                    String result = response.body().string();
                    Log.d(TAG, result);

                    switch (result) {
                        case "101":
//                            注册成功
                            MakeToast("注册成功");
                            Intent resultIntent=new Intent();
                            resultIntent.putExtra("username",username);
                            resultIntent.putExtra("password",password);
                            setResult(RESULT_OK,resultIntent);
                            finish();
                            break;
                        case "1062":
//                            账号不存在
                            MakeToast("用户名重复");
                            break;
                    }
                } catch (EmptyEditTextException e) {
                    if (e.code == EmptyEditTextException.Null_EditText) {
                        //输入框是空值
                        Log.d(TAG, "/login:输入框是空值");
                        MakeToast("error:输入框是null");
                    } else if (e.code == EmptyEditTextException.Empty_Username) {
                        //没有输入用户名
                        Log.d(TAG, "/login:没有输入用户名");
                        MakeToast("没有有输入用户名");
                    } else if (e.code == EmptyEditTextException.Empty_Password) {
                        //没有输入密码
                        Log.d(TAG, "/login:没有输入密码");
                        MakeToast("没有输入密码");
                    }
                } catch (Exception e) {
                    Log.d(TAG, "网络请求失败" + e.getMessage());
                    MakeToast("网络请求失败:" + e.getMessage());
                } finally {
                    if (response != null) response.close();
                    Log.d(TAG, "finish");
                }
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
}