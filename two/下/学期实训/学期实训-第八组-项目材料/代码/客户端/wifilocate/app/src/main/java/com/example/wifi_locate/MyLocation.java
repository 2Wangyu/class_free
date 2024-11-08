package com.example.wifi_locate;
import java.util.HashMap;
import java.util.Iterator;
import org.json.JSONException;

import android.util.Pair;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import org.json.JSONObject;

import android.graphics.Path;
import android.graphics.drawable.Drawable;
import androidx.core.content.ContextCompat;

import android.content.SharedPreferences;

public class MyLocation extends View {
    private Paint paint;
    private float x = -1;
    private float y = -1;
    private float beginX = -1;
    private float beginY = -1;
    public float startX=-1;
    public float startY=-1;
    public float targetX=-1;
    public float targetY=-1;
    private  int screenWidth;
    private  int screenHeight;
    private Drawable drawable;
    private static final String TAG = "MyLocation";
    HashMap<String, Pair<Float, Float>> coordinateMap = new HashMap<>();
    public boolean useNavigation=false;
    private Path path;
    private float arrowSize = 41; // 箭头大小
    Pair<Float, Float> coord;
    private int navigationType=-1;
    private int nearby=-1;
    private int width2;
    private int height2;

    private int dotRadius = 20; // 点的半径
    private int dotColor = Color.RED;
    private float dotX, dotY; // 点的中心坐标
    private SharedPreferences sharedPreferences;
    private String username;
    private String targetName;
    private String positionName;



    public MyLocation(Context context) {
        super(context);
        init(context);
    }






