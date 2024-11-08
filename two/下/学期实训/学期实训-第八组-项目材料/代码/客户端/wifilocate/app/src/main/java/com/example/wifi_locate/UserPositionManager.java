package com.example.wifi_locate;
import org.json.JSONObject;

public class UserPositionManager {
    private static UserPositionManager instance;
    private JSONObject userPositions;

    private UserPositionManager() {
        // 私有构造函数，防止外部实例化
    }

    public static synchronized UserPositionManager getInstance() {
        if (instance == null) {
            instance = new UserPositionManager();
        }
        return instance;
    }

    public void setUserPositions(JSONObject userPositions) {
        this.userPositions = userPositions;
    }

    public JSONObject getUserPositions() {
        return userPositions;
    }
}