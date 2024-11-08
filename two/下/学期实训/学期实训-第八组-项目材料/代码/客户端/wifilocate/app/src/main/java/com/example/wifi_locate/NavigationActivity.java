package com.example.wifi_locate;

import static android.content.Intent.FLAG_ACTIVITY_CLEAR_TASK;
import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;
import java.util.Iterator;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.os.Looper;
import android.os.Message;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.Toast;
import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import com.getbase.floatingactionbutton.FloatingActionButton;
import com.getbase.floatingactionbutton.FloatingActionsMenu;
import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.android.material.chip.Chip;
import android.util.Log;
import android.util.DisplayMetrics;
import android.os.Handler;
import android.widget.TextView;
import android.Manifest;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import androidx.appcompat.app.AlertDialog;
import androidx.core.app.ActivityCompat;
import android.view.ViewTreeObserver;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class NavigationActivity extends AppCompatActivity {

    private Chip chipShop;
    private Chip chipPeople;
    private Chip chipDescri;
    private FrameLayout frameLayout;
    private  float positionX;
    private  float positionY;
    private ImageView imageView;
    private static final String TAG = "NavigationActivity";
    private WifiScanTask wifiScanTask;
    private Handler uiHandler;
    int screenWidth;
    int screenHeight;
    private int viewWidth;
    private int viewHeight;

    private static final int LOCATION_PERMISSION_REQUEST_CODE = 1;


    private MyLocation myLocation;
    private TextView coordinatesTextView;


    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_navigation);



        //定位相关操作
        myLocation = findViewById(R.id.myLocation);

        coordinatesTextView = findViewById(R.id.coordinatesTextView);

        DisplayMetrics displayMetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
        screenWidth = displayMetrics.widthPixels;
        screenHeight = displayMetrics.heightPixels;


        // 打印屏幕宽度和高度

        Log.e(TAG, "Screen width: " + screenWidth + "px");
        Log.e(TAG, "Screen height: " + screenHeight + "px");


        checkLocationPermission();




        //chip对应的操作
        chipShop = findViewById(R.id.chip_shop);
        chipPeople= findViewById(R.id.chip_people);
        chipDescri=findViewById(R.id.chip_describe);
        imageView=findViewById(R.id.navigationimage1);
        frameLayout = findViewById(R.id.frame_layout);


        // Setting up onCheckedChangeListener for chipShop
        chipShop.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (isChecked) {
                imageView.setImageDrawable(ContextCompat.getDrawable(this, R.mipmap.navigationselect));
            } else {
                imageView.setImageDrawable(ContextCompat.getDrawable(this, R.mipmap.navigationbg1));
            }
        });


        //
        chipPeople.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (isChecked) {
                myLocation.setNearby(1);
                myLocation.invalidate();
            } else {
                myLocation.setNearby(-1);
                myLocation.invalidate();
            }
        });

        // Setting up onCheckedChangeListener for chipPeople
        chipDescri.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (isChecked) {
                imageView.setImageDrawable(ContextCompat.getDrawable(this, R.mipmap.navigationselect1));
            } else {
                imageView.setImageDrawable(ContextCompat.getDrawable(this, R.mipmap.navigationbg1));
            }

        });




        //启动WiFi扫描，处理位置信息
        uiHandler = new Handler(Looper.getMainLooper()) {
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                Bundle bundle = msg.getData();
                String coordinates = bundle.getString("coordinates");
                String userPositionsString = bundle.getString("user_positions");

                //用户个人定位
                //coordinatesTextView.setText(coordinates);
                if (coordinates != null && coordinates.contains(",")) {
                    String[] parts = coordinates.replace("[", "").replace("]", "").split(",");
                    if (parts.length >= 2) {
                        try {


                            positionX = Float.parseFloat(parts[0].trim());
                            positionY = Float.parseFloat(parts[1].trim());

                            //Log.e(TAG, "x=" +positionX +"y="+positionY);


                            int width = myLocation.getWidth();
                            int height = myLocation.getHeight();
                            Log.e(TAG, "width=" + width + " height=" + height);
                            String positionName = "0";

                            switch (parts[2].trim()) {
                                case "415":
                                    positionName = "KumoKumo";
                                    break;
                                case "414":
                                    positionName = "鲜牛记";break;
                                case "414.1":
                                    positionName = "鲜牛记";
                                    break;
                                case "413":
                                    positionName = "金山城";
                                    break;
                                case "403":
                                    positionName = "奈雪的茶";
                                    break;
                                case "402":
                                    positionName = "喜茶";
                                    break;
                                case "401":
                                    positionName = "满记甜品";
                                    break;
                                default:
                                    positionName = "-1";

                            }
                            Log.e(TAG, "111111111  " + myLocation.getTargetName() + " 2222222222 " + positionName);


                            if (myLocation.useNavigation){
                                if (myLocation.getTargetName().equals(positionName)) {

                                        Toast.makeText(NavigationActivity.this, "已到达目的地", Toast.LENGTH_SHORT).show();
                                        myLocation.setNavigationType(0);
                                        myLocation.useNavigation = false;

                                }
                        }

                            myLocation.setPositionName(positionName);
                            myLocation.setDotPosition(positionX,positionY,width,height);
                            //myLocation.setDotPosition(0.4,0.71,width,height);
                           // myLocation .setDotPosition(x1,y1,screenWidth,screenHeight);

                        } catch (NumberFormatException e) {
                            e.printStackTrace();

                        }
                    }
                }


                //其他用户位置信息
                if (userPositionsString != null) {
                    try {
                        JSONObject userPositions = new JSONObject(userPositionsString);
                        UserPositionManager.getInstance().setUserPositions(userPositions);
                        // 遍历键值对列表
                        Iterator<String> keys = userPositions.keys();
                        while (keys.hasNext()) {
                            String key = keys.next();
                            String value = userPositions.getString(key);
                            Log.e(TAG, "User: " + key + ", Position: " + value);
                            // 在UI上显示或处理这些数据
                        }
                    } catch (JSONException e) {
                        Log.e(TAG, "Error parsing user_positions JSON: " + e.getMessage());
                    }
                }


            }
        };





        // 创建并启动后台WiFi扫描任务
        wifiScanTask = new WifiScanTask(this,uiHandler);
        Thread thread = new Thread(wifiScanTask);
        thread.start();
        Log.e(TAG, "线程启动" );



        //获得导航信息
        // 获取从上一个活动传递过来的消息
        if (getIntent().hasExtra("key_message")) {
            String message = getIntent().getStringExtra("key_message");
            Toast.makeText(NavigationActivity.this, message, Toast.LENGTH_SHORT).show();

            // 等待视图完成布局后再获取宽度和高度
            myLocation.getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
                @Override
                public void onGlobalLayout() {
                    // 确保监听器只触发一次
                    myLocation.getViewTreeObserver().removeOnGlobalLayoutListener(this);

                    // 获取视图的宽度和高度
                    viewWidth = myLocation.getWidth();
                    viewHeight = myLocation.getHeight();

                    Log.e(TAG, "mylocation width: " + viewWidth + "px");
                    Log.e(TAG, "mylocation height: " + viewHeight + "px");

                    myLocation.useNavigation=true;
                    myLocation.setTargetName(message);
                    Log.e(TAG, "主页面进入"+message );
                    myLocation.setbeginX(myLocation.getx());
                    Log.e(TAG,"x="+myLocation.getx());
                    myLocation.setbeginY(myLocation.gety());
                    myLocation.setNavigationType(1);
                    myLocation.setTargetPosition(message,viewWidth,viewHeight);



                }
            });
        }







        //spinner获取地址
        Spinner searchBoxSpinner = findViewById(R.id.search_box_spinner);
        // 创建适配器并设置数据源
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.spinner_items, android.R.layout.simple_spinner_item);
        // 设置下拉框样式
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        // 绑定适配器到Spinner
        searchBoxSpinner.setAdapter(adapter);

        //本界面的导航button
        findViewById(R.id.search_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // 假设你的 EditText 的 id 是 etMessage
                String selectedItem = (String) searchBoxSpinner.getSelectedItem();
                if( selectedItem.isEmpty() ){
                    Toast.makeText(NavigationActivity.this, "请选择您想要前往的区域！", Toast.LENGTH_SHORT).show();
                }
                else {
                   //开始导航
//
                    Toast.makeText(NavigationActivity.this, selectedItem, Toast.LENGTH_SHORT).show();
//********************************************************

                    int width = myLocation.getWidth();
                    int height = myLocation.getHeight();
                    Log.e(TAG, "导航2width="+width +"height="+ height );
                    myLocation.useNavigation=true;
                    myLocation.setTargetName(selectedItem);
                    myLocation.setbeginX(myLocation.getx());
                    myLocation.setbeginY(myLocation.gety());

                    // 延迟1秒执行操作
                    Handler handler = new Handler();
                    handler.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            // 在这里写入延迟执行的代码
                            myLocation.setNavigationType(1);
                            myLocation.setTargetPosition(selectedItem,width,height);
                        }
                    }, 100); // 1000 毫秒 = 1 秒




                }

            }
        });



        //底部导航栏
        BottomNavigationView bottomNavigationView = findViewById(R.id.bottomnavigation);
        bottomNavigationView.setSelectedItemId(R.id.navigationnavigation);

        bottomNavigationView.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @SuppressLint("NonConstantResourceId")
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                if(item.getItemId()==R.id.navigationhome) {
                    Intent intent=new Intent(new Intent(NavigationActivity.this, HomePage4Activity.class));
                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                    startActivity(intent);
                    return true;

                }
                else if(item.getItemId()==R.id.navigationshop) {
                    Intent intent=new Intent(new Intent(NavigationActivity.this, ShopActivity.class));
                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
                    startActivity(intent);
                    return true;
                }
                else if(item.getItemId()==R.id.navigationnavigation) {

                    return true;
              }
