package com.example.wifi_locate;
import android.Manifest;
import static android.app.PendingIntent.getActivity;
import static android.content.Intent.FLAG_ACTIVITY_CLEAR_TASK;
import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

import static com.example.frontend.StaticRvAdapter.selectedPosition;
import static android.content.Intent.FLAG_ACTIVITY_CLEAR_TASK;
import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;


import android.app.Application;

import com.example.frontend.DynamicRVModel_for_comment;
import android.annotation.SuppressLint;
import android.content.Intent;

import android.content.pm.PackageManager;
import android.graphics.Color;
import android.net.Uri;

import android.os.Bundle;

import android.speech.tts.TextToSpeech;
import android.text.SpannableString;
import android.text.style.ForegroundColorSpan;
import android.text.style.UnderlineSpan;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RatingBar;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.frontend.DRVinterface.UpdateRecycleView;
import com.example.frontend.DRVinterface.UpdateRecycleView1;
import com.example.frontend.DynamicRVAdapter;
import com.example.frontend.DynamicRVAdapter1;
import com.example.frontend.DynamicRVModel;
import com.example.frontend.StaticRvAdapter;
import com.example.frontend.StaticRvAdapter1;
import com.example.frontend.StaticRvModel;
import com.example.wifi_locate.Internet.Internet_Global;
import com.example.wifi_locate.Internet.MyCookieJar;
import com.example.wifi_locate.MyException.EmptyEditTextException;
import com.getbase.floatingactionbutton.FloatingActionButton;
import com.getbase.floatingactionbutton.FloatingActionsMenu;
import com.google.android.material.bottomnavigation.BottomNavigationView;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Locale;

import okhttp3.Call;
import okhttp3.FormBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class ShopActivity extends AppCompatActivity implements UpdateRecycleView,UpdateRecycleView1,TextToSpeech.OnInitListener {
    private FloatingActionButton fabAction1;
    private RatingBar ratingBar;
    private EditText etComment1;
    private RecyclerView recyclerView,recyclerView2;
    private static final int MY_REQUEST_CODE = 12345;
    private String TAG = "SPEECHSTH";
    ArrayList<DynamicRVModel> items = new ArrayList<>();
    private static final  int MY_PERMISSIONS_REQUEST_RECORD_AUDIO=123;
    private static final int REQUEST_SPEECH_INPUT=1234;
    DynamicRVAdapter dynamicRVAdapter;
    private StaticRvAdapter staticRvAdapter;
    DynamicRVAdapter1 dynamicRVAdapter1;
    private StaticRvAdapter1 staticRvAdapter1;

    //识别功能
    private TextToSpeech mTts;
    private Button mButton;

;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_shop2);

        //语音权限
       // SpeechUtility.createUtility(ShopActivity.this,"appid=b3cdb87b");
        // 动态请求录音和网络权限（Android 6.0及以上）


        mTts=new TextToSpeech(this, this::onInit);


        //底部导航栏的切换
        BottomNavigationView bottomNavigationView = findViewById(R.id.bottomnavigation);
        bottomNavigationView.setSelectedItemId(R.id.navigationshop);
        bottomNavigationView.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @SuppressLint("NonConstantResourceId")
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                if(item.getItemId()==R.id.navigationhome) {

                    Intent intent=new Intent(new Intent(ShopActivity.this, HomePage4Activity.class));
                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                    startActivity(intent);
                    return true;
                }
                else if(item.getItemId()==R.id.navigationshop) {
                    return true;
                }
                else if(item.getItemId()==R.id.navigationnavigation) {
                    Intent intent=new Intent(new Intent(ShopActivity.this, NavigationActivity.class));
                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                    startActivity(intent);
                    return true;
                }
