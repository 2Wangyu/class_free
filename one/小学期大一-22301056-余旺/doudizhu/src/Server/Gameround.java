package Server;

import java.util.*;

//服务器的功能
//具体出牌，牌的数量都通过str转换替代

//1,完成发牌，抢地主功能，打牌（虚拟，实际上是在客户端进行）
//2，判断打牌结束功能


public class Gameround {
    private ArrayList<Player> players;//三个玩家
    private ArrayList<String> lordcards;//地主的牌
    private ArrayList<String> n = new ArrayList<>();//抢地主点数，根据点数来抢地主
    private int whoIsLord;//地主
    private ArrayList<String> setCards;//一副扑克

    //初始化
    public Gameround(ArrayList<Player> players) {
        this.players = players;
        //X代表10方便传输
        String[] strings = {
                "A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K",
                "A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K",
                "A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K",
                "A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K",
                "W", "w"};//一副扑克牌
        List<String> list = Arrays.asList(strings);
        this.setCards = new ArrayList<>(list);//转换成ArrayList,好操作一些
    }


    public void gameStart() {
        for (Player player : players){
            player.setInGame(true);//设置玩家在游戏内,在游戏结束是以便直接出现在房间里面
        }
        do {
            //发牌
            dealCards();
            //抢地主
        } while (!roblord());//抢地主,如果都为0,则重新发牌

        //出牌循环
        int i = whoIsLord;//记录谁是地主,从地主开始出牌
        while (true) {
            //接收出的牌，
            String r = sendToOne(i, "请你出牌");//提示玩家出牌
            if (r != null){
                String[] str = r.split("");//玩家出的牌
                for (String s : str) {
                    //移除出的牌
                    players.get(i).getPlayerDeck().remove(s);
                }
            }
            if (players.get(i).getPlayerDeck().isEmpty()){//如果玩家出完牌了
                sendToAll("游戏结束");//提示游戏结束
                if (i == whoIsLord) {//如果是地主则给其他两名玩家说地主赢了
                    sendToAnotherTwoWithoutI(i, "" + i);
                    sendToOne(i, "you");
                } else {
                    sendToAll(""+i);//给其他玩家说谁是赢家
                }
                break;
            }
            System.out.println("player" + i + "出了" + r);
            sendToAnotherTwo(i, r);//给其他玩家发送此玩家出的牌
            i = (i+1) % 3;
        }
    }


    //发牌
    public void dealCards() {
        Collections.shuffle(setCards);//打乱牌组
        //用subList将牌组隔开，在通过发送数据实现发牌功能
        List<String> deck = setCards.subList(0, 17);//发牌,一人17张
        players.get(0).setPlayerDeck(new ArrayList<>(deck));
        deck = setCards.subList(17, 34);
        players.get(1).setPlayerDeck(new ArrayList<>(deck));
        deck = setCards.subList(34, 51);
        players.get(2).setPlayerDeck(new ArrayList<>(deck));
        deck = setCards.subList(51, 54);
        lordcards = new ArrayList<>(deck);//3张地主牌
        for (int i = 0; i < 3; i++) {
            sendToOne(i, "游戏开始");
            sendToOne(i, players.get(i).outputPlayerDeck());//给玩家发送手牌
        }
    }


    //抢地主
    public boolean roblord() {
        int no = 0;//都不叫,则重新发牌
        init();//初始化抢地主点数
        for (int i = 0; i < 3; i++) {
            sendToOne(i, "抢地主");
            String s = sendToOne(i, tostring(n));
            players.get(i).setNumber(Integer.parseInt(s));
            if (s.equals("0")) {
                no++;
            }else {
                n.remove(s);
            }
            sendToAnotherTwo(i, s);//给其他玩家发送此玩家抢的点数
        }
        if (no == 3){
            System.out.println("重新洗牌");
            return false;
        }
        //找出地主
        for (int i = 1; i < 3; i++) {
            if (players.get(i).getNumber() > players.get(whoIsLord).getNumber()) {
                whoIsLord = i;//i是地主
            }
        }
        for (int i = 0; i < 3; i++) {
            if (i == whoIsLord) {
                sendToOne(i, "you");
                sendToOne(i, lordcards.get(0));//给地主三张多的牌
                sendToOne(i, lordcards.get(1));
                sendToOne(i, lordcards.get(2));
            } else {
                sendToOne(i, "" + whoIsLord + this.lordcards.get(0)+this.lordcards.get(1)+this.lordcards.get(2));//给其他玩家说地主是谁和地主牌
            }
        }
        return true;
    }

  //初始化抢地主，叫地主的点数
    public void init(){//初始化抢地主点数
        ArrayList<String> i = new ArrayList<>();
        i.add("0");
        i.add("1");
        i.add("2");
        i.add("3");
        n = i;
        whoIsLord = 0;
    }
    //给所有人发消息，并接受客户端传来的消息
    public void sendToAll(String message) {
        for (int i = 0; i < 3; i++) {
            players.get(i).sendMsg(message);
            players.get(i).receiveMsg();
        }
    }

    //给除了i的其他两人发送消息
    public void sendToAnotherTwo(int i, String message) {
        for (int j = 0; j < 3; j++) {
            if (j != i) {
                players.get(j).sendMsg(i + message);
                players.get(j).receiveMsg();
            }
        }
    }

    //给除了i的其他两人发送消息,不带i
    public void sendToAnotherTwoWithoutI(int i, String message) {
        for (int j = 0; j < 3; j++) {
            if (j != i) {
                players.get(j).sendMsg(message);
                players.get(j).receiveMsg();
            }
        }
    }

    //给i发消息
    public String sendToOne(int i, String message) {
        players.get(i).sendMsg(message);
        return players.get(i).receiveMsg();
    }
    //toString
    public String tostring(ArrayList<String> arrayList){
        int n = arrayList.size();
        StringBuilder str = new StringBuilder();
        for (int i = 0; i < n; i++) {
            str.append(arrayList.get(i));
        }
        return str.toString();
    }
}
