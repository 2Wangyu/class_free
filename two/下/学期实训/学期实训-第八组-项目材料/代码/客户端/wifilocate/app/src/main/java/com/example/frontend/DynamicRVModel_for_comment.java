package com.example.frontend;

import android.graphics.Bitmap;

public class DynamicRVModel_for_comment {

    private String name;
    private String name1;
    private float ratingbar;
    private Bitmap bitmap;

    public DynamicRVModel_for_comment(String name, String name1, Bitmap bitmap, float ratingbar) {

        this.name = name;
        this.name1 = name1;
        this.ratingbar = ratingbar;
        this.bitmap=bitmap;
    }

    public String getName() {
        return name;
    }

    public String getName1() {
        return name1;
    }

    public Bitmap getImage() {
        return bitmap;

    }

    public float getRatingbar() {
        return ratingbar;
    }
}