//                else if (item.getItemId()==R.id.navigationreviews) {
//                    Intent intent=new Intent(new Intent(ShopActivity.this, ProfileActivity.class));
//                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
//                    startActivity(intent);
//
//                    return true;
//                }
                else return false;
            }
        });


        //对于悬浮按钮的展示
        FloatingActionsMenu floatingMenu = findViewById(R.id.floating_menu);

        FloatingActionButton fabAction2 = findViewById(R.id.fabaction2);
        FloatingActionButton fabAction1=findViewById(R.id.fabaction);
        //FloatingActionButton fabAction3=findViewById(R.id.fabaction3);


        fabAction2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                showRatingInputDialog();
            }
        });
        fabAction1.setOnClickListener(new View.OnClickListener() {
            @SuppressLint("QueryPermissionsNeeded")
            @Override
            public void onClick(View v) {
                if (ContextCompat.checkSelfPermission(ShopActivity.this, Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
                    // 权限尚未被授予，请求权限
                    ActivityCompat.requestPermissions(ShopActivity.this,
                            new String[]{Manifest.permission.CALL_PHONE},
                            MY_REQUEST_CODE); // YOUR_REQUEST_CODE是一个你定义的int常量
                } else {
                    // 权限已经被授予，执行拨打电话的操作（如果你需要的话）
                    makePhoneCall();
                }
            }
        });

//        fabAction3.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//
////                if (ContextCompat.checkSelfPermission(ShopActivity.this, Manifest.permission.RECORD_AUDIO)
////                        != PackageManager.PERMISSION_GRANTED) {
////                    // 如果没有权限，则请求权限
////                    ActivityCompat.requestPermissions(ShopActivity.this,
////                            new String[]{Manifest.permission.RECORD_AUDIO},
////                            MY_PERMISSIONS_REQUEST_RECORD_AUDIO);
////                } else {
////                    // 如果有权限，则初始化语音识别
////                    initiateVoiceRecognition();
////                }
//
//
////                showmes();
//
//
//
//
//
//
//            }
//        });


        //循环视图的展示，正常情况下的显示
        final ArrayList<StaticRvModel> item=new ArrayList<>();
        item.add(new StaticRvModel(R.mipmap.canteen2,"金山城"));
        item.add(new StaticRvModel(R.mipmap.k,"kumo"));
        item.add(new StaticRvModel(R.mipmap.x,"喜茶"));
        item.add(new StaticRvModel(R.mipmap.canteen5,"鲜牛记"));
        item.add(new StaticRvModel(R.mipmap.m,"满记甜品"));
        item.add(new StaticRvModel(R.mipmap.c,"奈雪的茶"));
        recyclerView=findViewById(R.id.recyclerview1);

        staticRvAdapter=new StaticRvAdapter(item,this,this);
        staticRvAdapter1=new StaticRvAdapter1(item,this, (UpdateRecycleView1) this);


        // 创建线性布局管理器，并设置为水平方向
        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
        layoutManager.setOrientation(LinearLayoutManager.HORIZONTAL);
        // 设置RecyclerView的布局管理器
        recyclerView.setLayoutManager(layoutManager);
        recyclerView.setAdapter(staticRvAdapter);


        //下方的食物展示
        items = new ArrayList<>();
        recyclerView2 = findViewById(R.id.recyclerview2);
        dynamicRVAdapter = new DynamicRVAdapter(items);
        dynamicRVAdapter1=new DynamicRVAdapter1(new ArrayList<>());

        // 创建线性布局管理器，并设置为垂直方向
        LinearLayoutManager layoutManager1 = new LinearLayoutManager(this);
        layoutManager1.setOrientation(LinearLayoutManager.VERTICAL);
        // 设置RecyclerView的布局管理器
        recyclerView2.setLayoutManager(layoutManager1);
        recyclerView2.setAdapter(dynamicRVAdapter);


        //左右切换商家和评论
        TextView textViewShop = findViewById(R.id.textViewShop);
        TextView textViewPeople = findViewById(R.id.textViewReview);

        // 设置初始状态
        updateTextViewStyle(textViewShop, true); // 设置TextViewShop为点击状态
        updateTextViewStyle(textViewPeople, false); // 设置TextViewPeople为未点击状态

        // 点击事件处理
        TextView finalTextViewShop = textViewShop;
        TextView finalTextViewPeople = textViewPeople;
        textViewShop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updateTextViewStyle(finalTextViewShop, true); // 点击TextViewShop
                updateTextViewStyle(finalTextViewPeople, false); // 设置TextViewPeople为未点击状态
                recyclerView.setLayoutManager(layoutManager);
                recyclerView.setAdapter(staticRvAdapter);
                recyclerView2.setLayoutManager(layoutManager1);
                recyclerView2.setAdapter(dynamicRVAdapter);

            }
        });

        textViewPeople.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updateTextViewStyle(finalTextViewShop, false); // 设置TextViewShop为未点击状态
                updateTextViewStyle(finalTextViewPeople, true); // 点击TextViewPeople

                recyclerView.setLayoutManager(layoutManager);
                recyclerView.setAdapter(staticRvAdapter1);
                recyclerView2.setLayoutManager(layoutManager1);
                recyclerView2.setAdapter(dynamicRVAdapter1);



            }
        });












    }

    @Override
    public void callback(int position, ArrayList<DynamicRVModel> items) {
        dynamicRVAdapter = new DynamicRVAdapter(items);
        dynamicRVAdapter.notifyDataSetChanged();
        recyclerView2.setAdapter(dynamicRVAdapter);

    }

    @Override
    public void callback1(int position, ArrayList<DynamicRVModel_for_comment> items) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                dynamicRVAdapter1=new DynamicRVAdapter1(items);
                dynamicRVAdapter1.notifyDataSetChanged();
                recyclerView2.setAdapter(dynamicRVAdapter1);
            }
        });

    }


    //开启新界面获取相关信息
    @SuppressLint("MissingInflatedId")
    private void showRatingInputDialog() {
        // Inflate the dialog layout
        View dialogView = LayoutInflater.from(this).inflate(R.layout.dialog_rating_input, null);

        // Initialize views
        ratingBar = dialogView.findViewById(R.id.ratingBar);
//        etComment = dialogView.findViewById(R.id.etComment);
        etComment1=dialogView.findViewById(R.id.etComment1);
        Button btnSubmit = dialogView.findViewById(R.id.btnSubmit);

        // Create and show the dialog
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setView(dialogView);
        final AlertDialog dialog = builder.create();
        dialog.show();

        // Handle submit button click
        btnSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                float rating = ratingBar.getRating();
                int id=selectedPosition;
                String comment=etComment1.getText().toString().trim();

//                if (rating == 0 || comment.isEmpty()) {
                if (rating == 0 || comment.isEmpty()) {
                    Toast.makeText(ShopActivity.this, "请填写反馈", Toast.LENGTH_SHORT).show();
                } else {
                    // Dismiss the dialog
                    dialog.dismiss();
//                    Toast.makeText(ShopActivity.this, "感谢您的反馈！", Toast.LENGTH_SHORT).show();
                    // 处理反馈逻辑
                    // 例如，将反馈信息发送到服务器或保存到本地
                    Comment_Post(String.valueOf(id),rating,comment);
                }
            }
        });
    }


