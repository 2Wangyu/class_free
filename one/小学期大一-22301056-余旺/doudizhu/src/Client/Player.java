package Client;

import TestSqlite.JDBC_Connector;
import TestSqlite.JDBC_Connector1;
import WordTest.Test3;
import org.apache.poi.ss.formula.functions.T;

import javax.swing.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

import static java.lang.Thread.sleep;

//通过和服务端的发送与接受信息实现了
//多个房间的跳转
//抢地主，发牌，出牌，显示牌，整理牌堆，结果展示等等的效果

public class Player {
    //用于屏幕录制

    private DataInputStream in;//输入流
    private DataOutputStream out;//输出流
    private Socket socket = new Socket();//客户端的套接字
    private ArrayList<String> deck = new ArrayList<>();//自己的牌
    private String serverMessage;//和服务器消息
    private boolean isLord;//自己是不是地主
    private String whoIsLord;//谁是地主
    private String state;//准备状态
    private boolean isInGame;//判断是否从游戏里出来
    private String roomInfo;//房间内玩家准备情况
    private String roomNum;//大厅里房间人数情况
    private String selectRoom;//玩家房间选择

    //通过玩家这个来控制三个窗口分别打开和运行
    StartJFrame startJFrame;
    RoomJFrame roomJFrame;
    GameJFrame gameJFrame;
    public static boolean inStartJFrame = true;//开始页面
    int x = 450;//窗口默认位置
    int y = 210;

    //位置改变就需要不断更新位置
    public void refreshJFrameLocate(int[] point) {
        if (point[0] != this.x)
            this.x = point[0];
        if (point[1] != this.y)
            this.y = point[1];
    }

    //用不了
    public void setInStartJFrame(boolean inStartJFrame) {
        this.inStartJFrame = inStartJFrame;
    }

    //对于玩家的操作
    public Player() {
        try {
            //服务器ip，
            //如果想要多人进行游戏，需要将ip设置成不同的ip地址
            //这里方便进行使用了本地ip
            String ip = "127.0.0.1";//本地ip
            InetSocketAddress socketAddress = new InetSocketAddress(ip,57498 );
            this.socket.connect(socketAddress);
            System.out.println("接入成功");//可以忽视
            this.in = new DataInputStream(this.socket.getInputStream());
            this.out = new DataOutputStream(this.socket.getOutputStream());
        } catch (IOException e) {
            System.out.println("断开连接");//可以忽视
        }
        this.isInGame = false;
        this.selectRoom = "-1";
    }

    //游戏选择房间
    public void home() throws IOException, ClassNotFoundException {
        startJFrame = new StartJFrame(this.x, this.y);
        startJFrame.show(this);
        while (Player.inStartJFrame) {//这循环里什么都不放的话会有bug
            try {
                refreshJFrameLocate(startJFrame.getLocate());//更新窗口位置
                sleep(10);
            } catch (Exception e) {
                System.exit(0);
            }
            ;
        }
        //一旦跳出循环代表登录或者注册成功了
        startJFrame.close();
        while (true) {
            if (!isInGame) {

                System.out.println("大厅");
                //直接显示大厅
                System.out.println("选择房间");
                this.selectRoom = "-1";
                SelectRoomJFrame selectRoomJFrame = new SelectRoomJFrame(this.x, this.y);
                selectRoomJFrame.showSelectRoom(this);//调试选择房间窗口
                //读取服务器信息
                serverMessage = in.readUTF();
                //发送房间信息
                out.writeUTF(this.selectRoom);
                selectRoomJFrame.refresh(serverMessage);
                //是否可以进入房间需要通过服务端来控制
                while (true) {
                    refreshJFrameLocate(selectRoomJFrame.getLocate());//更新位置
                    serverMessage = in.readUTF();//服务器发过来的房间信息
                    if (serverMessage.equals("full")) {//弹出提示人员已经满了
                        System.out.println("房间人数已满");
                        JOptionPane.showMessageDialog(null, "房间人数已满");
                        this.selectRoom = "-1";
                    }
                    if (serverMessage.equals("ok")) {//在后面显示进入房间
                        out.writeUTF("1");
                        selectRoomJFrame.close();//关闭选择房间窗口
                        break;
                    }
                    storeRoomNum(serverMessage, selectRoomJFrame);//储存大厅房间状态(人数)
                    out.writeUTF(this.selectRoom);

                }
            }
            if (gameReady())//游戏准备环节,准备完成则开始游戏
                break;
        }
    }

    //状态
    public void setState(String state) {
        this.state = state;
    }

