package com.example.wifi_locate;

import static android.content.Intent.FLAG_ACTIVITY_CLEAR_TASK;
import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.RatingBar;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.frontend.DRVinterface.UpdateRecycleView;
import com.example.frontend.DRVinterface.UpdateRecycleView1;
import com.example.frontend.DynamicRVAdapter;
import com.example.frontend.DynamicRVAdapter1;
import com.example.frontend.DynamicRVModel;
import com.example.frontend.DynamicRVModel_for_comment;
import com.example.frontend.StaticRvAdapter;
import com.example.frontend.StaticRvAdapter1;
import com.example.frontend.StaticRvModel;
import com.getbase.floatingactionbutton.FloatingActionButton;
import com.google.android.material.bottomnavigation.BottomNavigationView;

import java.util.ArrayList;

public class ProfileActivity extends AppCompatActivity implements UpdateRecycleView1{

    private FloatingActionButton fabAction1;
    private RatingBar ratingBar;
    private EditText etComment;
    private RecyclerView recyclerView,recyclerView2;
    private StaticRvAdapter1 staticRvAdapter;

    ArrayList<DynamicRVModel> items=new ArrayList<>();
    DynamicRVAdapter1 dynamicRVAdapter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_profile);

//        //底部导航栏
//        BottomNavigationView bottomNavigationView = findViewById(R.id.bottomnavigation);
//        bottomNavigationView.setSelectedItemId(R.id.navigationreviews);
//
//        bottomNavigationView.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
//            @SuppressLint("NonConstantResourceId")
//            @Override
//            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
//                if(item.getItemId()==R.id.navigationhome) {
//                    Intent intent=new Intent(new Intent(ProfileActivity.this, HomePage4Activity.class));
//                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
//                    startActivity(intent);
//
//                    return true;
//                }
//                else if(item.getItemId()==R.id.navigationshop) {
//
//                    Intent intent=new Intent(new Intent(ProfileActivity.this, ShopActivity.class));
//                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
//                    startActivity(intent);
//                    return true;
//                }
//                else if(item.getItemId()==R.id.navigationnavigation) {
//
//                    Intent intent=new Intent(new Intent(ProfileActivity.this, NavigationActivity.class));
//                    intent.setFlags(FLAG_ACTIVITY_CLEAR_TASK | FLAG_ACTIVITY_NEW_TASK);
//                    startActivity(intent);
//                    return true;
//                }
//                else if (item.getItemId()==R.id.navigationreviews) {
//
//                    return true;
//                }
//                else return false;
//            }
//        });


        //循环视图的展示
        final ArrayList<StaticRvModel> item=new ArrayList<>();
        item.add(new StaticRvModel(R.mipmap.canteen2,"金山城"));
        item.add(new StaticRvModel(R.mipmap.k,"kumo"));
        item.add(new StaticRvModel(R.mipmap.x,"喜茶"));
        item.add(new StaticRvModel(R.mipmap.canteen5,"鲜牛记"));
        item.add(new StaticRvModel(R.mipmap.m,"满记甜品"));
        item.add(new StaticRvModel(R.mipmap.c,"奈雪的茶"));
        recyclerView=findViewById(R.id.recyclerview3);
        staticRvAdapter=new StaticRvAdapter1(item,this, (UpdateRecycleView1) this);
        recyclerView.setLayoutManager(new LinearLayoutManager(this,LinearLayoutManager.HORIZONTAL,false));
        recyclerView.setAdapter(staticRvAdapter);
        //下方的食物展示
        items =new ArrayList<>();
        recyclerView2=findViewById(R.id.recyclerview4);
        dynamicRVAdapter=new DynamicRVAdapter1(new ArrayList<>());
        recyclerView2.setLayoutManager(new LinearLayoutManager(this,LinearLayoutManager.VERTICAL,false));
        recyclerView2.setAdapter(dynamicRVAdapter);




    }

//    @Override
//    public  void callback1(int position, ArrayList<DynamicRVModel> items) {
//        runOnUiThread(new Runnable() {
//            @Override
//            public void run() {
//                dynamicRVAdapter=new DynamicRVAdapter1(items);
//                dynamicRVAdapter.notifyDataSetChanged();
//                recyclerView2.setAdapter(dynamicRVAdapter);
//            }
//        });
//
//    }
    @Override
    public void callback1(int position, ArrayList<DynamicRVModel_for_comment> items) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                dynamicRVAdapter=new DynamicRVAdapter1(items);
                dynamicRVAdapter.notifyDataSetChanged();
                recyclerView2.setAdapter(dynamicRVAdapter);
            }
        });

    }


}