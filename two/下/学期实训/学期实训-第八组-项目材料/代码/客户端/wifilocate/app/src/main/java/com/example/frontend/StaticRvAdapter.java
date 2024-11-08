package com.example.frontend;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.frontend.DRVinterface.UpdateRecycleView;
import com.example.wifi_locate.R;

import java.util.ArrayList;

public class StaticRvAdapter extends RecyclerView.Adapter<StaticRvAdapter.StaticRVViewHolder>{


    private ArrayList<StaticRvModel> items;
    int row_index=-1;
    UpdateRecycleView updateRecycleView;
    Activity activity;
    boolean check=true;
    boolean select=true;
    public static int selectedPosition = -1; // 初始化为-1表示没有选中项



    public StaticRvAdapter(ArrayList<StaticRvModel> items,  Activity activity,UpdateRecycleView  updateRecycleView) {

        this.items = items;
        this.activity= (Activity) activity;
        this.updateRecycleView= (UpdateRecycleView) updateRecycleView;
    }

    @NonNull
    @Override
    public StaticRVViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view= LayoutInflater.from(parent.getContext()).inflate(R.layout.static_rv_item,parent,false);
        StaticRVViewHolder staticRVViewHolder=new StaticRVViewHolder(view);
        return staticRVViewHolder;
    }

    @Override
    public void onBindViewHolder(@NonNull StaticRVViewHolder holder, @SuppressLint("RecyclerView") final int position) {
        StaticRvModel currentItems=items.get(position);
        holder.imageView.setImageResource(currentItems.getImage());
        holder.textView.setText(currentItems.getText());
        if(check){
            //金山城
            selectedPosition=0;
            ArrayList<DynamicRVModel> items=new ArrayList<DynamicRVModel>();
            items.add(new DynamicRVModel("1 虾汤过桥东星斑","鲜香可口、新鲜现做、东星斑",R.mipmap.eaten21,4.8f));
            items.add(new DynamicRVModel("2 云南普洱熏乳鸽","回味无穷、新鲜现做、小青龙",R.mipmap.eaten22,4.0f));
            items.add(new DynamicRVModel("3 团圆八珍锅","独家秘制、新鲜现做、八珍锅",R.mipmap.eaten23,3.5f));
            items.add(new DynamicRVModel("4 云南普洱熏乳鸽","层次丰富、新鲜现做、乳鸽",R.mipmap.eaten24,3.9f));
            items.add(new DynamicRVModel("5 牛气冲天","独家秘制、精制卤味、黄牛",R.mipmap.eaten25,4.9f));
            items.add(new DynamicRVModel("6 江南花雕鸡","回味无穷、精制卤味、花雕鸡",R.mipmap.eaten26,4.5f));
            items.add(new DynamicRVModel("7 金汤肥牛","口感丰富、新鲜现做、肥牛",R.mipmap.eaten27,4.1f));
            items.add(new DynamicRVModel("8 葱爆羊肉","独家秘制、新鲜现做、羊肉",R.mipmap.eaten28,4.8f));
            updateRecycleView.callback(position,items);
            check=false;
        }

        holder.linearLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            //检查项目是否被选中
            public void onClick(View view) {
                row_index=position;
                notifyDataSetChanged();
                //根据位置修改食品列表数据
                if(position==0){
                    selectedPosition=0;
//     金山城
                    ArrayList<DynamicRVModel> items=new ArrayList<DynamicRVModel>();
                    items.add(new DynamicRVModel("1 虾汤过桥东星斑","鲜香可口、新鲜现做、东星斑",R.mipmap.eaten21,4.8f));
                    items.add(new DynamicRVModel("2 云南普洱熏乳鸽","回味无穷、新鲜现做、小青龙",R.mipmap.eaten22,4.0f));
                    items.add(new DynamicRVModel("3 团圆八珍锅","独家秘制、新鲜现做、八珍锅",R.mipmap.eaten23,3.5f));
                    items.add(new DynamicRVModel("4 云南普洱熏乳鸽","层次丰富、新鲜现做、乳鸽",R.mipmap.eaten24,3.9f));
                    items.add(new DynamicRVModel("5 牛气冲天","独家秘制、精制卤味、黄牛",R.mipmap.eaten25,4.9f));
                    items.add(new DynamicRVModel("6 江南花雕鸡","回味无穷、精制卤味、花雕鸡",R.mipmap.eaten26,4.5f));
                    items.add(new DynamicRVModel("7 金汤肥牛","口感丰富、新鲜现做、肥牛",R.mipmap.eaten27,4.1f));
                    items.add(new DynamicRVModel("8 葱爆羊肉","独家秘制、新鲜现做、羊肉",R.mipmap.eaten28,4.8f));
                    updateRecycleView.callback(position,items);
                    check=false;

                } else if (position==1) {
                    //kumokumo
                    selectedPosition=1;
                    ArrayList<DynamicRVModel> items=new ArrayList<DynamicRVModel>();
                    items.add(new DynamicRVModel("1 上海酒酿巴斯克蛋糕","层次丰富、精心烘焙、芝士",R.mipmap.k1,4.9f));
                    items.add(new DynamicRVModel("2 咸蛋黄芝士蛋糕","层次丰富、手工制作、咸蛋黄",R.mipmap.k2,4.1f));
                    items.add(new DynamicRVModel("3 巧克力芝士厚乳可颂挞","层次丰富、精心烘焙、巧克力",R.mipmap.k3,4.1f));
                    items.add(new DynamicRVModel("4 香芋巴斯克蛋糕","层次丰富、精心烘焙、芝士",R.mipmap.k4,3.9f));
                    items.add(new DynamicRVModel("5 草莓芝士厚乳可颂挞","层次丰富、精心烘焙、草莓",R.mipmap.k5,4.2f));
                    items.add(new DynamicRVModel("6 原味芝士布丁烧","奶香浓郁、手工制作、芝士",R.mipmap.k6,4.9f));
                    items.add(new DynamicRVModel("7 软心芝士巴斯克蛋糕","入口即化、精心烘焙、芝士",R.mipmap.k7,4.8f));
                    items.add(new DynamicRVModel("8 芝士小脆","奶香浓郁、酥脆可口、芝士",R.mipmap.k8,4.0f));
                    updateRecycleView.callback(position,items);
                    check=false;


                } else if (position==2) {

                    //喜茶
                    selectedPosition=2;
                    ArrayList<DynamicRVModel> items=new ArrayList<DynamicRVModel>();
                    items.add(new DynamicRVModel("1 小奶茉","鲜醇白茉、手工制作、生牛乳",R.mipmap.x1,4.8f));
                    items.add(new DynamicRVModel("2 绿妍轻柠茶","酸甜沁爽、手工制作、新鲜柠檬",R.mipmap.x2,4.0f));
                    items.add(new DynamicRVModel("3 轻芝多肉葡萄","肉质鲜嫩、手工制作、夏黑葡萄",R.mipmap.x3,3.5f));
                    items.add(new DynamicRVModel("4 椰椰芒芒","浓郁爽口、手工制作、鲜芒果",R.mipmap.x4,3.9f));
                    items.add(new DynamicRVModel("5 鸭喜香轻柠茶","清凉爽口、手工制作、真果柠檬",R.mipmap.x5,4.9f));
                    items.add(new DynamicRVModel("6 烤黑糖波波真乳茶","软糯Q弹、手工制作、真牛乳",R.mipmap.x6,4.5f));
                    items.add(new DynamicRVModel("7 多肉桃李","清凉爽口、手工制作、时令鲜果",R.mipmap.x7,4.1f));
                    items.add(new DynamicRVModel("8 多肉葡萄","脆爽嫩滑、手工制作、夏黑葡萄",R.mipmap.x8,4.8f));
                    updateRecycleView.callback(position,items);
                    check=false;



                } else if (position==3) {

                    selectedPosition=3;
                    ArrayList<DynamicRVModel> items=new ArrayList<DynamicRVModel>();
                    items.add(new DynamicRVModel("1 匙仁","肉质细腻、手工制作、牛肉",R.mipmap.eaten51,4.6f));
                    items.add(new DynamicRVModel("2 大叶毛肚","口感丰富、新鲜现做，鲜毛肚",R.mipmap.eaten52,4.1f));
                    items.add(new DynamicRVModel("3 鲜打牛肉丸","肉质细腻、手工制作、牛肉",R.mipmap.eaten53,4.5f));
                    items.add(new DynamicRVModel("4 吊龙","肉质细腻、手工制作、牛肉",R.mipmap.eaten54,3.9f));
                    items.add(new DynamicRVModel("5 匙柄","新鲜美味、正宗涮锅、匙柄",R.mipmap.eaten55,4.8f));
                    items.add(new DynamicRVModel("6 牛腩","新鲜美味、正宗涮锅、牛腩",R.mipmap.eaten56,4.1f));
                    items.add(new DynamicRVModel("7 菌菇拼盘","新鲜美味、正宗涮锅、新鲜菌类",R.mipmap.eaten57,4.2f));
                    items.add(new DynamicRVModel("8 牛舌","新鲜美味、正宗涮锅、牛舌",R.mipmap.eaten58,4.8f));
                    updateRecycleView.callback(position,items);
                    check=false;
                } else if (position==4) {

                    //满记甜品
                    selectedPosition=4;
                    ArrayList<DynamicRVModel> items=new ArrayList<DynamicRVModel>();
                    items.add(new DynamicRVModel("1 生磨杏仁茶汤丸","新鲜美味、手工制作、茶汤丸",R.mipmap.m1,4.6f));
                    items.add(new DynamicRVModel("2 莲子红豆沙","新鲜美味、手工制作、莲子豆沙",R.mipmap.m2,4.1f));
                    items.add(new DynamicRVModel("3 海底椰西米露","新鲜美味、手工制作、西米露",R.mipmap.m3,4.5f));
                    items.add(new DynamicRVModel("4 芒果西米露","新鲜美味、手工制作、西米露",R.mipmap.m4,3.9f));
                    items.add(new DynamicRVModel("5 雪山蓝莓","新鲜美味、手工制作、蓝莓",R.mipmap.m5,4.2f));
                    items.add(new DynamicRVModel("6 榴莲班戟","新鲜美味、手工制作、榴莲",R.mipmap.m6,4.9f));
                    items.add(new DynamicRVModel("7 芒果白雪黑糯米","新鲜美味、手工制作、芒果糯米",R.mipmap.m7,4.7f));
                    items.add(new DynamicRVModel("8 杨枝甘露","新鲜美味、手工制作、芒果",R.mipmap.m8,4.4f));
                    updateRecycleView.callback(position,items);
                    check=false;
                }else if (position==5) {
                    //茶甜度适中、手工制作、新鲜水果
                    ArrayList<DynamicRVModel> items=new ArrayList<DynamicRVModel>();
                    items.add(new DynamicRVModel("1 霸气香水橙子","甜度适中、手工制作、新鲜水果",R.mipmap.c1,4.6f));
                    items.add(new DynamicRVModel("2 香水大红袍鲜奶茶","奶香浓郁、手工制作、大红袍",R.mipmap.c2,4.1f));
                    items.add(new DynamicRVModel("3 香水茉莉初雪奶茶","奶香浓郁、手工制作、茉莉初雪",R.mipmap.c3,4.5f));
                    items.add(new DynamicRVModel("4 霸气香水西柚","酸甜适中、手工制作、新鲜水果",R.mipmap.c4,3.9f));
                    items.add(new DynamicRVModel("5 霸气香水柠檬油柑","酸甜适中、手工制作、新鲜水果",R.mipmap.c5,4.2f));
                    items.add(new DynamicRVModel("6 霸气香水葡萄","酸甜适中、手工制作、新鲜水果",R.mipmap.c6,4.9f));
                    items.add(new DynamicRVModel("7 霸气香水芝士草莓","酸甜适中、手工制作、新鲜水果",R.mipmap.c7,4.7f));
                    items.add(new DynamicRVModel("8 霸气桂花生椰龙眼","冷热皆可、手工制作、酒酿龙眼",R.mipmap.c8,4.4f));
                    updateRecycleView.callback(position,items);
                    check=false;

                }
            }
        });

        if(select){
            if(position==0){
                holder.linearLayout.setBackgroundResource(R.drawable.static_rv_selected_bg);
            }
            select=false;

        }
        else {
            //根据是否被选中更换其背景
            if(row_index==position) {
                holder.linearLayout.setBackgroundResource(R.drawable.static_rv_selected_bg);
            } else {
                holder.linearLayout.setBackgroundResource(R.drawable.static_rv_bg);

            }

        }

    }

    @Override
    public int getItemCount() {
        return items.size();
    }

    public static class StaticRVViewHolder extends RecyclerView.ViewHolder{
            TextView textView;
            ImageView  imageView;

            LinearLayout linearLayout;

            public StaticRVViewHolder(@NonNull View itemView){
               super(itemView);
               imageView=itemView.findViewById(R.id.image1);
               textView=itemView.findViewById(R.id.text1);
               linearLayout=itemView.findViewById(R.id.linearLayout);



            }

        }

}