    //如果返回true表示开始游戏, false表示退出房间, 返回大厅选择房间
    //state为玩家状态,默认unready,ready为准备,quit为退出房间,不断传回服务器
    public boolean gameReady() throws IOException {
        //进入准备阶段，则需要打开第三个：房间窗口
        roomJFrame = new RoomJFrame(this.x, this.y);
        roomJFrame.show(this);
        this.isInGame = false;
        //退出游戏后返回准备阶段,可以退出房间到大厅或继续准备
        this.state = "unready";//按钮切换ready,unready,quit
        String message;
        while (true) {
            refreshJFrameLocate(roomJFrame.getLocate());//更新位置
            message = in.readUTF();
            if (message.startsWith("ready?")) {//例1020  0没人 1有 2准备
                String[] s = message.split("\\?");
                storeRoomInfo(s[1], roomJFrame);//储存房间状态,并修改
                out.writeUTF(state);
            }
            if (message.equals("start")) {
                out.writeUTF("start");
                System.out.println("start");
                roomJFrame.close();
                return true;
            }
            if (message.equals("quit")) {
                out.writeUTF("quit");
                System.out.println("退出房间");

                roomJFrame.close();//关闭调试窗口
                return false;
            }
        }
    }


    //玩家游戏环节
    //玩家进行抢地主, 出牌阶段
    //游戏局内
    public void playGame() throws IOException, InterruptedException, ClassNotFoundException {
        do {
            this.isInGame = true;
            //游戏局内,设为true,游戏单局结束后直接到准备阶段
            //让游戏持续进行下去

            //获取手牌
            dealCards();
        } while (!robLord());//抢地主环节
        //开始出牌
        gameRound();
    }

     // 玩家游戏环节里获取手牌方法
    //获取手牌
    public void dealCards() throws IOException, ClassNotFoundException {
        String str = message();//服务器传过来的开始游戏信息
        System.out.println(str);
        List<String> result = Arrays.asList(message().split(""));//message里是服务器传过来的手牌信息
        deck = new ArrayList<>(result);//手牌
        sortDeck();//排序
        //获取自己的牌
        System.out.println("你的牌为\n" + deck.toString());//显示手牌




        JDBC_Connector1.getInstance().add(User.getInstance().getUsername(), "你的牌为" + deck.toString());



    }

    //true表示地主产生,进入出牌环节;false表示都不叫地主,重新发牌
    // 玩家游戏环节里抢地主方法
    public boolean robLord() throws IOException, InterruptedException, ClassNotFoundException {
        System.out.println("抢地主");

        //显示抢地主
        gameJFrame = new GameJFrame(this.x, this.y, this);
        gameJFrame.showGame();
       //屏幕录制


        gameJFrame.printCards();
        int noCall = 0;
        for (int i = 0; i < 3; i++) {
            refreshJFrameLocate(gameJFrame.getLocate());
            //从服务器获取信息，
            serverMessage = message();
            if (serverMessage.equals("抢地主")) {
                serverMessage = in.readUTF();
                String s = gameJFrame.returnNum(serverMessage);
                //改成按钮传入,需要设置阻塞,
                //写入while死循环？,选择了才返回,选择抢地主的点数，没想明白
                if (s.equals("0")) {
                    //后面的通过scanner方法读入的都需要阻塞,使用while死循环？？
                    noCall++;
                }
                out.writeUTF(s);
                System.out.println("你抢了" + s);//向服务器传入自己抢的点数以便以共享


                JDBC_Connector1.getInstance().add(User.getInstance().getUsername(), "你抢了" + s );


            } else {
                gameJFrame.refresh(serverMessage);
                //显示其他玩家抢的点数
                if (serverMessage.charAt(1) == '0') {
                    noCall++;
                }
            }
        }
        if (noCall == 3) {
            //三人都不叫,返回false ,重新发牌
            gameJFrame.close();
            return false;
        }
        serverMessage = message();
        whoIsLord = serverMessage;
        //储存地主信息
        if (serverMessage.equals("you")) {
            System.out.println("你是地主");


            JDBC_Connector1.getInstance().add(User.getInstance().getUsername(),  "你是地主" );




            //显示自己为地主
            isLord = true;
            //添加地主三张牌
            String c;
            StringBuilder s = new StringBuilder();
            for (int i = 0; i < 3; i++) {
                c = message();
                deck.add(c);
                s.append(c);
            }
            gameJFrame.addSelf(s.toString());
            //地主显示三张地主牌传入builder.toString
        } else {
            System.out.println(serverMessage);
            //显示地主,加上地主的三张牌 例2AAA,显示
            isLord = false;
            //服务器发送地主的三张牌
            //界面显示地主牌
            whoIsLord = serverMessage.charAt(0) + "";
            gameJFrame.addLord(serverMessage);
            //更新地主身份
        }
        sortDeck();
        gameJFrame.printCards();//显示手牌
        System.out.println("你的手牌为" + deck.toString());//显示自己的手牌


        JDBC_Connector1.getInstance().add(User.getInstance().getUsername(),  "你的手牌为" + deck.toString() );


        return true;
    }