    public MyLocation(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);

    }

    public MyLocation(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);

    }
    public void setNearby(int x){
        nearby=x;
    }
    public void setNavigationType(int x){
        this.navigationType=x;
    }
    public int getNavigationType(){
        return this.navigationType;
    }

    public void setPositionName(String positionName) {
        this.positionName = positionName;
    }

    public void setTargetName(String targetName) {
        this.targetName = targetName;
    }
    public String getTargetName(){
        return this.targetName;
    }

    public float getx(){
        return x;
    }
    public float gety(){
        return y;
    }
    public void setbeginX(float x){
        this.beginX =x;
    }
    public void setbeginY(float y){
        this.beginY =y;
    }

    private void init(Context context) {
        paint = new Paint();
        path= new Path();
        paint.setColor(Color.RED);
        paint.setStyle(Paint.Style.FILL);
        drawable = ContextCompat.getDrawable(context, R.drawable.baseline_edit_location_24);
        sharedPreferences = context.getSharedPreferences("account", Context.MODE_PRIVATE);


         username = sharedPreferences.getString("username", "defaultUsername");
        //Log.e(TAG,"username"+username);

//         sharedPreferences = getSharedPreferences("account", Context.MODE_PRIVATE);
//        String valueString = sharedPreferences.getString("key_string", "default_value");
//        int valueInt = sharedPreferences.getInt("key_int", 0);
//        boolean valueBoolean = sharedPreferences.getBoolean("key_boolean", false);


        coordinateMap.put("1.1", new Pair<>(0.5f,0.97f ));
        coordinateMap.put("1.2", new Pair<>(0.4f,0.72f ));
        coordinateMap.put("1.3", new Pair<>(0.5f,0.87f ));
        coordinateMap.put("1.4", new Pair<>(0.5f,0.79f ));
        coordinateMap.put("1.5", new Pair<>(0.5f,0.71f ));
        coordinateMap.put("1.6", new Pair<>(0.4f,0.63f ));
        coordinateMap.put("1.7", new Pair<>(0.5f,0.63f ));
        coordinateMap.put("1.8", new Pair<>(0.5f,0.54f ));
        coordinateMap.put("1.9", new Pair<>(0.5f,0.45f ));
        coordinateMap.put("1.11", new Pair<>(0.5f,0.38f ));
        coordinateMap.put("1.12", new Pair<>(0.5f, 0.30f));
        coordinateMap.put("1.13", new Pair<>(0.5f,0.22f ));
        coordinateMap.put("1.14", new Pair<>(0.5f,0.14f ));
        coordinateMap.put("1.15", new Pair<>(0.5f,0.06f ));
        coordinateMap.put("401", new Pair<>(0.4f,0.96f ));
        coordinateMap.put("满记甜品", new Pair<>(0.4f,0.96f ));

        coordinateMap.put("402", new Pair<>(0.4f,0.55f ));
        coordinateMap.put("喜茶", new Pair<>(0.4f,0.55f ));

        coordinateMap.put("403", new Pair<>(0.4f,0.38f ));
        coordinateMap.put("奈雪的茶", new Pair<>(0.4f,0.38f ));

        coordinateMap.put("413", new Pair<>(0.6f,0.21f ));
        coordinateMap.put("金山城", new Pair<>(0.6f,0.21f ));

        coordinateMap.put("414", new Pair<>(0.6f,0.61f ));
        coordinateMap.put("鲜牛记", new Pair<>(0.6f,0.61f ));

        coordinateMap.put("415", new Pair<>(0.66f,0.80f ));
        coordinateMap.put("KumoKumo", new Pair<>(0.66f,0.80f ));






    }

    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

       // Log.e(TAG, "进入前");
        //Log.e(TAG, "x=" + x + "y=" + y + "  targetx=" + targetX + "targety=" + targetY);


        if(x!=-1&&y!=-1) {

            //自身位置与目标位置导航
            if (navigationType == 1) {


                if (useNavigation == true && !(x == targetX && y == targetY)) {
                    Log.e(TAG, "进入");
                    Paint paint = new Paint();
                    paint.setColor(Color.RED); // 设置线条颜色
                    paint.setStrokeWidth(5); // 设置线条宽度
                    paint.setStyle(Paint.Style.STROKE); // 实线样式
                    paint.setAntiAlias(true);
                    float startx1=-1;
                    float starty1=-1 ;
                    float endx1=-1 ;
                    float endy1=-1 ;

                    switch (positionName){
                        case  "KumoKumo":
                            startx1 = 0.66f*screenWidth;
                            starty1 = 0.80f*screenHeight;
                            endx1 = 0.5f * screenWidth;
                            endy1 =0.80f*screenHeight;
                            if(targetX==startx1&&targetY==starty1){
                                return;
                            }
                            break;
                        case  "鲜牛记":
                            startx1 = 0.620f*screenWidth;
                            starty1 = 0.61f*screenHeight;
                            endx1 = 0.5f * screenWidth;
                            endy1 =0.61f*screenHeight;
                            break;
                        case  "金山城":
                            startx1 = 0.62f*screenWidth;
                            starty1 = 0.21f*screenHeight;
                            endx1 = 0.5f * screenWidth;
                            endy1 =0.21f*screenHeight;
                            break;
                        case  "奈雪的茶":
                            startx1 = 0.4f*screenWidth;
                            starty1 = 0.38f*screenHeight;
                            endx1 = 0.5f * screenWidth;
                            endy1 =0.38f*screenHeight;
                            break;
                        case  "喜茶":
                            startx1 = 0.4f*screenWidth;
                            starty1 = 0.55f*screenHeight;
                            endx1 = 0.5f * screenWidth;
                            endy1 =0.55f*screenHeight;
                            break;
                        case  "满记甜品":
                            startx1 = 0.4f*screenWidth;
                            starty1 = 0.96f*screenHeight;
                            endx1 = 0.5f * screenWidth;
                            endy1 =0.96f*screenHeight;
                            break;
                        default:
                            startx1 = x;
                            starty1 = y;
                            endx1 = 0.5f * screenWidth;
                            endy1 = y;
                    }

                    // 定义线条的起点和终点坐标

                    float startx2 = endx1;
                    float starty2 = endy1;
                    float endx2 = endx1;
                    float endy2 = targetY;

                    float startx3 = endx2;
                    float starty3 = endy2;
                    float endx3 = targetX;
                    float endy3 = targetY;


                    //目标在走廊两侧
                    if (targetX != 0.5 * screenWidth && x != 0.5 * screenWidth) {


                        if (path != null) {
                            path.reset();
                            // 继续进行路径的绘制等操作
                        }
                        path.moveTo(startx1, starty1);
                        path.lineTo(endx1, endy1);

                        // 计算箭头
                        double angle1 = Math.atan2(endy1 - starty1, endx1 - startx1);
                        double arrowAngle1 = Math.PI / 6; // 箭头夹角
                        float arrowX1 = (float) (endx1 - arrowSize * Math.cos(angle1 + arrowAngle1));
                        float arrowY1 = (float) (endy1 - arrowSize * Math.sin(angle1 + arrowAngle1));
                        float arrowX2 = (float) (endx1 - arrowSize * Math.cos(angle1 - arrowAngle1));
                        float arrowY2 = (float) (endy1 - arrowSize * Math.sin(angle1 - arrowAngle1));

                        canvas.drawPath(path, paint); // 绘制路径

                        //绘制箭头
                        path.moveTo(endx1, endy1);
                        path.lineTo(arrowX1, arrowY1);
                        path.moveTo(endx1, endy1);
                        path.lineTo(arrowX2, arrowY2);

                        canvas.drawPath(path, paint); // 绘制箭头


                        if (path != null) {
                            path.reset();
                            // 继续进行路径的绘制等操作
                        }
                        path.moveTo(startx2, starty2);
                        path.lineTo(endx2, endy2);

                        // 计算箭头
                        double angle2 = Math.atan2(endy2 - starty2, endx2 - startx2);
                        double arrowAngle2 = Math.PI / 6; // 箭头夹角
                        arrowX1 = (float) (endx2 - arrowSize * Math.cos(angle2 + arrowAngle2));
                        arrowY1 = (float) (endy2 - arrowSize * Math.sin(angle2 + arrowAngle2));
                        arrowX2 = (float) (endx2 - arrowSize * Math.cos(angle2 - arrowAngle2));
                        arrowY2 = (float) (endy2 - arrowSize * Math.sin(angle2 - arrowAngle2));

                        canvas.drawPath(path, paint); // 绘制路径

                        //绘制箭头
                        path.moveTo(endx2, endy2);
                        path.lineTo(arrowX1, arrowY1);
                        path.moveTo(endx2, endy2);
                        path.lineTo(arrowX2, arrowY2);

                        canvas.drawPath(path, paint); // 绘制箭头


                        if (path != null) {
                            path.reset();
                            // 继续进行路径的绘制等操作
                        }
                        path.moveTo(startx3, starty3);
                        path.lineTo(endx3, endy3);

                        // 计算箭头
                        double angle3 = Math.atan2(endy3 - starty3, endx3 - startx3);
                        double arrowAngle3 = Math.PI / 6; // 箭头夹角
                        arrowX1 = (float) (endx3 - arrowSize * Math.cos(angle3 + arrowAngle3));
                        arrowY1 = (float) (endy3 - arrowSize * Math.sin(angle3 + arrowAngle3));
                        arrowX2 = (float) (endx3 - arrowSize * Math.cos(angle3 - arrowAngle3));
                        arrowY2 = (float) (endy3 - arrowSize * Math.sin(angle3 - arrowAngle3));

                        canvas.drawPath(path, paint); // 绘制路径

                        //绘制箭头
                        path.moveTo(endx3, endy3);
                        path.lineTo(arrowX1, arrowY1);
                        path.moveTo(endx3, endy3);
                        path.lineTo(arrowX2, arrowY2);

                        canvas.drawPath(path, paint); // 绘制箭头


                        Log.e(TAG, "startx1=" + startx1 + ", starty1=" + starty1);
                        Log.e(TAG, "endx1=" + endx1 + ", endy1=" + endy1);
                        Log.e(TAG, "startx3=" + startx1 + ", starty3=" + starty3);
                        Log.e(TAG, "endx3=" + endx3 + ", endy3=" + endy3);


                    }

                    //起始点在走廊上
                    if (targetX == 0.5 * screenWidth || x == 0.5 * screenWidth) {
                        Log.e(TAG, "进入2");

                        if (path != null) {
                            path.reset();
                            // 继续进行路径的绘制等操作
                        }
                        path.moveTo(startx1, starty1);
                        path.lineTo(endx1, endy1);

                        // 计算箭头
                        double angle1 = Math.atan2(endy1 - starty1, endx1 - startx1);
                        double arrowAngle1 = Math.PI / 6; // 箭头夹角
                        float arrowX1 = (float) (endx1 - arrowSize * Math.cos(angle1 + arrowAngle1));
                        float arrowY1 = (float) (endy1 - arrowSize * Math.sin(angle1 + arrowAngle1));
                        float arrowX2 = (float) (endx1 - arrowSize * Math.cos(angle1 - arrowAngle1));
                        float arrowY2 = (float) (endy1 - arrowSize * Math.sin(angle1 - arrowAngle1));

                        //canvas.drawPath(path, paint); // 绘制路径

                        //绘制箭头
                        path.moveTo(endx1, endy1);
                        path.lineTo(arrowX1, arrowY1);
                        path.moveTo(endx1, endy1);
                        path.lineTo(arrowX2, arrowY2);

                        //canvas.drawPath(path, paint); // 绘制箭头


                        if (path != null) {
                            path.reset();
                            // 继续进行路径的绘制等操作
                        }
                        path.moveTo(startx2, starty2);
                        path.lineTo(endx2, endy2);

                        // 计算箭头
                        double angle2 = Math.atan2(endy2 - starty2, endx2 - startx2);
                        double arrowAngle2 = Math.PI / 6; // 箭头夹角
                        arrowX1 = (float) (endx2 - arrowSize * Math.cos(angle2 + arrowAngle2));
                        arrowY1 = (float) (endy2 - arrowSize * Math.sin(angle2 + arrowAngle2));
                        arrowX2 = (float) (endx2 - arrowSize * Math.cos(angle2 - arrowAngle2));
                        arrowY2 = (float) (endy2 - arrowSize * Math.sin(angle2 - arrowAngle2));

                        canvas.drawPath(path, paint); // 绘制路径

                        //绘制箭头
                        path.moveTo(endx2, endy2);
                        path.lineTo(arrowX1, arrowY1);
                        path.moveTo(endx2, endy2);
                        path.lineTo(arrowX2, arrowY2);

                        canvas.drawPath(path, paint); // 绘制箭头


                        if (path != null) {
                            path.reset();
                            // 继续进行路径的绘制等操作
                        }
                        path.moveTo(startx3, starty3);
                        path.lineTo(endx3, endy3);

                        // 计算箭头
                        double angle3 = Math.atan2(endy3 - starty3, endx3 - startx3);
                        double arrowAngle3 = Math.PI / 6; // 箭头夹角
                        arrowX1 = (float) (endx3 - arrowSize * Math.cos(angle3 + arrowAngle3));
                        arrowY1 = (float) (endy3 - arrowSize * Math.sin(angle3 + arrowAngle3));
                        arrowX2 = (float) (endx3 - arrowSize * Math.cos(angle3 - arrowAngle3));
                        arrowY2 = (float) (endy3 - arrowSize * Math.sin(angle3 - arrowAngle3));

                        canvas.drawPath(path, paint); // 绘制路径

                        //绘制箭头
                        path.moveTo(endx3, endy3);
                        path.lineTo(arrowX1, arrowY1);
                        path.moveTo(endx3, endy3);
                        path.lineTo(arrowX2, arrowY2);

                        canvas.drawPath(path, paint); // 绘制箭头


                        Log.e(TAG, "startx1=" + startx1 + ", starty1=" + starty1);
                        Log.e(TAG, "endx1=" + endx1 + ", endy1=" + endy1);
                        Log.e(TAG, "startx3=" + startx1 + ", starty3=" + starty3);
                        Log.e(TAG, "endx3=" + endx3 + ", endy3=" + endy3);


                    }


                }

            }
            //自定义起点和终点

            else if (navigationType == 2) {


                if (useNavigation == true && !(x == targetX && y == targetY)) {

                    Paint paint = new Paint();
                    paint.setColor(Color.RED); // 设置线条颜色
                    paint.setStrokeWidth(5); // 设置线条宽度
                    paint.setStyle(Paint.Style.STROKE); // 实线样式
                    paint.setAntiAlias(true);

                    // 定义线条的起点和终点坐标
                    float startx1 = startX;
                    float starty1 = startY;
                    float endx1 = 0.5f * screenWidth;
                    float endy1 = startY;

                    float startx2 = endx1;
                    float starty2 = endy1;
                    float endx2 = endx1;
                    float endy2 = targetY;

                    float startx3 = endx2;
                    float starty3 = endy2;
                    float endx3 = targetX;
                    float endy3 = targetY;


                    //目标在走廊两侧
                    if (true) {
                        if (path != null) {
                            path.reset();
                            // 继续进行路径的绘制等操作
                        }
                        path.moveTo(startx1, starty1);
                        path.lineTo(endx1, endy1);

                        // 计算箭头
                        double angle1 = Math.atan2(endy1 - starty1, endx1 - startx1);
                        double arrowAngle1 = Math.PI / 6; // 箭头夹角
                        float arrowX1 = (float) (endx1 - arrowSize * Math.cos(angle1 + arrowAngle1));
                        float arrowY1 = (float) (endy1 - arrowSize * Math.sin(angle1 + arrowAngle1));
                        float arrowX2 = (float) (endx1 - arrowSize * Math.cos(angle1 - arrowAngle1));
                        float arrowY2 = (float) (endy1 - arrowSize * Math.sin(angle1 - arrowAngle1));

                        canvas.drawPath(path, paint); // 绘制路径

                        //绘制箭头
                        path.moveTo(endx1, endy1);
                        path.lineTo(arrowX1, arrowY1);
                        path.moveTo(endx1, endy1);
                        path.lineTo(arrowX2, arrowY2);

                        canvas.drawPath(path, paint); // 绘制箭头


                        if (path != null) {
                            path.reset();
                            // 继续进行路径的绘制等操作
                        }
                        path.moveTo(startx2, starty2);
                        path.lineTo(endx2, endy2);

                        // 计算箭头
                        double angle2 = Math.atan2(endy2 - starty2, endx2 - startx2);
                        double arrowAngle2 = Math.PI / 6; // 箭头夹角
                        arrowX1 = (float) (endx2 - arrowSize * Math.cos(angle2 + arrowAngle2));
                        arrowY1 = (float) (endy2 - arrowSize * Math.sin(angle2 + arrowAngle2));
                        arrowX2 = (float) (endx2 - arrowSize * Math.cos(angle2 - arrowAngle2));
                        arrowY2 = (float) (endy2 - arrowSize * Math.sin(angle2 - arrowAngle2));

                        canvas.drawPath(path, paint); // 绘制路径

                        //绘制箭头
                        path.moveTo(endx2, endy2);
                        path.lineTo(arrowX1, arrowY1);
                        path.moveTo(endx2, endy2);
                        path.lineTo(arrowX2, arrowY2);

                        canvas.drawPath(path, paint); // 绘制箭头


                        if (path != null) {
                            path.reset();
                            // 继续进行路径的绘制等操作
                        }
                        path.moveTo(startx3, starty3);
                        path.lineTo(endx3, endy3);

                        // 计算箭头
                        double angle3 = Math.atan2(endy3 - starty3, endx3 - startx3);
                        double arrowAngle3 = Math.PI / 6; // 箭头夹角
                        arrowX1 = (float) (endx3 - arrowSize * Math.cos(angle3 + arrowAngle3));
                        arrowY1 = (float) (endy3 - arrowSize * Math.sin(angle3 + arrowAngle3));
                        arrowX2 = (float) (endx3 - arrowSize * Math.cos(angle3 - arrowAngle3));
                        arrowY2 = (float) (endy3 - arrowSize * Math.sin(angle3 - arrowAngle3));

                        canvas.drawPath(path, paint); // 绘制路径

                        //绘制箭头
                        path.moveTo(endx3, endy3);
                        path.lineTo(arrowX1, arrowY1);
                        path.moveTo(endx3, endy3);
                        path.lineTo(arrowX2, arrowY2);

                        canvas.drawPath(path, paint); // 绘制箭头


                        Log.e(TAG, "startx1=" + startx1 + ", starty1=" + starty1);
                        Log.e(TAG, "endx1=" + endx1 + ", endy1=" + endy1);
                        Log.e(TAG, "startx3=" + startx1 + ", starty3=" + starty3);
                        Log.e(TAG, "endx3=" + endx3 + ", endy3=" + endy3);


                    }


                }

            }


        }

        if (x != -1 && y != -1 && drawable != null) {
            double width = drawable.getIntrinsicWidth();
            width=width*1000/screenWidth;//这里是调整图标大小
            double height = drawable.getIntrinsicHeight();
            height=height*1632/screenHeight;
            drawable.setBounds((int)(x - width / 2), (int)(y - height ), (int)(x + width / 2), (int)(y ));
            drawable.draw(canvas);
            Log.e(TAG, "Drawable width=" + width + ", height=" + height);
        }

        if(nearby==1){
            JSONObject userPositions = UserPositionManager.getInstance().getUserPositions();

            if (userPositions != null) {
                // 处理 user_positions
                Iterator<String> keys = userPositions.keys();
                while (keys.hasNext()) {
                    String key = keys.next();
                    try {
                        String value = userPositions.getString(key);
                        Log.d(TAG, "User: " + key + ", Position: " + value);
                        if (!key.equals(username)) {
                            // 确保 coordinateMap 和 value 都不为 null
                            if (coordinateMap != null && value != null) {
                                coord = coordinateMap.get(value);
                                if (coord != null) {
                                    Log.e(TAG, coord.toString());
                                    paint.setColor(dotColor);
                                    paint.setAntiAlias(true);
                                    Log.e(TAG, coord.first.toString() + coord.second.toString());
                                    this.dotX = coord.first * width2;
                                    this.dotY = coord.second * height2;
                                    Log.e(TAG, "dotX=" + this.dotX + " dotY=" + this.dotY);
                                    canvas.drawCircle(dotX, dotY, dotRadius, paint);
                                    paint.setColor(Color.BLACK); // 设置文字颜色为黑色
                                    paint.setStyle(Paint.Style.FILL); // 设置画笔样式
                                    paint.setTextSize(40); // 设置文字大小为40px
                                    canvas.drawText(key, dotX-dotRadius , dotY+dotRadius+ 40, paint);
                                } else {
                                    Log.e(TAG, "Coordinate not found for value: " + value);
                                }
                            } else {
                                Log.e(TAG, "coordinateMap or value is null");
                            }
                        }
                    } catch (JSONException e) {
                        Log.e(TAG, "Error getting value for key: " + key, e);
                    }
                }
            } else {
                Log.d(TAG, "No user positions available");
            }
        }

    }

    public void setTargetPosition(String target,int width,int height) {
        width2=width;
        height2=height;
        coord = coordinateMap.get(target);
        Log.e(TAG,coord.toString());
        if (coord != null) {
            Log.e(TAG, coord.first.toString() + coord.second.toString());
            this.targetX = coord.first * width;
            this.targetY = coord.second * height;
            Log.e(TAG, "Mytargetx=" + this.targetX + "Mytargety=" + this.targetY);
        }



            invalidate();


    }
    public void setStartPosition(String target,int width,int height) {
        width2=width;
        height2=height;
        coord = coordinateMap.get(target);
        Log.e(TAG,coord.toString());
        if (coord != null) {
            Log.e(TAG, coord.first.toString() + coord.second.toString());
            this.startX = coord.first * width;
            this.startY = coord.second * height;
            Log.e(TAG, "Mystartx=" +  coord.first + "Mystarty=" +coord.second );
        }
    }


    public void setDotPosition(float x, float y,int width,int height) {
        width2=width;
        height2=height;
        this.x = x*width;
        this.y = y*height;
        this.screenWidth=width;
        this.screenHeight=height;
        if(x!=-1){
            invalidate(); // 请求重绘
        }



        //****************************************************************
        //弹窗
        if(x==targetX&&y==targetY){
            if(beginX!=x&&beginY!=y){
                //弹窗






                this.useNavigation=false;
                beginX=x;
                beginY=y;
                targetY=-1;
                targetX=-1;
            }

        }

    }
}
