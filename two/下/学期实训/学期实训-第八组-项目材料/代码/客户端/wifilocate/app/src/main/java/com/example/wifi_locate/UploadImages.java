package com.example.wifi_locate;

import static android.content.Intent.FLAG_ACTIVITY_CLEAR_TASK;
import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import androidx.activity.EdgeToEdge;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.alibaba.fastjson2.JSON;
import com.example.wifi_locate.Internet.Internet_Global;
import com.example.wifi_locate.Internet.MyCookieJar;
import com.example.wifi_locate.MyException.InternetException;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

import okhttp3.Call;
import okhttp3.FormBody;
import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class UploadImages extends AppCompatActivity {
    private String TAG = "Upload";
    private ActivityResultLauncher<Intent> activityResultLauncher;
    private Button selectButton;
    private Uri uri;
    private ImageView _selectimage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_upload_images);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        selectButton = findViewById(R.id.select_button);
        _selectimage = findViewById(R.id.selected_image);
        activityResultLauncher = registerForActivityResult(new ActivityResultContracts.StartActivityForResult(), result -> {

            try {   // 返回处理
                if (result.getResultCode() == RESULT_OK) {
                    Intent data = result.getData();
                    uri = data.getData();
                    Log.d(TAG, "选择了文件: " + uri);
                    send_the_image(uri);
                } else {
                    Log.d(TAG, "没有选择");
                }
            } catch (Exception e) {
                Log.d(TAG, "onCreate: " + e.getMessage());
                Log.e(TAG, "onCreate: ", e);
            }
        });

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



    /**
     * 上传一个40M的视频文件
     */
    private void send_the_image(Uri uri) {

        File file = UritoFile(uri);
        if (file.exists()) {
            ByteArrayOutputStream baos = null;
            FileInputStream fis = null;
            try {
                baos = new ByteArrayOutputStream();
                fis = new FileInputStream(file);
                int len = 0;
                byte[] buffer = new byte[3000];
                while ((len = fis.read(buffer)) != -1) {
                    baos.write(buffer, 0, len);
                }
                byte[] image_bytes = baos.toByteArray();

                Log.d(TAG, "Image_size: " + image_bytes.length);
                Bitmap bitmap = BitmapFactory.decodeByteArray(image_bytes, 0, image_bytes.length);
                if (bitmap == null) throw new InternetException();
                // 将 Bitmap 设置到 ImageView 中显示
                _selectimage.setImageBitmap(bitmap);

            } catch (InternetException e) {
                Log.d(TAG, "uploadImage is null!!");
            } catch (FileNotFoundException e) {
                throw new RuntimeException(e);
            } catch (IOException e) {
                throw new RuntimeException(e);
            } finally {
                try {
                    if (baos != null) baos.close();
                    if (fis != null) fis.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }

            }




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

//    private void upload()


    public void select_file(View view) {
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("image/*");//筛选器
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        activityResultLauncher.launch(intent);
    }

//    public void get_image_test(View view) {
//        Thread t1=new Thread(()->{
//            try{
//                OkHttpClient okHttpClient = new OkHttpClient
//                        .Builder().cookieJar(new MyCookieJar()).connectTimeout(10, TimeUnit.SECONDS).build();
//                List<Integer> id_list=new ArrayList<>();
//                id_list.add(1);
////                id_list.add(2);
//                MediaType mediaType=MediaType.Companion.parse("application/json;charset=utf-8");
//                RequestBody requestBody=RequestBody.Companion.create(JSON.toJSONString(id_list), mediaType);
//
//
//                OkHttpClient okHttpClientPostJson = new OkHttpClient();
//
//                Request request = new Request.Builder()
//                        .url(Internet_Global.Root + "/user/get_uic")
//                        .post(requestBody)
//                        .build();
//                //3.获取call对象
//                Call call = okHttpClient.newCall(request);
//                //4.执行网络操作（同步）
//                //同步执行网络操作
//                Response response = call.execute();
//                InputStream is=response.body().byteStream();
//                ByteArrayOutputStream baos=new ByteArrayOutputStream();
//                byte[] buffer=new byte[1000];
//                int len=0;
//                while ((len=is.read(buffer))!=-1){
//                    baos.write(buffer,0,len);
//                }
//                byte[] image_bytes=baos.toByteArray();
//                Bitmap bitmap = BitmapFactory.decodeByteArray(image_bytes, 0, image_bytes.length);
//                // 在主线程更新 UI
//                runOnUiThread(() -> {
//                    _selectimage.setImageBitmap(bitmap);
//                });
//            } catch (IOException e) {
//                Log.d(TAG, e.getMessage());
//                Log.e(TAG, "get_the_image: ",e );
//            }catch (Exception e){
//                Log.e(TAG, "get_image_test: ", e);
//            }
//        });
//        t1.start();
//
//    }
}