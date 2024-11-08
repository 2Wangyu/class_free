package com.example.wifi_locate;

import androidx.biometric.BiometricPrompt;
import androidx.biometric.BiometricManager;
import androidx.core.content.ContextCompat;

import static android.content.Intent.FLAG_ACTIVITY_CLEAR_TASK;
import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;


import android.content.SharedPreferences;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.example.wifi_locate.Internet.Internet_Global;
import com.example.wifi_locate.Internet.MyCookieJar;
import com.example.wifi_locate.MyException.EmptyEditTextException;

import java.util.Arrays;
import java.util.concurrent.Executor;

import javax.crypto.Cipher;

import okhttp3.Call;
import okhttp3.FormBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class LoginActivity extends AppCompatActivity {
    private String cookie = null;
    private EditText et_username;
    private EditText et_password;
    private CheckBox is_save_account;
    private static final String TAG = "Page_Login";
    private SharedPreferences save_account;
    private ActivityResultLauncher<Intent> activityResultLauncher;
    public String myUsername;




    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_login);

        // 指纹识别的button
        Button btn1 = findViewById(R.id.login1);
        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                BiometricPrompt.PromptInfo promptInfo = new BiometricPrompt.PromptInfo.Builder()
                        .setTitle("Please Verify ")
                        .setDescription("User Authentication is required to proceed")
                        .setNegativeButtonText("Cancel")
                        .build();
                getPrompt().authenticate(promptInfo);
            }
        });

        //初始化控件
        et_username = findViewById(R.id.et_username);
        et_password = findViewById(R.id.et_password);
        save_account = getSharedPreferences("account", Context.MODE_PRIVATE);

        is_save_account = findViewById(R.id.save_account);
        is_save_account.setChecked(save_account.getBoolean("is_save", true));
        is_save_account.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                SharedPreferences.Editor editor = save_account.edit();
                Boolean is_checked = is_save_account.isChecked();
                if (!is_checked) {
                    editor.remove("username");
                    editor.remove("password");
                }
                editor.putBoolean("is_save", is_checked);
                editor.commit();
            }
        });

        if (is_save_account.isChecked()) {
            et_username.setText(save_account.getString("username", ""));
            et_password.setText(save_account.getString("password", ""));
        }


        //需要返回值的事件启动器
        activityResultLauncher = registerForActivityResult(new ActivityResultContracts.StartActivityForResult(), result -> {
            // 返回处理
            if (result.getResultCode() == RESULT_OK) {
                Intent data = result.getData();
                String result_username = null;
                if ((result_username = data.getStringExtra("username")) != null) {
                    et_username.setText(result_username);
                }
                String result_password = null;
                if ((result_password = data.getStringExtra("password")) != null) {
                    et_password.setText(result_password);
                }
            } else {
                Log.d(TAG, "接受result失败 ", new Exception("接收result失败"));
            }
        });
        //获取
//        sharedPreferences=getSharedPreferences("user",MODE_PRIVATE);


        //点击事件:注册
        findViewById(R.id.register).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //点击跳转到注册界面
                Intent intent = new Intent(LoginActivity.this, RegisterActivity.class);
                activityResultLauncher.launch(intent);
            }
        });

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        /**
         * 登录：by服务器
         */
        findViewById(R.id.login).setOnClickListener((View view) -> {
            login();
        });

    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    private void login() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                Response response = null;

                try {
                    if (et_username == null || et_password == null)
                        throw new EmptyEditTextException("EditText为null", EmptyEditTextException.Null_EditText);
                    String username = et_username.getText().toString();
                    String password = et_password.getText().toString();
                    if (username.isEmpty())
                        throw new EmptyEditTextException("空的用户名框", EmptyEditTextException.Empty_Username);
                    if (password.isEmpty())
                        throw new EmptyEditTextException("空的密码框", EmptyEditTextException.Empty_Password);

                    Log.d(TAG, "发送请求");
                    OkHttpClient okHttpClient = new OkHttpClient.Builder()
                            .cookieJar(new MyCookieJar())
                            .build();
                    //2.获取request对象
                    RequestBody requestBody = new FormBody.Builder().add("username", username).add("password", password).build();
                    Request request = new Request.Builder()
                            .url(Internet_Global.Root + "/login/login")
                            .post(requestBody)
                            .build();

                    //3.获取call对象
                    Call call = okHttpClient.newCall(request);
                    //4.执行网络操作（同步）
                    //同步执行网络操作
                    response = call.execute();

                    String result = response.body().string();
                    Log.d(TAG, response.headers().toString());

                    switch (result) {
                        case "100":
//                            登陆成功
                            /**
                             * 获取cookies,并放到唯一实例Internet_Global
                             */
//                            Headers headers=response.headers();
//                            List<Cookie> cookies=Cookie.parseAll(request.url(),headers);
//                            Internet_Global.getInstance().setCookies(Cookie.parseAll(request.url(),headers));
//                            跳转
                            SharedPreferences.Editor editor = save_account.edit();
                            if (is_save_account.isChecked()) {
                                editor.putString("username", username);
                                editor.putString("password", password);
                            }
                            editor.putString("finger_username", username);
                            editor.putString("finger_password", password);
                            editor.commit();
                        {
                            Intent intent = new Intent(LoginActivity.this, HomePage4Activity.class);
                            intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                            startActivity(intent);
                        }
                        break;
                        case "201":
//                            账号不存在
                            MakeToast("账号不存在");
                            break;
                        case "202":
//                            密码错误
                            MakeToast("密码错误");
                            break;
                        case "204": {
                            Intent intent = new Intent(LoginActivity.this, HomePage4Activity.class);
                            intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                            startActivity(intent);
                        }
                        //MakeToast("重复登录");
                        break;
                    }


                } catch (EmptyEditTextException e) {
                    if (e.code == EmptyEditTextException.Null_EditText) {
                        //输入框是空值
                        Log.d(TAG, "/login:输入框是空值");
                        MakeToast("error:输入框是空值");
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
                    Log.d(TAG, "网络请求失败" + e.getMessage() + Arrays.toString(e.getStackTrace()));
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

    // 指纹识别
    private BiometricPrompt getPrompt() {
        //获取主线程识别器
        Executor executor = ContextCompat.getMainExecutor(this);
        BiometricPrompt.AuthenticationCallback callback = new BiometricPrompt.AuthenticationCallback() {
            @Override
            public void onAuthenticationSucceeded(BiometricPrompt.AuthenticationResult result) {
                super.onAuthenticationSucceeded(result);

                String username = save_account.getString("finger_username", "");
                String password = save_account.getString("finger_password", "");
                myUsername=username;
                if (username.isEmpty() || password.isEmpty()) {
                    MakeToast("您还没有登录过哦。。。");
                } else {
                    et_username.setText(username);
                    et_password.setText(password);
                    login();
                    MakeToast("验证成功!");
                }

//                notifyUser("Authentication Succeed!");
//                Intent intent=new Intent(LoginActivity.this,HomePage4Activity.class);
//                intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
//                startActivity(intent);
            }

            @Override
            public void onAuthenticationFailed() {
                super.onAuthenticationFailed();
                notifyUser("Authentication Falled!!");
            }

            @Override
            public void onAuthenticationError(int errorCode, CharSequence errString) {
                super.onAuthenticationError(errorCode, errString);
                notifyUser(errString.toString());
            }
        };
        BiometricPrompt biometricPrompt = new androidx.biometric.BiometricPrompt(this, executor, callback);
        return biometricPrompt;
    }

    private void notifyUser(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }


}




