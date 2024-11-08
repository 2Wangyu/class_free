package Server;


import java.util.ArrayList;

public class Room {
    private ArrayList<Player> players = new ArrayList<>();//在房间里的玩家
    private int num;//人数
    private boolean start;//开始游戏信号
    private ArrayList<Player> readyPlayer = new ArrayList<>();//已经准备了的玩家
    static int n = 3;

     public void decrease(){
         synchronized (this){
             n--;
         }
     }

     //每一个房间都初始化，默认0人加入
    public Room() {
        this.num = 0;
        this.start = false;
    }

    public void addPlayer(Player player) {//加入玩家
        players.add(player);
        num++;
    }

    public void setStart(boolean start) {
        this.start = start;
    }

    public ArrayList<Player> getReadyPlayer() {
        return readyPlayer;
    }

    //当有玩家申请加入时
    public void addReady(Player player) {//加入准备玩家
        if (!readyPlayer.contains(player)) {
            readyPlayer.add(player);
            System.out.println("ready");
        }
        if (readyPlayer.size() == 3) {
            this.start = true;//三人都准备则开始信号置true
        }
    }
    //当有玩家不想准备的时候则移除该玩家准备情况，但仍然占据房间
    public void removeReady(Player player) {//取消准备玩家
        if (readyPlayer.remove(player))
            System.out.println("unready");
    }

    public int getNum() {
        return num;
    }

    public ArrayList<Player> getPlayers() {
        return players;
    }


    //删除的时候，准备的和在玩的玩家都要删除
    public void removePlayer(Player player) {//玩家退出房间
        players.remove(player);//删除房间里的玩家
        readyPlayer.remove(player);//如果退出的是已准备玩家,也删除
        num--;
    }

    public boolean isStart() {
        return start;
    }


    //对于其他位置的两位玩家的准备和进房间情况进行统计
    public String roomInfo(Player player) {
         //只有一个玩家用1020表示
        if (this.num == 1) {
            return "1020";
        } else if (this.num == 2) {
            int i = 1;
            for (Player p : players) {
                if (!p.equals(player)) {
                    if (readyPlayer.contains(p))
                        i = 2;
                }
            }
            //两个玩家
            //准备1220.没准备1120
            return "1" + i + "20";
        } else {
            int[] i = {1, 1};
            int n = 0;
            for (Player p : players) {
                if (!p.equals(player)) {
                    if (readyPlayer.contains(p))
                        i[n++] = 2;
                }
            }
            //三个玩家
            //都准备1222，一个没准备1221，都没准备1121
            return "1" + i[0] + "2" + i[1];
        }
    }
}