       // 玩家游戏环节里出牌循环方法, 比较上家牌, 能吃则出牌, 不能在重新选择
    public void gameRound() throws InterruptedException, IOException, ClassNotFoundException {
        while (true) {

                serverMessage = in.readUTF();
            if (serverMessage.equals("请你出牌")) {
                System.out.println("请你出牌");//提示玩家出牌
                String str;
                //出牌
                str = gameJFrame.outCards();
                out.writeUTF(str);//str表示出的牌,
                String[] s = str.split("");
                for (String s1 : s) {
                    deck.remove(s1);
                }
                //重新整理牌堆
                gameJFrame.printCards();
                System.out.println("你出了" + str + "牌");


                JDBC_Connector1.getInstance().add(User.getInstance().getUsername(),  "你出了" + str + "牌" );


                //显示玩家出的牌
                gameJFrame.printPlayedCards("m" + str);
                //显示出牌
                CompareCard.getInstance().setCompareCard("m" + str);
                //出牌记录下来
                System.out.println("你现在的牌为" + deck.toString());


                JDBC_Connector1.getInstance().add(User.getInstance().getUsername(),  "你现在的牌为" + deck.toString() );


            } else if (serverMessage.equals("游戏结束")) {//服务器返回结束信号
                out.writeUTF("1");
                serverMessage = message();
                if (serverMessage.equals(whoIsLord)) {
                    if (isLord) {


                        System.out.println("地主赢了");
                        JDBC_Connector1.getInstance().add(User.getInstance().getUsername(),  "你作为地主赢了" );
                        //欢乐豆数量的变更
                        User.getInstance().setHappybeen(User.getInstance().getHappybeen()+40);
                        //每一局的牌打完之后都会出现欢乐豆数量的变更，每一次word文档的写出都会更新数据
                        //同时为了方式用户意外退出导致信息没有储存，每打完一把游戏保存一次
                        new Test3(User.getInstance().getUsername(), User.getInstance().getPassword(), User.getInstance().getHappybeen()).test();
                        //将数据储存到数据库当中
                        new JDBC_Connector(User.getInstance().getUsername(), User.getInstance().getPassword(), User.getInstance().getHappybeen()).add();

                        gameJFrame.showLordWin();


                    } else {
                        System.out.println("农民输了");

                        User.getInstance().setHappybeen(User.getInstance().getHappybeen()-20);
                        new Test3(User.getInstance().getUsername(), User.getInstance().getPassword(), User.getInstance().getHappybeen()).test();
                        new JDBC_Connector(User.getInstance().getUsername(), User.getInstance().getPassword(), User.getInstance().getHappybeen()).add();
                        JDBC_Connector1.getInstance().add(User.getInstance().getUsername(),  "你作为农民赢了" );


                        gameJFrame.showFarmerLose();

                    }
                } else {
                    if (isLord) {
                        System.out.println("地主输了");


                        JDBC_Connector1.getInstance().add(User.getInstance().getUsername(),  "你作为地主输了" );
                        User.getInstance().setHappybeen(User.getInstance().getHappybeen()-40);
                        new Test3(User.getInstance().getUsername(), User.getInstance().getPassword(), User.getInstance().getHappybeen()).test();                        new JDBC_Connector(User.getInstance().getUsername(), User.getInstance().getPassword(), User.getInstance().getHappybeen()).add();
                        new JDBC_Connector(User.getInstance().getUsername(), User.getInstance().getPassword(), User.getInstance().getHappybeen()).add();

                        gameJFrame.showLordLose();


                    } else {
                        System.out.println("农民赢了");


                        JDBC_Connector1.getInstance().add(User.getInstance().getUsername(),  "你作为农民赢了" );
                        User.getInstance().setHappybeen(User.getInstance().getHappybeen()+20);
                        new Test3(User.getInstance().getUsername(), User.getInstance().getPassword(), User.getInstance().getHappybeen()).test();
                        new JDBC_Connector(User.getInstance().getUsername(), User.getInstance().getPassword(), User.getInstance().getHappybeen()).add();


                        gameJFrame.showFarmerWin();

                    }
                }
                gameJFrame.close();
                //一局游戏结束就结束录制






            } else {
                CompareCard.getInstance().setCompareCard(serverMessage);//记录其他玩家出牌
                gameJFrame.printPlayedCards(serverMessage);
                System.out.println(serverMessage);//处理其他玩家出牌,第一个为玩家序号,后面是玩家出的牌
                out.writeUTF("1");
            }
        }
    }

    //封装的客户端接收服务器的消息
    public String message() throws IOException {
        String str = this.in.readUTF();
        this.out.writeUTF("message");
        return str;
    }

