package com.example.wifi_locate;

import static android.content.Intent.FLAG_ACTIVITY_CLEAR_TASK;
import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;
import static android.graphics.BitmapFactory.decodeByteArray;
import static android.graphics.BitmapFactory.decodeStream;
import static com.example.frontend.StaticRvAdapter.selectedPosition;
import static com.example.wifi_locate.R.drawable.grey_background;
import static com.example.wifi_locate.R.drawable.list_item;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.widget.Toolbar;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageDecoder;
import android.graphics.drawable.Animatable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.widget.Spinner;

import com.alibaba.fastjson2.JSON;
import com.example.wifi_locate.Internet.Internet_Global;
import com.example.wifi_locate.Internet.MyCookieJar;
import com.example.wifi_locate.MyException.InternetException;
import com.google.android.material.bottomnavigation.BottomNavigationView;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.TimeUnit;

import okhttp3.Call;
import okhttp3.FormBody;
import okhttp3.Headers;
import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import okhttp3.ResponseBody;
import okio.BufferedSink;

public class HomePage4Activity extends AppCompatActivity {

    private String TAG = "HP";
    private ActivityResultLauncher<Intent> activityResultLauncher;
    private ImageView user_ic;
    private File file;
    private Bitmap bitmap;
    private EditText new_name;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_page4);
        file=null;
        activityResultLauncher = registerForActivityResult(new ActivityResultContracts.StartActivityForResult(), result -> {
            try {   // 返回处理
                if (result.getResultCode() == RESULT_OK) {
                    Intent data = result.getData();
                    Uri uri = data.getData();
                    Log.d(TAG, "选择了文件: " + uri);
                    file=UritoFile(uri);
                    user_ic.setImageBitmap(getImage(file));
                } else {
                    Log.d(TAG, "没有选择");
                }
            } catch (Exception e) {
                Log.d(TAG, "onCreate: " + e.getMessage());
                Log.e(TAG, "onCreate: ", e);
            }
        });


        //修改相关内容
        Spinner spinner = findViewById(R.id.spinner);
        @SuppressLint("ResourceType") ArrayAdapter<CharSequence> adapter1 = ArrayAdapter.createFromResource(this,
                R.array.spinner_string, R.drawable.list_item); // 使用自定义布局
        spinner.setAdapter(adapter1);
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                String selectedItem = (String) spinner.getSelectedItem();

                if (Objects.equals(selectedItem, "修改头像")) {
                    showRatingInputIcon();

                } else if (Objects.equals(selectedItem, "修改用户名")) {

                    showNameEditDialg();
                } else if (Objects.equals(selectedItem, "查看个人信息")) {


                    showmesshangchuan();
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {

            }
        });


        //gif图展示
        @SuppressLint({"MissingInflatedId", "LocalSuppress"})
        ImageView img_gif = findViewById(R.id.gif1);
        //如果系统版本为Android9.0以上,则利用新增的AnimatedImageDrawable显示GIF动画
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            try {
                //利用Android9.0新增的ImageDecoder读取gif动画
                ImageDecoder.Source source = ImageDecoder.createSource(getResources(), R.drawable.test1);
                //从数据源中解码得到gif图形数据
                @SuppressLint("WrongThread") Drawable drawable = ImageDecoder.decodeDrawable(source);
                //设置图像视图的图形为gif图片
                img_gif.setImageDrawable(drawable);
                //如果是动画图形，则开始播放动画
                if (drawable instanceof Animatable) {
                    Animatable animatable = (Animatable) img_gif.getDrawable();
                    animatable.start();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        @SuppressLint({"MissingInflatedId", "LocalSuppress"}) ImageView img_gif2 = findViewById(R.id.gif2);
        //如果系统版本为Android9.0以上,则利用新增的AnimatedImageDrawable显示GIF动画
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            try {
                //利用Android9.0新增的ImageDecoder读取gif动画
                ImageDecoder.Source source = ImageDecoder.createSource(getResources(), R.drawable.test3);
                //从数据源中解码得到gif图形数据
                @SuppressLint("WrongThread") Drawable drawable = ImageDecoder.decodeDrawable(source);
                //设置图像视图的图形为gif图片
                img_gif2.setImageDrawable(drawable);
                //如果是动画图形，则开始播放动画
                if (drawable instanceof Animatable) {
                    Animatable animatable = (Animatable) img_gif2.getDrawable();
                    animatable.start();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }


        @SuppressLint({"MissingInflatedId", "LocalSuppress"}) ImageView img_gif1 = findViewById(R.id.gif3);
        //如果系统版本为Android9.0以上,则利用新增的AnimatedImageDrawable显示GIF动画
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            try {
                //利用Android9.0新增的ImageDecoder读取gif动画
                ImageDecoder.Source source = ImageDecoder.createSource(getResources(), R.drawable.test2);
                //从数据源中解码得到gif图形数据
                @SuppressLint("WrongThread") Drawable drawable = ImageDecoder.decodeDrawable(source);
                //设置图像视图的图形为gif图片
                img_gif1.setImageDrawable(drawable);
                //如果是动画图形，则开始播放动画
                if (drawable instanceof Animatable) {
                    Animatable animatable = (Animatable) img_gif1.getDrawable();
                    animatable.start();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }


        //底部导航栏
        BottomNavigationView bottomNavigationView = findViewById(R.id.bottomnavigation);
        bottomNavigationView.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @SuppressLint("NonConstantResourceId")
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                if (item.getItemId() == R.id.navigationhome) {

                    return true;
                } else if (item.getItemId() == R.id.navigationshop) {
                    Intent intent = new Intent(HomePage4Activity.this, ShopActivity.class);

                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                    startActivity(intent);

                    return true;
                } else if (item.getItemId() == R.id.navigationnavigation) {
                    Intent intent = new Intent(HomePage4Activity.this, NavigationActivity.class);
                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                    startActivity(intent);
                    return true;
                }
//                else if (item.getItemId()==R.id.navigationreviews) {
//                    Intent intent=new Intent(HomePage4Activity.this, ProfileActivity.class);
//                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
//                    startActivity(intent);
//
//                    return true;
//                }
                else return false;
            }
        });


        //三个按钮的跳转界面
        //点击事件
        findViewById(R.id.gonavigation).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //点击跳转到导航界面
                Intent intent = new Intent(HomePage4Activity.this, NavigationActivity.class);
                intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                startActivity(intent);
            }
        });
        findViewById(R.id.goshop).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //点击跳转到商店界面
                Intent intent = new Intent(HomePage4Activity.this, ShopActivity.class);
                intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                startActivity(intent);
            }
        });
        findViewById(R.id.goreview).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //点击跳转到评价界面
                Intent intent = new Intent(HomePage4Activity.this, ShopActivity.class);
                intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                startActivity(intent);
            }
        });


        //spinner适配器
        //spinner获取地址
        Spinner searchBoxSpinner1 = findViewById(R.id.search_box_spinner1);
        // 创建适配器并设置数据源
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.spinner_items, android.R.layout.simple_spinner_item);
        // 设置下拉框样式
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        // 绑定适配器到Spinner
        searchBoxSpinner1.setAdapter(adapter);

        findViewById(R.id.your_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String selectedItem = (String) searchBoxSpinner1.getSelectedItem();
                if (selectedItem.isEmpty()) {
                    Toast.makeText(HomePage4Activity.this, "请选择您想要前往的区域！", Toast.LENGTH_SHORT).show();
                }
                //判断地址是否正确的匹配问题
                else {
                    //点击跳转到注册界面
                    Intent intent = new Intent(HomePage4Activity.this, NavigationActivity.class);
                    // 在Intent中添加额外的数据
                    intent.putExtra("key_message", selectedItem);
                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                    // 启动ShopActivity
                    startActivity(intent);
                }


            }
        });