//    @SuppressLint("MissingInflatedId")
//    private void showmes() {
//        // Inflate the dialog layout
//        View dialogView = LayoutInflater.from(this).inflate(R.layout.modify_userrec, null);
//
//
//
//        mButton = dialogView.findViewById(R.id.btnSubmitrec);
//
//        // Create and show the dialog
//        AlertDialog.Builder builder = new AlertDialog.Builder(this);
//        builder.setView(dialogView);
//        final AlertDialog dialog = builder.create();
//        dialog.show();
//
//        // Handle submit button click
//        mButton.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//
//                sayHello();
//
//
//
//            }
//        });
//    }




    private class post_runable implements Runnable {
        String name;
        float stars;
        String comment;
        public post_runable(String name, float stars, String comment) {
            this.name = name;
            this.stars = stars;
            this.comment = comment;
        }
        @Override
        public void run() {
            Response response = null;
            if (comment == null || comment.isEmpty()) comment = "这个人很懒，没有留下评论";

            try {
                Log.d(TAG, "发送请求");
                OkHttpClient okHttpClient = new OkHttpClient.Builder()
                        .cookieJar(new MyCookieJar())
                        .build();
                //2.获取request对象
                RequestBody requestBody = new FormBody.Builder().add("sid", name).add("stars", String.valueOf(stars)).add("comment", comment).build();
                Request request = new Request.Builder()
                        .url(Internet_Global.Root + "/comment")
                        .post(requestBody)
                        .build();

                //3.获取call对象
                Call call = okHttpClient.newCall(request);
                //4.执行网络操作（同步）
                //同步执行网络操作
                response = call.execute();

                String result = response.body().string();
                Log.d(TAG, response.headers().toString());

                if (result.equals("100")) {
                    MakeToast("感谢你的评价！！");
                } else if(result.equals("204")) {
                    MakeToast("评论过于频繁");
                }else if(result.equals("206")){
                    MakeToast("error未登录");
                }


            } catch (Exception e) {
                Log.d(TAG, "网络请求失败" + e.getMessage() + Arrays.toString(e.getStackTrace()));
                MakeToast("网络请求失败:" + e.getMessage());
            } finally {
                if (response != null) response.close();
                Log.d(TAG, "finish");
            }
        }
    }

    private void Comment_Post(String name, float stars, String comment) {
        new Thread(new post_runable(name, stars, comment)).start();
    }

    private void MakeToast(String massage) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(getApplicationContext(), massage, Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void updateTextViewStyle(TextView textView, boolean clicked) {
        String text = textView.getText().toString();
        SpannableString spannableString = new SpannableString(text);

        if (clicked) {
            // 点击状态，设置为 #FF5A66 的颜色和添加下划线
            spannableString.setSpan(new ForegroundColorSpan(Color.parseColor("#FF5A66")), 0, text.length(), 0);
            spannableString.setSpan(new UnderlineSpan(), 0, text.length(), 0);
        } else {
            // 未点击状态，设置为黑色和取消下划线
            spannableString.setSpan(new ForegroundColorSpan(Color.BLACK), 0, text.length(), 0);
            spannableString.setSpan(new UnderlineSpan(), 0, 0, 0); // 取消下划线的方式
        }

        // 应用SpannableString到TextView
        textView.setText(spannableString);
    }


    // 处理权限请求结果的回调方法
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == MY_REQUEST_CODE) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                // 权限被授予，执行拨打电话的操作
                makePhoneCall();
            } else {
                // 权限请求被拒绝
                Toast.makeText(this, "权限被拒绝，无法拨打电话", Toast.LENGTH_SHORT).show();
            }
        }
    }

    // 拨打电话的方法（如果你需要的话）
    private void makePhoneCall() {
        Intent callIntent = new Intent(Intent.ACTION_CALL);
        String phonenumber = "";
        if(selectedPosition==0){
            phonenumber="13584149536";

        } else if (selectedPosition==1) {
            phonenumber="15299001706";
        }
        else if(selectedPosition==2){
            phonenumber="18094987067";
        }else if(selectedPosition==3){
            phonenumber="18501925734";
        }
        else if(selectedPosition==4){
            phonenumber="18810758375";
        }
        else if(selectedPosition==5){
            phonenumber="13584149536";
        }
        callIntent.setData(Uri.parse("tel:" + phonenumber));
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
            return;
        }
        startActivity(callIntent);
    }

