package com.example.frontend;

import static android.graphics.BitmapFactory.decodeByteArray;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;
import static com.example.frontend.StaticRvAdapter.selectedPosition;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.alibaba.fastjson2.JSON;
import com.alibaba.fastjson2.JSONArray;
import com.example.frontend.DRVinterface.UpdateRecycleView;
import com.example.frontend.DRVinterface.UpdateRecycleView1;
import com.example.wifi_locate.Internet.Internet_Global;
import com.example.wifi_locate.Internet.MyCookieJar;
import com.example.wifi_locate.R;
import com.example.wifi_locate.ShopActivity;

import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.TimeUnit;

import okhttp3.Call;
import okhttp3.FormBody;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class StaticRvAdapter1 extends RecyclerView.Adapter<StaticRvAdapter1.StaticRVViewHolder> {


    private ArrayList<StaticRvModel> items;
    int row_index = -1;
    UpdateRecycleView1 updateRecycleView;
    Activity activity;
    boolean check = true;
    boolean select = true;
    private String TAG = "SR1";
    OkHttpClient okHttpClient;

    public StaticRvAdapter1(ArrayList<StaticRvModel> items, Activity activity, UpdateRecycleView1 updateRecycleView) {
        this.items = items;
        this.activity = activity;
        this.updateRecycleView = updateRecycleView;
        okHttpClient = new OkHttpClient.Builder()
                .cookieJar(new MyCookieJar())
                .build();
    }

    @NonNull
    @Override
    public StaticRVViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.static_rv_item, parent, false);
        StaticRVViewHolder staticRVViewHolder = new StaticRVViewHolder(view);
        return staticRVViewHolder;
    }

    @Override
    public void onBindViewHolder(@NonNull StaticRVViewHolder holder, @SuppressLint("RecyclerView") final int position) {
        StaticRvModel currentItems = items.get(position);
        holder.imageView.setImageResource(currentItems.getImage());
        holder.textView.setText(currentItems.getText());

        if (check) {


            Thread t1 = new Thread(new get_comments(position));
            t1.start();

        }

        holder.linearLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            //检查项目是否被选中
            public void onClick(View view) {
                row_index = position;
                notifyDataSetChanged();
//                ArrayList<DynamicRVModel> items = new ArrayList<DynamicRVModel>();
//                updateRecycleView.callback1(position, items);
                check = false;

                Thread t1 = new Thread(new get_comments(position));
                t1.start();

            }
        });

        if (select) {
            if (position == 0) {

                holder.linearLayout.setBackgroundResource(R.drawable.static_rv_selected_bg);
            }
            select = false;

        } else {
            //根据是否被选中更换其背景
            if (row_index == position) {
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

    public static class StaticRVViewHolder extends RecyclerView.ViewHolder {
        TextView textView;
        ImageView imageView;

        LinearLayout linearLayout;

        public StaticRVViewHolder(@NonNull View itemView) {
            super(itemView);
            imageView = itemView.findViewById(R.id.image1);
            textView = itemView.findViewById(R.id.text1);
            linearLayout = itemView.findViewById(R.id.linearLayout);
        }
    }

    private class get_comments implements Runnable {
        int position;

        public get_comments(int position) {
            this.position = position;
        }

        @Override
        public void run() {
            Response response = null;


            try {
                Log.d(TAG, "发送请求");

                //2.获取request对象
                RequestBody requestBody = new FormBody.Builder().add("sid", String.valueOf(position)).build();
                Request request = new Request.Builder()
                        .url(Internet_Global.Root + "/get_comment")
                        .post(requestBody)
                        .build();

                //3.获取call对象
                Call call = okHttpClient.newCall(request);
                //4.执行网络操作（同步）
                //同步执行网络操作
                response = call.execute();

                String result = response.body().string();
                Log.d(TAG, "run: "+result);
                JSONArray jsonArray = JSON.parseArray(result);

//                Log.d(TAG, "JSONArray is=" + jsonArray.toString());
//                ArrayList<DynamicRVModel> items = new ArrayList<DynamicRVModel>();

                StringBuilder sb = new StringBuilder();

                ArrayList<DynamicRVModel_for_comment> comments = new ArrayList<DynamicRVModel_for_comment>();

                for (int i = 0; i < jsonArray.size(); i++) {
//                    Log.d(TAG, "JSONObject" + i);
                    com.alibaba.fastjson2.JSONObject obj = jsonArray.getJSONObject(i);
//                    Log.d(TAG, obj.toString());
                    String name = obj.getString("name");
                    String comment = obj.getString("comment");
                    String stars = obj.getString("stars");
                    String uid=obj.getString("uid");

                    comments.add(new DynamicRVModel_for_comment(name, comment, get_user_ic(Integer.parseInt(uid)), Float.parseFloat(stars)));
                }
                Log.d(TAG, sb.toString());
                updateRecycleView.callback1(position, comments);
                check = false;

            } catch (Exception e) {
                ArrayList<DynamicRVModel_for_comment> comments = new ArrayList<>();
                comments.add(new DynamicRVModel_for_comment("网络错误", "", Bitmap.createBitmap(256, 256, Bitmap.Config.ARGB_8888), 0f));
                updateRecycleView.callback1(position, comments);
                check = false;
                Log.d(TAG, "网络请求失败" + e.getMessage() + Arrays.toString(e.getStackTrace()));
//                MakeToast("网络请求失败:" + e.getMessage());
            } finally {
                if (response != null) response.close();
                Log.d(TAG, "finish");
            }

        }

        private Bitmap get_user_ic(int uid) {

            Response response = null;
            InputStream is = null;
            ByteArrayOutputStream baos = null;
            Bitmap bitmap = null;
            try {
                OkHttpClient okHttpClient = new OkHttpClient
                        .Builder().cookieJar(new MyCookieJar()).connectTimeout(10, TimeUnit.SECONDS).build();
                List<Integer> id_list = new ArrayList<>();
                id_list.add(uid);
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
                // 在主线程更新 UI
            } catch (IOException e) {
                Log.d(TAG, e.getMessage());
                Log.e(TAG, "get_the_image: ", e);
            } catch (Exception e) {
                Log.e(TAG, "get_image_test: ", e);
            } finally {
                try {
                    if (response != null) response.close();
                    if (is != null) is.close();
                    if (baos != null) baos.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }

            if (bitmap != null)
                return bitmap;
            else return  Bitmap.createBitmap(256, 256, Bitmap.Config.ARGB_8888);

        }


    }

}