//                else if (item.getItemId()==R.id.navigationreviews) {
//
//                    Intent intent=new Intent(new Intent(NavigationActivity.this, ProfileActivity.class));
//                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
//                    startActivity(intent);
//                    return true;
//                }
                else return false;
            }
        });

        //
        //对于悬浮按钮的展示
        FloatingActionsMenu floatingMenu = findViewById(R.id.floating_menu);

        FloatingActionButton fabAction3 = findViewById(R.id.fabaction3);
        fabAction3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showPositionInputDialog();
            }
        });

    }

    @SuppressLint("MissingInflatedId")
    private void showPositionInputDialog() {
        // Inflate the dialog layout
        View dialogView = LayoutInflater.from(this).inflate(R.layout.text_navigation_input, null);
        //spinner适配器
        //spinner获取地址
        @SuppressLint({"MissingInflatedId", "LocalSuppress"}) Spinner searchBoxSpinner1 = dialogView.findViewById(R.id.spinnerStartLocation);
        @SuppressLint({"MissingInflatedId", "LocalSuppress"}) Spinner searchBoxSpinner2 = dialogView.findViewById(R.id.spinnerEndLocation);
        // 创建适配器并设置数据源
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.spinner_items, android.R.layout.simple_spinner_item);
        // 设置下拉框样式
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        // 绑定适配器到Spinner
        searchBoxSpinner1.setAdapter(adapter);
        searchBoxSpinner2.setAdapter(adapter);

        // Initialize views

        Button btnSubmit = dialogView.findViewById(R.id.buttonSubmit1);

        // Create and show the dialog
        androidx.appcompat.app.AlertDialog.Builder builder = new androidx.appcompat.app.AlertDialog.Builder(this);
        builder.setView(dialogView);
        final androidx.appcompat.app.AlertDialog dialog = builder.create();
        dialog.show();

        // Handle submit button click
        btnSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String start=(String) searchBoxSpinner1.getSelectedItem();
                String end = (String) searchBoxSpinner2.getSelectedItem();

                if (start.isEmpty()|| end.isEmpty()) {
                    Toast.makeText(NavigationActivity.this, "请输入您的起始和终止位置", Toast.LENGTH_SHORT).show();
                } else {
                    // Dismiss the dialog
                    dialog.dismiss();
//                    Toast.makeText(NavigationActivity.this, "准备出发，开始导航！", Toast.LENGTH_SHORT).show();
                    Toast.makeText(NavigationActivity.this, start+"到"+end, Toast.LENGTH_SHORT).show();
                   //开始导航展示信息
                    //&**********************************************************************************
                    int width = myLocation.getWidth();
                    int height = myLocation.getHeight();


                    myLocation.useNavigation=true;
                    myLocation.setTargetName(end);

                    myLocation.setbeginX(myLocation.getx());
                    myLocation.setbeginY(myLocation.gety());


                    myLocation.setNavigationType(2);
                    myLocation.setStartPosition(start,width,height);
                    myLocation.setTargetPosition(end,width,height);


                }
            }
        });
    }

    private void checkLocationPermission() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            // 显示解释弹窗
            if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.ACCESS_FINE_LOCATION)) {
                new AlertDialog.Builder(this)
                        .setTitle("需要位置权限")
                        .setMessage("应用需要获取您的位置权限以提供相关功能。")
                        .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                // 请求位置权限
                                ActivityCompat.requestPermissions(NavigationActivity.this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, LOCATION_PERMISSION_REQUEST_CODE);
                            }
                        })
                        .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                dialog.dismiss();
                            }
                        })
                        .create()
                        .show();
            } else {
                // 直接请求位置权限
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, LOCATION_PERMISSION_REQUEST_CODE);
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == LOCATION_PERMISSION_REQUEST_CODE) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                // 权限被授予
                // 在这里进行位置相关操作
            } else {
                // 权限被拒绝
                // 在这里处理权限被拒绝的情况
                new AlertDialog.Builder(this)
                        .setTitle("权限被拒绝")
                        .setMessage("应用需要位置权限才能正常工作。")
                        .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                dialog.dismiss();
                            }
                        })
                        .create()
                        .show();
            }
        }
    }



    protected void onDestroy() {
        super.onDestroy();
        // 在Activity销毁时停止WiFi扫描任务
        if (wifiScanTask != null) {
            wifiScanTask.stopScanTask();
        }
    }


}