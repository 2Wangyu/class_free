package com.example.wifi_locate;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import androidx.core.content.ContextCompat;
public class NavigationLine extends View {
    private Paint paint;
    private double x = -1;
    private double y = -1;
    private  int screenWidth;
    private  int screenHeight;
    private Drawable drawable;
    private static final String TAG = "NavigationLine";
    public NavigationLine(Context context) {
        super(context);
        init(context);
    }

    public NavigationLine(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public NavigationLine(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    private void init(Context context) {
        paint = new Paint();
        paint.setColor(Color.RED);
        paint.setStyle(Paint.Style.FILL);
        drawable = ContextCompat.getDrawable(context, R.drawable.baseline_edit_location_24);


    }

    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        if (x != -1 && y != -1 && drawable != null) {
            double width = drawable.getIntrinsicWidth();
            width=width*1000/screenWidth;
            double height = drawable.getIntrinsicHeight();
            height=height*1632/screenHeight;
            drawable.setBounds((int)(x - width / 2), (int)(y - height ), (int)(x + width / 2), (int)(y ));
            drawable.draw(canvas);
            Log.e(TAG, "Drawable width=" + width + ", height=" + height);
        }
    }




    public void setDotPosition(double x, double y,int width,int height) {
        this.x = x*width;
        this.y = y*height;
        this.screenWidth=width;
        this.screenHeight=height;
        invalidate(); // 请求重绘
    }
}