//实现退出登录的toolbar
        Toolbar toolbar = findViewById(R.id.toolbar1);
        setSupportActionBar(toolbar);
        if (getSupportActionBar() != null) {
            getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        }

        toolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 执行页面跳转的逻辑
                Intent intent = new Intent(HomePage4Activity.this, LoginActivity.class);
                Internet_Global.getInstance().delete_cookie();
                new Thread(() -> {
                    try {
                        OkHttpClient okHttpClient = new OkHttpClient.Builder()
                                .cookieJar(new MyCookieJar())
                                .build();
                        //2.获取request对象
                        RequestBody requestBody = new FormBody.Builder().build();
                        Request request = new Request.Builder()
                                .url(Internet_Global.Root + "/login/logout")
                                .post(requestBody)
                                .build();
                        //3.获取call对象
                        Call call = okHttpClient.newCall(request);
                        //4.执行网络操作（同步）
                        //同步执行网络操作
                        Response response = call.execute();
                    } catch (IOException e) {
                        Log.e(TAG, "onClick: ", e);
                    }
                }).start();
                intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                startActivity(intent);

            }
        });
    }

    //开启新界面获取相关信息
    @SuppressLint("MissingInflatedId")
    private void showRatingInputDialog() {
        // Inflate the dialog layout
        View dialogView = LayoutInflater.from(this).inflate(R.layout.modify_usermes, null);
//        etComment = dialogView.findViewById(R.id.etComment);
        EditText etComment1 = dialogView.findViewById(R.id.modifyComment1);
        EditText etComment2 = dialogView.findViewById(R.id.modifyComment2);
        Button btnSubmit = dialogView.findViewById(R.id.btnSubmitmodify);

        // Create and show the dialog
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setView(dialogView);
        final AlertDialog dialog = builder.create();
        dialog.show();

        // Handle submit button click
        btnSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int id = selectedPosition;
                String comment = etComment1.getText().toString().trim();
                String comment1 = etComment2.getText().toString().trim();
//                if (rating == 0 || comment.isEmpty()) {
                if (comment1.isEmpty() || comment.isEmpty()) {
                    Toast.makeText(HomePage4Activity.this, "请填写", Toast.LENGTH_SHORT).show();
                } else if (!comment1.equals(comment)) {
                    Toast.makeText(HomePage4Activity.this, "请确认前后修改信息相同", Toast.LENGTH_SHORT).show();

                } else {
                    // Dismiss the dialog
                    dialog.dismiss();
//                    Toast.makeText(ShopActivity.this, "感谢您的反馈！", Toast.LENGTH_SHORT).show();
                    // 处理反馈逻辑
                    // 例如，将反馈信息发送到服务器或保存到本地
                    //


                }
            }
        });
    }


    @SuppressLint("MissingInflatedId")
    private void showNameEditDialg() {
        // Inflate the dialog layout
        View dialogView = LayoutInflater.from(this).inflate(R.layout.modify_name, null);
        EditText etComment1 = dialogView.findViewById(R.id.new_name);
        Button btnSubmit = dialogView.findViewById(R.id.btnSubmitmodify);

        // Create and show the dialog
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setView(dialogView);
        final AlertDialog dialog = builder.create();
        dialog.show();

        // Handle submit button click
        btnSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int id = selectedPosition;
                String comment = etComment1.getText().toString().trim();

//                if (rating == 0 || comment.isEmpty()) {
                if (comment.isEmpty()) {
                    MakeToast("请输入新的名字");
                } else {
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                                Response response = null;
                                InputStream is = null;
                                ByteArrayOutputStream baos = null;

                                try{
                                    OkHttpClient okHttpClient = new OkHttpClient
                                            .Builder().cookieJar(new MyCookieJar()).connectTimeout(10, TimeUnit.SECONDS).build();

                                    RequestBody requestBody=new FormBody.Builder()
                                            .add("name",comment)
                                            .build();
                                    Request request = new Request.Builder()
                                            .url(Internet_Global.Root + "/user/update_name")
                                            .post(requestBody)
                                            .build();
                                    //3.获取call对象
                                    Call call = okHttpClient.newCall(request);
                                    //4.执行网络操作（同步）
                                    //同步执行网络操作
                                    response = call.execute();
                                    String result=response.body().string();

                                    switch (result) {
                                        case "100":
                                            MakeToast("修改成功!");
                                            break;
                                        case "204":
                                            MakeToast("修改失败！");
                                            break;
                                        default:
                                            MakeToast("error:"+result);
                                    }
                                } catch (IOException e) {
                                    MakeToast("error"+e.getMessage());
                                }finally {
                                    try{
                                        if(response!=null)response.close();
                                        if(is!=null)is.close();
                                        if(baos!=null)baos.close();
                                    } catch (IOException e) {
                                        throw new RuntimeException(e);
                                    }
                                }



                        }
                    }).start();
                    dialog.dismiss();
                }
            }
        });
    }

    @SuppressLint("MissingInflatedId")
    private void showRatingInputIcon() {
        // Inflate the dialog layout
        View dialogView = LayoutInflater.from(this).inflate(R.layout.modify_usericon, null);
//        etComment = dialogView.findViewById(R.id.etComment);
        user_ic = dialogView.findViewById(R.id.modifyIcon);
        Button btnSubmit = dialogView.findViewById(R.id.btnSubmitmodify);

        // Create and show the dialog


        new Thread(()->{
            Response response = null;
            InputStream is = null;
            ByteArrayOutputStream baos = null;
            bitmap = null;

            try{
                OkHttpClient okHttpClient = new OkHttpClient
                        .Builder().cookieJar(new MyCookieJar()).connectTimeout(10, TimeUnit.SECONDS).build();
                List<Integer> id_list = new ArrayList<>();
                id_list.add(-1);
                MediaType mediaType = MediaType.Companion.parse("application/json;charset=utf-8");
                RequestBody requestBody = RequestBody.Companion.create(JSON.toJSONString(id_list), mediaType);
                Request request = new Request.Builder()
                        .url(Internet_Global.Root + "/user/get_uic")
                        .post(requestBody)
                        .build();

                //3.获取call对象
                Call call = okHttpClient.newCall(request);
                //4.执行网络操作（同步）
                //同步执行网络操作
                response = call.execute();
                is = response.body().byteStream();
                baos = new ByteArrayOutputStream();
                byte[] buffer = new byte[1000];
                int len = 0;
                while ((len = is.read(buffer)) != -1) {
                    baos.write(buffer, 0, len);
                }
                byte[] image_bytes = baos.toByteArray();
                bitmap = decodeByteArray(image_bytes, 0, image_bytes.length);
            } catch (IOException e) {
                MakeToast("error"+e.getMessage());
//                throw new RuntimeException(e);
            }finally {
                try{
                    if(response!=null)response.close();
                    if(is!=null)is.close();
                    if(baos!=null)baos.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (bitmap != null)
                        user_ic.setImageBitmap(bitmap);
                    else
                        user_ic.setImageBitmap(Bitmap.createBitmap(256, 256, Bitmap.Config.ARGB_8888));
                }
            });
        }).start();

        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setView(dialogView);
        final AlertDialog dialog = builder.create();
        dialog.show();


        //修改头像
        user_ic.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 这里编写点击ImageView后你想执行的代码

                Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
                intent.setType("image/jpeg");//筛选器
                intent.addCategory(Intent.CATEGORY_OPENABLE);
                activityResultLauncher.launch(intent);
            }
        });

        // Handle submit button click
        btnSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // 处理反馈逻辑
                // 例如，将反馈信息发送到服务器或保存到本地
                if(file==null)MakeToast("请选择图片");
                else {
                    Thread t1=new Thread(()->{
                        try{
                            OkHttpClient okHttpClient = new OkHttpClient
                                    .Builder().cookieJar(new MyCookieJar()).connectTimeout(10, TimeUnit.SECONDS).build();
                            //MediaType 为全部类型
                            MediaType mediaType = MediaType.parse("/*");
                            //根据文件类型，将File装进RequestBody中
                            //将fileBody添加进MultipartBody
                            RequestBody fileBody = RequestBody.Companion.create(file, mediaType);

                            MultipartBody multipartBody=new MultipartBody.Builder()
                                    .setType(MultipartBody.FORM)
                                    .addFormDataPart("file",file.getName(),fileBody)
                                    .build();

                            Request request = new Request.Builder()
                                    .url(Internet_Global.Root + "/user/upload_ic")
                                    .post(multipartBody)
                                    .build();

                            //3.获取call对象
                            Call call = okHttpClient.newCall(request);
                            //4.执行网络操作（同步）
                            //同步执行网络操作
                            Response response = call.execute();
                            String result = response.body().string();
                            Log.d(TAG, result);
                            switch (result) {
                                case "100":
                                    Log.d(TAG, "发送成功");
                                    MakeToast("上传成功");
                                    break;
                            }
                        } catch (IOException e) {
                            Log.d(TAG, e.getMessage());
                            Log.e(TAG, "get_the_image: ",e );
                        }
                    });
                    t1.start();
                }

            }
        });
    }

    //查看个人头像和用户名
    @SuppressLint("MissingInflatedId")
    private void showmesshangchuan() {
        // Inflate the dialog layout
        View dialogView = LayoutInflater.from(this).inflate(R.layout.inquery_name, null);

        TextView textView=dialogView.findViewById(R.id.queTitle);
        ImageView imageView=dialogView.findViewById(R.id.queIcon);
//setimage和set text

        new Thread(new Runnable() {
            @Override
            public void run() {
                Response response = null;
                InputStream is = null;
                ByteArrayOutputStream baos = null;
                bitmap = null;
                try{
                    OkHttpClient okHttpClient = new OkHttpClient
                            .Builder().cookieJar(new MyCookieJar()).connectTimeout(10, TimeUnit.SECONDS).build();
                    List<Integer> id_list = new ArrayList<>();
                    id_list.add(-1);
                    MediaType mediaType = MediaType.Companion.parse("application/json;charset=utf-8");
                    RequestBody requestBody = RequestBody.Companion.create(JSON.toJSONString(id_list), mediaType);
                    Request request = new Request.Builder()
                            .url(Internet_Global.Root + "/user/get_uic")
                            .post(requestBody)
                            .build();
                    //3.获取call对象
                    Call call = okHttpClient.newCall(request);
                    //4.执行网络操作（同步）
                    //同步执行网络操作
                    response = call.execute();
                    is = response.body().byteStream();
                    baos = new ByteArrayOutputStream();
                    byte[] buffer = new byte[1000];
                    int len = 0;
                    while ((len = is.read(buffer)) != -1) {
                        baos.write(buffer, 0, len);
                    }
                    byte[] image_bytes = baos.toByteArray();
                    bitmap = decodeByteArray(image_bytes, 0, image_bytes.length);
                } catch (IOException e) {
                    MakeToast("error"+e.getMessage());
                }finally {
                    try{
                        if(response!=null)response.close();
                        if(is!=null)is.close();
                        if(baos!=null)baos.close();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            if (bitmap != null)
                                imageView.setImageBitmap(bitmap);
                            else
                                imageView.setImageBitmap(Bitmap.createBitmap(256, 256, Bitmap.Config.ARGB_8888));
                        }
                    });
                }

                try{
                    OkHttpClient okHttpClient = new OkHttpClient.Builder()
                            .cookieJar(new MyCookieJar())
                            .build();
                    //2.获取request对象
                   Request request = new Request.Builder()
                            .url(Internet_Global.Root + "/user/get_name")
                            .get()
                            .build();
                    //3.获取call对象
                    Call call = okHttpClient.newCall(request);
                    //4.执行网络操作（同步）
                    //同步执行网络操作
                    response = call.execute();

                    String result = response.body().string();
                    Log.d(TAG, response.headers().toString());

                    switch (result){
                        case "204":
                            MakeToast("error:未登录");
                            break;
                        default:
                            Log.d(TAG, "名字"+result);
                            runOnUiThread(()-> {
                                textView.setText(result);
                            });
                    }




                } catch (IOException e) {
                    MakeToast("error:"+e.getMessage());
                }finally {

                }


            }
        }).start();






        // Create and show the dialog
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setView(dialogView);
        final AlertDialog dialog = builder.create();
        dialog.show();












        Button button1=dialogView.findViewById(R.id.btnSubmitquit);
        // Handle submit button click
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dialog.dismiss();
            }
        });
    }



    private Bitmap getImage(File file1) {
        Bitmap bitmap = null;
        if (file1.exists()) {
            ByteArrayOutputStream baos = null;
            FileInputStream fis = null;
            try {
                baos = new ByteArrayOutputStream();
                fis = new FileInputStream(file1);
                int len = 0;
                byte[] buffer = new byte[3000];
                while ((len = fis.read(buffer)) != -1) {
                    baos.write(buffer, 0, len);
                }
                byte[] image_bytes = baos.toByteArray();
                Log.d(TAG, "Image_size: " + image_bytes.length);
                bitmap = BitmapFactory.decodeByteArray(image_bytes, 0, image_bytes.length);
                if (bitmap == null) throw new InternetException();
                // 将 Bitmap 设置到 ImageView 中显示
            } catch (InternetException e) {
                Log.d(TAG, "uploadImage is null!!");
            } catch (IOException e) {
                MakeToast("error:"+e.getMessage());
                Log.e(TAG, "getImage: ",e );
            } finally {
                try {
                    if (baos != null) baos.close();
                    if (fis != null) fis.close();
                } catch (IOException e) {
                    MakeToast("error:"+e.getMessage());
                    Log.e(TAG, "getImage: ",e );
                }

            }

        }
        return bitmap;

    }

    private File UritoFile(Uri uri) {
        String img_path;
        String[] proj = {MediaStore.Images.Media.DATA};
        Cursor actualimagecursor = this.managedQuery(uri, proj, null,
                null, null);
        if (actualimagecursor == null) {
            img_path = uri.getPath();
        } else {
            int actual_image_column_index = actualimagecursor
                    .getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
            actualimagecursor.moveToFirst();
            img_path = actualimagecursor
                    .getString(actual_image_column_index);
        }
        File file = new File(img_path);
        return file;
    }




    private void MakeToast(String massage) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(getApplicationContext(), massage, Toast.LENGTH_SHORT).show();
            }
        });
    }


    public void Submitmodify_newname(View view) {



    }
}
