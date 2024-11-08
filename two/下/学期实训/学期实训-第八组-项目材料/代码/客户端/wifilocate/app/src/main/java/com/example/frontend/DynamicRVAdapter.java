package com.example.frontend;


import android.app.Activity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.RatingBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.frontend.DRVinterface.LoadMore;
import com.example.wifi_locate.R;

import java.util.ArrayList;
import java.util.List;

public class DynamicRVAdapter extends RecyclerView.Adapter<DynamicRVAdapter.DynamicRvHolder> {
    //创建数组列表
    public ArrayList<DynamicRVModel> dynamicRVModels;

    //
    public DynamicRVAdapter(ArrayList<DynamicRVModel> dynamicRVModels){
        this.dynamicRVModels=dynamicRVModels;
    }

    public class DynamicRvHolder extends RecyclerView.ViewHolder{
        //与相应的视图联系起来
        public ImageView imageView;
        public TextView textView;
        public TextView textView1;
        public RatingBar ratingBar;
        ConstraintLayout constraintLayout;


        public DynamicRvHolder(@NonNull View itemView) {
            super(itemView);
            imageView=itemView.findViewById(R.id.image2);
            textView=itemView.findViewById(R.id.name1);

            //新增的
            textView1=itemView.findViewById(R.id.details);
            ratingBar=itemView.findViewById(R.id.ratingbar);


            constraintLayout=itemView.findViewById(R.id.constraintLayout);


        }
    }

    @NonNull
    @Override
    public DynamicRVAdapter.DynamicRvHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view=LayoutInflater.from(parent.getContext()).inflate(R.layout.dynamic_rv_item_layout,parent,false);
        DynamicRvHolder dynamicRvHolder=new DynamicRvHolder(view);
        return dynamicRvHolder;

    }

    @Override
    public void onBindViewHolder(@NonNull DynamicRVAdapter.DynamicRvHolder holder, int position) {


        //单击改变图像
        DynamicRVModel currentItems=dynamicRVModels.get(position);
        holder.imageView.setImageResource(currentItems.getImage());
        holder.textView.setText(currentItems.getName());

        //新增的
        holder.textView1.setText(currentItems.getName1());
        holder.ratingBar.setRating(currentItems.getRatingbar());


    }

    @Override
    public int getItemCount() {
        return dynamicRVModels.size();
    }



}









