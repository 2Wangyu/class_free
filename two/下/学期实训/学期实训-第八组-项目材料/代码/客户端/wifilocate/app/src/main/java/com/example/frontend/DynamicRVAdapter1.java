package com.example.frontend;


import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RatingBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.RecyclerView;

import com.example.wifi_locate.R;

import java.util.ArrayList;

public class DynamicRVAdapter1 extends RecyclerView.Adapter<DynamicRVAdapter1.DynamicRvHolder> {
    //创建数组列表
    public ArrayList<DynamicRVModel_for_comment> dynamicRVModels_for_comment;

    //

    public DynamicRVAdapter1(ArrayList<DynamicRVModel_for_comment> dynamicRVModels){
        this.dynamicRVModels_for_comment=dynamicRVModels;
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
            imageView=itemView.findViewById(R.id.image2user);
            textView=itemView.findViewById(R.id.name1userId);
            //新增的
            textView1=itemView.findViewById(R.id.detailsuser);
            ratingBar=itemView.findViewById(R.id.ratingbaruser);
            constraintLayout=itemView.findViewById(R.id.constraintLayoutuser);
        }

        public ImageView getImageView() {
            return imageView;
        }
    }

    @NonNull
    @Override
    public DynamicRVAdapter1.DynamicRvHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view=LayoutInflater.from(parent.getContext()).inflate(R.layout.dynamic_rv_item_layout_rating,parent,false);
        DynamicRvHolder dynamicRvHolder=new DynamicRvHolder(view);
        return dynamicRvHolder;

    }

    @Override
    public void onBindViewHolder(@NonNull DynamicRVAdapter1.DynamicRvHolder holder, int position) {
        //单击改变图像
        DynamicRVModel_for_comment currentItems=dynamicRVModels_for_comment.get(position);
        holder.imageView.setImageBitmap(currentItems.getImage());
        holder.textView.setText(currentItems.getName());
        //新增的
        holder.textView1.setText(currentItems.getName1());
        holder.ratingBar.setRating(currentItems.getRatingbar());
    }
    @Override
    public int getItemCount() {
        return dynamicRVModels_for_comment.size();
    }
    
}