    //自定义的斗地主卡牌排序的比较器
    //自定义比较大小
    public static Comparator<String> comparator = (s1, s2) -> {
        //总的就是相等返回0，前者小返回-1，否则返回1

        if (s1.equals("3")) {
            if (s2.equals("3"))
                return 0;
            else
                return -1;
        } else if (s1.equals("4")) {
            if (s2.equals("3")) {
                return 1;
            } else if (s2.equals("4"))
                return 0;
            else {
                return -1;
            }
        } else if (s1.equals("5")) {
            if (s2.equals("3") || s2.equals("4")) {
                return 1;
            } else if (s2.equals("5"))
                return 0;
            else {
                return -1;
            }
        } else if (s1.equals("6")) {
            if (s2.equals("3") || s2.equals("4") || s2.equals("5")) {
                return 1;
            } else if (s2.equals("6"))
                return 0;
            else {
                return -1;
            }
        } else if (s1.equals("7")) {
            if (s2.equals("3") || s2.equals("4") || s2.equals("5") || s2.equals("6")) {
                return 1;
            } else if (s2.equals("7"))
                return 0;
            else {
                return -1;
            }
        } else if (s1.equals("8")) {
            if (s2.equals("3") || s2.equals("4") || s2.equals("5") || s2.equals("6") || s2.equals("7")) {
                return 1;
            } else if (s2.equals("8"))
                return 0;
            else {
                return -1;
            }
        } else if (s1.equals("9")) {
            if (s2.equals("3") || s2.equals("4") || s2.equals("5") ||
                    s2.equals("6") || s2.equals("7") || s2.equals("8")) {
                return 1;
            } else if (s2.equals("9"))
                return 0;
            else {
                return -1;
            }
            //特殊的X代表数字10
        } else if (s1.equals("X")) {
            if (s2.equals("3") || s2.equals("4") || s2.equals("5") ||
                    s2.equals("6") || s2.equals("7") || s2.equals("8") || s2.equals("9")) {
                return 1;
            } else if (s2.equals("X"))
                return 0;
            else {
                return -1;
            }
        } else if (s1.equals("J")) {
            if (s2.equals("W") || s2.equals("w") || s2.equals("2") ||
                    s2.equals("A") || s2.equals("K") || s2.equals("Q")) {
                return -1;
            } else if (s2.equals("J"))
                return 0;
            else {
                return 1;
            }
        } else if (s1.equals("Q")) {
            if (s2.equals("W") || s2.equals("w") || s2.equals("2") ||
                    s2.equals("A") || s2.equals("K")) {
                return -1;
            } else if (s2.equals("Q"))
                return 0;
            else {
                return 1;
            }
        } else if (s1.equals("K")) {
            if (s2.equals("W") || s2.equals("w") || s2.equals("2") ||
                    s2.equals("A")) {
                return -1;
            } else if (s2.equals("K"))
                return 0;
            else {
                return 1;
            }
        } else if (s1.equals("A")) {
            if (s2.equals("W") || s2.equals("w") || s2.equals("2")) {
                return -1;
            } else if (s2.equals("A"))
                return 0;
            else {
                return 1;
            }
        } else if (s1.equals("2")) {
            if (s2.equals("W") || s2.equals("w")) {
                return -1;
            } else if (s2.equals("2"))
                return 0;
            else {
                return 1;
            }
            //小王和大王
        } else if (s1.equals("w")) {
            if (s2.equals("W")) {
                return -1;
            } else {
                return 1;
            }
        } else if (s1.equals("W")) {
            return 1;
        }
        return 0;
    };


    //排序手牌
    public void sortDeck() {
        deck.sort(comparator);
    }

    public DataInputStream getIn() {
        return in;
    }

    public DataOutputStream getOut() {
        return out;
    }

    public ArrayList<String> getDeck() {
        return deck;
    }

    public void setDeck(ArrayList<String> deck) {
        this.deck = deck;
    }


     //储存大厅房间人数情况, 如果变化则更新
    public void storeRoomInfo(String info, RoomJFrame w) {
        String[] str = info.split("");//四位数字,每两位代表一个玩家,例1021代表1没人,2进房间未准备
        if (!info.equals(this.roomInfo)) {//0:没人,1:进房间,2:已准备
            System.out.println(info);//更新玩家准备情况
            w.refresh(info);
            this.roomInfo = info;
        }
    }

    public void setSelectRoom(String selectRoom) {
        this.selectRoom = selectRoom;
    }

    //储存房间玩家情况, 如果有变化则更新
   //
    public void storeRoomNum(String roomNum, SelectRoomJFrame w) {
        if (!roomNum.equals(this.roomNum) && !roomNum.equals("full")) {
            System.out.println(roomNum);//对接更新房间信息
            w.refresh(roomNum);
            this.roomNum = roomNum;
        }
    }

}
