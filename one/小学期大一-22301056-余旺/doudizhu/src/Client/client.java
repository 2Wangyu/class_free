package Client;

import java.io.IOException;
import java.util.Scanner;

//当每一个玩家进行注册或登录的时候会开启
public class client {

    public static void main(String[] args) throws IOException, InterruptedException, ClassNotFoundException {
        Player player = new Player();

        while (true) {
            //进行登录注册界面，房间选择界面，准备界面
            player.home();
            //进行最终的打牌界面
            player.playGame();
        }
    }
}
