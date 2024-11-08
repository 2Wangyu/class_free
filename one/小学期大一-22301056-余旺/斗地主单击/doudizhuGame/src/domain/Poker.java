package domain;

import Game.GameJFrame;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class Poker extends JLabel implements MouseListener {
    //牌的名字
    String name;
    //牌显示正面还是反面
    boolean up;
    //是否可点击
    boolean canClick = false;
    //当前状态，
    boolean clicked = false;


    //每个用户的游戏的主界面
    GameJFrame gameJFrame;

    public Poker(GameJFrame m, String name, boolean up) {
        this.gameJFrame = m;
        this.name = name;
        this.up = up;
        //判断当前的牌是显示正面还是背面
        //true代表是自己的牌显示正面，否则显示背面
        if (this.up){
            this.turnFront();
        }else {
            this.turnRear();
        }
        //设置牌的宽高大小
        this.setSize(71, 96);
        //把牌显示出来
        this.setVisible(true);
        //给每一张牌添加鼠标监听
        this.addMouseListener(this);
    }

    //显示正面牌是可以点击的
    public void turnFront(){
        //已经将牌的名字和图片名称相互对应了
        this.setIcon(new ImageIcon("D:\\桌面\\斗地主\\doudizhuGame\\image\\poker\\"+name+".png"));
        this.up=true;
    }
    //背面的牌是不可以点击的
    public void turnRear(){
        this.setIcon(new ImageIcon("D:\\桌面\\斗地主\\doudizhuGame\\image\\poker\\rear.jpg"));
        this.up=false;
    }




    //鼠标点击卡牌会让卡牌移动，只有牌面才可以移动卡牌
    @Override
    public void mouseClicked(MouseEvent e) {
        if(canClick){
         //获取当前牌的位置信息
            Point now=this.getLocation();
            //代表当前卡牌的移动情况
            int step;
            if(clicked){
                step=20;
            }
            else{
                step=-20;
            }
            clicked=!clicked;
            Point toPoint=new Point(now.x,now.y+step);
            this.setLocation(toPoint);
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public void setName(String name) {
        this.name = name;
    }

    public boolean isUp() {
        return up;
    }

    public void setUp(boolean up) {
        this.up = up;
    }

    public boolean isCanClick() {
        return canClick;
    }

    public void setCanClick(boolean canClick) {
        this.canClick = canClick;
    }

    public boolean isClicked() {
        return clicked;
    }

    public void setClicked(boolean clicked) {
        this.clicked = clicked;
    }

    public GameJFrame getGameJFrame() {
        return gameJFrame;
    }

    public void setGameJFrame(GameJFrame gameJFrame) {
        this.gameJFrame = gameJFrame;
    }

    @Override
    public String toString() {
        return "Poker{" +
                "name='" + name + '\'' +
                ", up=" + up +
                ", canClick=" + canClick +
                ", clicked=" + clicked +
                ", gameJFrame=" + gameJFrame +
                '}';
    }
}
