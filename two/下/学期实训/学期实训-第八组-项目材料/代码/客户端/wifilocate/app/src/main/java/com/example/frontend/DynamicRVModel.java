package com.example.frontend;

public class DynamicRVModel {

    String name;
    String name1;

    float ratingbar;
    private  int image;


    public DynamicRVModel(String name,String name1,int image,float ratingbar) {

        this.name = name;
        this.name1=name1;
        this.image=image;
        this.ratingbar=ratingbar;
    }

    public String getName() {
        return name;
    }
    public String getName1(){

        return name1;
    }
    public int getImage(){
        return image;

    }

    public float getRatingbar() {
        return ratingbar;
    }
}
