package com.example.frontend.DRVinterface;

import android.media.Image;
import android.widget.ImageView;

import com.example.frontend.DynamicRVModel;
import com.example.frontend.DynamicRVModel_for_comment;

import java.util.ArrayList;
import java.util.List;

public interface UpdateRecycleView1 {
    public void callback1(int position, ArrayList<DynamicRVModel_for_comment> items);
}