//
//    private void initiateVoiceRecognition() {
//        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
//        if (intent.resolveActivity(getPackageManager()) != null) {
//            intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
//            intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());
//            startActivityForResult(intent, REQUEST_SPEECH_INPUT);
//        } else {
//            // 没有语音识别活动，可以在这里处理
//            Toast.makeText(this, "此设备不支持语音识别", Toast.LENGTH_SHORT).show();
//        }
//    }
//
//    @Override
//    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
//        super.onActivityResult(requestCode, resultCode, data);
//        if (requestCode == REQUEST_SPEECH_INPUT && resultCode == RESULT_OK) {
//            ArrayList<String> result = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
//            if (result != null && !result.isEmpty()) {
//                String spokenText = result.get(0);
//                Log.d("VoiceRecognition", "语音识别: " + spokenText);
//                // 在这里处理并展示识别出的文本
//            } else {
//                // 结果为空，可以在这里处理
//                Toast.makeText(this, "没有识别到语音", Toast.LENGTH_SHORT).show();
//            }
//        } else if (resultCode == RecognizerIntent.RESULT_CLIENT_ERROR) {
//            // 语音识别出错，可以在这里处理
//            Toast.makeText(this, "语音识别出错", Toast.LENGTH_SHORT).show();
//        }
//    }

    //文字转语音
@Override
public void onDestroy() {
    // 生命周期中结束
    if (mTts != null) {
        mTts.stop();
        mTts.shutdown();
    }

    super.onDestroy();
}
    // 实现TextToSpeech.OnInitListener.
    public void onInit(int status) {
        if (status == TextToSpeech.SUCCESS) {
            //设置首选语言为中文,注意，语言可能是不可用的，结果将指示此
            int result = mTts.setLanguage(Locale.CHINA);
            if (result == TextToSpeech.LANG_MISSING_DATA ||
                    result == TextToSpeech.LANG_NOT_SUPPORTED) {
                //语言数据丢失或不支持该语言。
                Log.e(TAG, "语言数据丢失或不支持该语言");
            } else {
                //检查文档中其他可能的结果代码。
                // 例如，语言可能对区域设置可用，但对指定的国家和变体不可用
                // TTS引擎已成功初始化。
                // 允许用户按下按钮让应用程序再次发言。//mAgainButton.setEnabled(true);
            }
        } else {
            // 初始化失败
            Log.e(TAG, "初始化失败");
        }
    }

    private void sayHello() {
        String hello ="计蒙不吃鱼";
        //TextToSpeech的speak方法有两个重载。
        // 执行朗读的方法
        //speak(CharSequence text,int queueMode,Bundle params,String utteranceId);
        // 将朗读的的声音记录成音频文件
        //synthesizeToFile(CharSequence text,Bundle params,File file,String utteranceId);
        //第二个参数queueMode用于指定发音队列模式，两种模式选择
        //（1）TextToSpeech.QUEUE_FLUSH：该模式下在有新任务时候会清除当前语音任务，执行新的语音任务
        //（2）TextToSpeech.QUEUE_ADD：该模式下会把新的语音任务放到语音任务之后，
        //等前面的语音任务执行完了才会执行新的语音任务

        int speak = mTts.speak(hello,
                TextToSpeech.QUEUE_FLUSH,
                null);


    }


}




