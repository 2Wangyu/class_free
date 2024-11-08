package com.example.frontend;

import android.widget.RatingBar;

public class StaticRvModel {

    private int image;
    private String text;
    private RatingBar ratingBar;

    public StaticRvModel(int image, String text) {
        this.image = image;
        this.text = text;
    }

    public int getImage() {
        return image;
    }

    public String getText() {
        return text;
    }
    public RatingBar getRatingBar(){
        return  ratingBar;
    }
}
