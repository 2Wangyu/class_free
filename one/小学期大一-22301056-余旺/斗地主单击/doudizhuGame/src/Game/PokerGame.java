package Game;

import java.lang.invoke.CallSite;
import java.util.*;

public class PokerGame {

    //确保无论打多少局斗地主都只有一准备的牌
    static ArrayList<Integer> list=new ArrayList<>();

    //把牌和序号产生对应关系
    static HashMap<Integer,String> hm=new HashMap<>();




    //静态代码块,以此来表示每一张牌
    static {
        //准备的牌
        String[] color={"方片","梅花","黑桃","红桃"};
        String[] number={"3","4","5","6","7","8","9","10","J","Q","K","A","2"};

        //牌的序号
        int realNumber=1;

        //牌的具体表示
        for (String s : number) {
            //s表示每一张花色
            for (String s1 : color){
                //s1表示数字
                //进行组合拼接并加入到集合中
                hm.put(realNumber,s1+s);
                list.add(realNumber);
                realNumber++;
            }

        }
        //不要忘了小王和大王
        hm.put(realNumber,"小王");
        list.add(realNumber);
        realNumber++;
        hm.put(realNumber,"大王");
        list.add(realNumber);
        realNumber++;
    }


    //空参构造
    public PokerGame(){
        //洗牌,直接打乱序号的顺序
        Collections.shuffle(list);
        //System.out.println(list);

        //发牌，需要准备四个集合
        TreeSet<Integer> lord=new TreeSet<>();
        TreeSet<Integer> player1=new TreeSet<>();
        TreeSet<Integer> player2=new TreeSet<>();
        TreeSet<Integer> player3=new TreeSet<>();

        //遍历牌盒得到每一张牌
        for (int i = 0; i <list.size() ; i++) {
            //i代表索引
            int poker=list.get(i);
            //给底牌发牌
            if(i<3){
                lord.add(poker);
                continue;
            }
            //分别给三个玩家发牌
            if(i%3==0)
                player1.add(poker);
            else if (i%3==1) {
                player2.add(poker);
            }
            else
                player3.add(poker);

        }
//        System.out.println(lord);
//        System.out.println(player1);
//        System.out.println(player2);
//        System.out.println(player3);
        //执行看牌的流程
        lookPoker("底牌",lord);
        lookPoker("玩家1",player1);
        lookPoker("玩家2",player2);
        lookPoker("玩家3",player3);
    }
    //看牌
    public void lookPoker(String name,TreeSet<Integer> list){
        System.out.print(name+":");
        for (int poker : list) {
            System.out.print(hm.get(poker)+" ");
        }
        System.out.println();



    }
}
