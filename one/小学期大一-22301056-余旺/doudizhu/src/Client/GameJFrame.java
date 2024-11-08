package Client;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static java.lang.Thread.*;

public class GameJFrame {
    //加入音乐特效
    Music bgm=new Music("D:\\workspace\\doudizhu\\src\\Client\\music\\bgm (1).wav");

    Player player;
    ArrayList<Integer> card = new ArrayList<>();
    JLayeredPane layeredPane = new JLayeredPane();
    JFrame frame = new JFrame("游戏界面");
    ImageIcon bg = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\desk.jpg");
    JPanel back;//背景

    JPanel front = new JPanel();//按钮之类
    //和抢地主相关的
    ImageIcon _noCall = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\0.png");
    ImageIcon _one = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\1.png");
    ImageIcon _two = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\2.png");
    ImageIcon _three = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\3.png");
    JButton noCall = new JButton();
    JButton one = new JButton();
    JButton two = new JButton();
    JButton three = new JButton();
    //出牌阶段的
    JButton chupai = new JButton();
    JButton buchu = new JButton();
    //人物出牌后的信息
    JLabel notice = new JLabel("", JLabel.CENTER);
    ImageIcon GG = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\GG.png");
    ImageIcon GG_lord1 = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\GG_lord1.png");
    ImageIcon GG_lord2 = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\GG_lord2.png");
    ImageIcon chupai_btn = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\chupai.png");
    ImageIcon chupai_false_btn = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\chupai_false.png");
    ImageIcon buchu_btn = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\buchu.png");
    JLabel player1 = new JLabel(GG);
    JLabel player2 = new JLabel(GG);
    JPanel p1 = new JPanel();
    JPanel p2 = new JPanel();
    JLabel player1_num = new JLabel();//玩家手牌数,和玩家抢的点数
    JLabel player2_num = new JLabel("", SwingConstants.LEFT);
    //牌背
    ImageIcon poker_back = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\poker_back.png");
    JPanel dipai = new JPanel();
    JLabel dipai_1 = new JLabel("", JLabel.CENTER);
    JLabel dipai_2 = new JLabel("", JLabel.CENTER);
    JLabel dipai_3 = new JLabel("", JLabel.CENTER);
    JPanel btn_group = new JPanel();//抢点数按钮
    JPanel btn_group2 = new JPanel();//出牌按钮
    Font font = new Font("宋体", Font.BOLD, 20);
    Font font2 = new Font("宋体", Font.BOLD, 16);
    private String player1_id = "-1";
    private String player2_id = "-1";
    private int player1_deckNum;
    private int player2_deckNum;
    int x = 450;
    int y = 210;
    int width = 650;
    int height = 450;
    private String robLord = "-1";
    private Boolean isOutCards = false;
    ImageIcon[] images = new ImageIcon[15];//卡牌图片
    ImageIcon[] smallImages = new ImageIcon[15];//小图片
    private int last_cardNum = 0;//出牌区上次的卡牌数
    private int last_haveCards = 0;//手牌区上次手牌数量

    public GameJFrame(int x, int y, Player player) {
        //当打开界面的时候开始播放音乐
        bgm.setLoop(true);
        bgm.setVolumn(-20).play();


        this.player = player;
        this.x = x;
        this.y = y;
        notice.setForeground(Color.white);
        notice.setFont(font);

        player1_num.setForeground(Color.white);
        player2_num.setForeground(Color.white);
        player1_num.setFont(font2);
        player2_num.setFont(font2);

        chupai.setContentAreaFilled(false);
        buchu.setContentAreaFilled(false);
        chupai.setBorder(null);
        buchu.setBorder(null);
        buchu.setIcon(buchu_btn);
        chupai.setIcon(chupai_false_btn);

        //按钮的动作事件
        chupai.addActionListener(e -> {
            //出牌时候的音乐特效
            isOutCards = true;
            bgm.over();
            Music out=new Music("D:\\workspace\\doudizhu\\src\\Client\\music\\出牌.wav");
            out.setVolumn(6f).play();
            bgm.setVolumn(-20).setLoop(true).play();

            front.remove(btn_group2);
        });

        buchu.addActionListener(e -> {
            //
            if (CompareCard.getInstance().getPlayer().equals("m")) {
                JOptionPane.showMessageDialog(null, "必须出牌");
            } else {
                for (Integer i : card) {
                    labels[i].setLocation(labels[i].getX(), labels[i].getY() + 20);
                }
                card.clear();
                isOutCards = true;
                //不出牌的音乐特效
                bgm.over();
                Music no=new Music("D:\\workspace\\doudizhu\\src\\Client\\music\\不要.wav");
                no.setVolumn(6f).play();
                bgm.setVolumn(-20).setLoop(true).play();

                front.remove(btn_group2);
            }
        });
        btn_group2.setOpaque(false);

        //开启游戏后除非关闭程序否则不让提前退出游戏
        frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                JOptionPane.showMessageDialog(null, "请完成这一局游戏");

            }
        });
        //所以的牌
        images[0] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\A.jpg");
        images[1] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\2.jpg");
        images[2] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\3.jpg");
        images[3] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\4.jpg");
        images[4] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\5.jpg");
        images[5] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\6.jpg");
        images[6] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\7.jpg");
        images[7] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\8.jpg");
        images[8] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\9.jpg");
        images[9] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\10.jpg");
        images[10] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\J.jpg");
        images[11] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\Q.jpg");
        images[12] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\K.jpg");
        images[13] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\small.jpg");
        images[14] = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\poker\\big.jpg");
        for (int i = 0; i < 15; i++) {
            smallImages[i] = new ImageIcon();
            smallImages[i].setImage(images[i].getImage().getScaledInstance(images[i].getIconWidth() * 3 / 4,
                    images[i].getIconHeight() * 3 / 4, Image.SCALE_FAST));
        }

        //底牌水平放置
        dipai.setLayout(new GridLayout(1, 11));
        for (int i = 0; i < 4; i++) {
            dipai.add(new JLabel());
        }
        dipai.add(dipai_1);
        dipai.add(dipai_2);
        dipai.add(dipai_3);
        for (int i = 0; i < 4; i++) {
            dipai.add(new JLabel());
        }
        //开始的界面是以牌背展示出来
        dipai_1.setIcon(poker_back);
        dipai_2.setIcon(poker_back);
        dipai_3.setIcon(poker_back);
        dipai.setOpaque(false);
    }





    //显示窗口
    public void showGame() {
        back = (JPanel) frame.getContentPane();
        bg.setImage(bg.getImage().getScaledInstance(width, height, Image.SCALE_DEFAULT));
        JLabel b = new JLabel(bg);
        //出牌与否
        btn_group2.add(chupai);
        btn_group2.add(buchu);

        back.setOpaque(false);
        back.add(b);

        //几个玩家的信息
        p1.add(player1);
        p1.add(player1_num);

        p2.add(player2_num);
        p2.add(player2);
        p1.setOpaque(false);
        p2.setOpaque(false);

        layeredPane.add(back, JLayeredPane.DEFAULT_LAYER);
        frame.setBounds(x, y, width, height);
        front.setLayout(new BorderLayout());
        front.setBounds(0, 0, width, height);
        front.setBorder(BorderFactory.createEmptyBorder(0, 10, 160, 30));
        front.add(p1, BorderLayout.WEST);
        front.add(p2, BorderLayout.EAST);

        //抢地主的时候四个按钮
        noCall.addActionListener(e -> this.robLord = "0");
        one.addActionListener(e -> this.robLord = "1");
        two.addActionListener(e -> this.robLord = "2");
        three.addActionListener(e -> this.robLord = "3");

        btn_group.setOpaque(false);
        front.add(btn_group, BorderLayout.SOUTH);
        front.add(dipai, BorderLayout.NORTH);
        front.setOpaque(false);
        front.add(notice, BorderLayout.CENTER);
        layeredPane.add(front, JLayeredPane.MODAL_LAYER);
        notice.setText("等待其他玩家选择点数");

        frame.setResizable(false);
        frame.setLayeredPane(layeredPane);
        frame.setVisible(true);
    }


   //到底谁是地主
    public String returnNum(String num) throws InterruptedException {
        robLord = "-1";
        notice.setText("请选择你的点数");
        String[] str = num.split("");
        List<String> list = Arrays.asList(str);
        ArrayList<String> arr = new ArrayList<>(list);
        noCall.setContentAreaFilled(false);
        noCall.setBorder(null);
        noCall.setIcon(_noCall);
        btn_group.add(noCall);
        //根据那选择的点数进行展示
        if (arr.contains("1")) {
            one.setContentAreaFilled(false);
            one.setBorder(null);
            one.setIcon(_one);
            btn_group.add(one);
        }
        if (arr.contains("2")) {
            two.setContentAreaFilled(false);
            two.setBorder(null);
            two.setIcon(_two);
            btn_group.add(two);
        }
        if (arr.contains("3")) {
            three.setContentAreaFilled(false);
            three.setBorder(null);
            three.setIcon(_three);
            btn_group.add(three);
        }
        frame.invalidate();
        frame.repaint();
        frame.setVisible(true);
        while (this.robLord.equals("-1")) {
            sleep(10);
        }
        front.remove(btn_group);
        btn_group.remove(noCall);
        btn_group.remove(one);
        btn_group.remove(two);
        btn_group.remove(three);
        notice.setText("等待其他玩家选择点数");
        return this.robLord;
    }

    //加载底牌
    public void addLord(String s) {
        notice.setText("");
        String[] str = s.split("");
        ///dipai.setText(str[1] + str[2] + str[3]);设置底牌
        addIcon(dipai_1, str[1], this.smallImages);
        addIcon(dipai_2, str[2], this.smallImages);
        addIcon(dipai_3, str[3], this.smallImages);
        //底牌到底给谁由str第一个编号对应的角色来决定
        if (str[0].equals(player1_id)) {
            player1.setIcon(GG_lord1);
            this.player1_deckNum = 20;
            this.player2_deckNum = 17;
        }
        if (str[0].equals(player2_id)) {
            player2.setIcon(GG_lord2);
            this.player1_deckNum = 17;
            this.player2_deckNum = 20;
        }
        player1_num.setText(player1_deckNum + "张");
        player2_num.setText(player2_deckNum + "张");
    }

    //地主给自己加底牌的
    public void addSelf(String s) {
        notice.setText("");
        ImageIcon lord = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\lord.png");
        JLabel l = new JLabel(lord);
     //dipai.setText(s);设置底牌
        String[] str = s.split("");
        addIcon(dipai_1, str[0], this.smallImages);
        addIcon(dipai_2, str[1], this.smallImages);
        addIcon(dipai_3, str[2], this.smallImages);
        l.setBounds(0, height - lord.getIconHeight() - 50, lord.getIconWidth(), lord.getIconHeight());
        l.setOpaque(false);
        layeredPane.add(l);
        layeredPane.setLayer(l, 201);

        player1_deckNum = 17;
        player2_deckNum = 17;
        player1_num.setText(player1_deckNum + "张");
        player2_num.setText(player2_deckNum + "张");

    }
   //玩家的编号便于排版
    public void refresh(String dianshu) {
        String[] str = dianshu.split("");
        if (this.player1_id.equals("-1")) {
            this.player1_id = str[0];
            if (str[1].equals("0"))
                player1_num.setText("不叫");
            else if (str[1].equals("1"))
                player1_num.setText("1分");
            else if (str[1].equals("2"))
                player1_num.setText("2分");
            else
                player1_num.setText("3分");
            return;
        }
        this.player2_id = str[0];
        if (str[1].equals("0"))
            player2_num.setText("不叫");
        else if (str[1].equals("1"))
            player2_num.setText("1分");
        else if (str[1].equals("2"))
            player2_num.setText("2分");
        else
            player2_num.setText("3分");
    }

   // 地主胜利画面
    public void showLordWin() throws InterruptedException {
        //播放音乐
        bgm.over();
        Music win=new Music("D:\\workspace\\doudizhu\\src\\Client\\music\\win.wav");
        win.setLoop(false).setVolumn(-1).play();
        //展示图片
        ImageIcon lordWin = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\lord_win.png");
        JLabel label = new JLabel(lordWin);
        label.setBounds(width / 2 - lordWin.getIconWidth() / 2, height / 2 - lordWin.getIconHeight() / 2, lordWin.getIconWidth(), lordWin.getIconHeight());
        layeredPane.add(label);
        layeredPane.setLayer(label, 290);
        sleep(3000);
        System.exit(0);
    }


     //地主失败画面
    public void showLordLose() throws InterruptedException {
        //播放音乐
        bgm.over();
        Music lose=new Music("D:\\workspace\\doudizhu\\src\\Client\\music\\lose.wav");
        lose.setLoop(false).setVolumn(-1).play();

        ImageIcon lordLose = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\lord_lose.png");
        JLabel label = new JLabel(lordLose);
        label.setBounds(width / 2 - lordLose.getIconWidth() / 2, height / 2 - lordLose.getIconHeight() / 2, lordLose.getIconWidth(), lordLose.getIconHeight());
        layeredPane.add(label);
        layeredPane.setLayer(label, 290);
        sleep(3000);
        System.exit(0);
    }

    //农民胜利画面
    public void showFarmerWin() throws InterruptedException {
        //播放音乐
        bgm.over();
        Music win=new Music("D:\\workspace\\doudizhu\\src\\Client\\music\\win.wav");
        win.setLoop(false).setVolumn(-1).play();

        ImageIcon farmerWin = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\farmer_win.png");
        JLabel label = new JLabel(farmerWin);
        label.setBounds(width / 2 - farmerWin.getIconWidth() / 2, height / 2 - farmerWin.getIconHeight() / 2, farmerWin.getIconWidth(), farmerWin.getIconHeight());
        layeredPane.add(label);
        layeredPane.setLayer(label, 290);
        sleep(3000);
        System.exit(0);
    }

    //农民失败画面
    public void showFarmerLose() throws InterruptedException {
        //播放音乐
        bgm.over();
        Music lose=new Music("D:\\workspace\\doudizhu\\src\\Client\\music\\lose.wav");
        lose.setLoop(false).setVolumn(-1).play();


        ImageIcon farmerLose = new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\farmer_lose.png");
        JLabel label = new JLabel(farmerLose);
        label.setBounds(width / 2 - farmerLose.getIconWidth() / 2, height / 2 - farmerLose.getIconHeight() / 2, farmerLose.getIconWidth(), farmerLose.getIconHeight());
        layeredPane.add(label);
        layeredPane.setLayer(label, 290);
        sleep(3000);
        System.exit(0);

    }
     //出牌
    public String outCards() throws InterruptedException {
        chupai.setEnabled(false);
        this.front.add(btn_group2, BorderLayout.SOUTH);
        frame.validate();
        while (!this.isOutCards) {
            sleep(10);
        }
        this.isOutCards = false;
        StringBuilder stringBuilder = new StringBuilder();
        //实时的储存卡片
        if (this.card == null)
            return "";
        for (Integer i : this.card) {
            stringBuilder.append(player.getDeck().get(i));
        }
        card.clear();
        //取出牌堆
        for (JLabel label : labels) {
            layeredPane.remove(label);
        }
        frame.invalidate();
        frame.repaint();
        frame.setVisible(true);
        return stringBuilder.toString();
    }

    JLabel[] labels = new JLabel[20];

   //展示卡片
    public void printCards() {
        for (int i = 0; i < last_haveCards; i++) {
            layeredPane.remove(labels[i]);
        }
        this.last_haveCards = player.getDeck().size();
        for (int i = 0; i < 20; i++) {
            JLabel l = new JLabel();
            labels[i] = l;
        }

        int w = images[0].getIconWidth();
        int h = images[0].getIconWidth();
        int num = player.getDeck().size();
        int total_w = (num * w + 2 * w) / 3;
        int floor = 250;
        for (int i = 0; i < num; i++) {
            addIcon(labels[i], player.getDeck().get(i), this.images);
            labels[i].setBounds(width / 2 - total_w / 2 + i * w / 3, height / 2 + 70, w, h + 30);
            layeredPane.add(labels[i]);
            int finalI = i;
            //每一张图片添加鼠标点击的标签
            labels[i].addMouseListener(new MouseListener() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    //根据是否被点击过决定上下移动20个像素
                    if (!card.contains(finalI)) {
                        card.add(finalI);
                        labels[finalI].setLocation(labels[finalI].getX(), labels[finalI].getY() - 20);
                    } else {
                        card.remove((Integer) finalI);
                        labels[finalI].setLocation(labels[finalI].getX(), labels[finalI].getY() + 20);
                    }
                    CompareCard compareCard = CompareCard.getInstance();
                    StringBuilder stringBuilder = new StringBuilder();
                    //没牌不需出牌
                    if (card.size() == 0) {
                        chupai.setIcon(chupai_false_btn);
                        chupai.setEnabled(false);
                    } else {
                        for (Integer i : card) {
                            String s = player.getDeck().get(i);
                            stringBuilder.append(s);
                        }
                        //有牌还需要比较后确定是否可以出牌
                        if (compareCard.compare(stringBuilder.toString())) {
                            chupai.setIcon(chupai_btn);
                            chupai.setEnabled(true);
                        } else {
                            chupai.setIcon(chupai_false_btn);
                            chupai.setEnabled(false);
                        }
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
            });
            layeredPane.setLayer(labels[i], floor++);
            frame.invalidate();
            frame.repaint();
            frame.setVisible(true);
        }
    }

    JLabel[] playedCards = new JLabel[20];

    //展示对手的卡牌数量，对手出的牌
    public void printPlayedCards(String s) throws InterruptedException {
        String[] str = s.split("");
        if (str.length == 1) {
            pass(s);
            return;
        }
        for (int i = 0; i < this.last_cardNum; i++) {
            layeredPane.remove(playedCards[i]);
        }
        String p = str[0];
        List<String> list = Arrays.asList(s.substring(1, str.length).split(""));
        ArrayList<String> cards = new ArrayList<>(list);
        int bias = 130;
        int w = images[0].getIconWidth() * 3 / 4;
        int h = images[0].getIconWidth() * 3 / 4;
        int num = cards.size();
        System.out.println(num);//
        this.last_cardNum = num;
        int total_w = (num * w + 2 * w) / 3;
        int floor = 270;
        for (int i = 0; i < 20; i++) {
            playedCards[i] = new JLabel();
        }
        //根据每一个玩家的编号展示各自打出的牌
        for (int i = 0; i < num; i++) {
            addIcon(playedCards[i], cards.get(i), this.smallImages);
            if (p.equals("m"))
                playedCards[i].setBounds(width / 2 - total_w / 2 + i * w / 3, height / 2 - 65, w, h + 30);
            else if (p.equals(player1_id)) {
                playedCards[i].setBounds(bias + i * w / 3, height / 2 - 65, w, h + 30);
                player1_deckNum -= 1;
                player1_num.setText(player1_deckNum + "张");
            } else {
                playedCards[i].setBounds(width - bias - total_w + i * w / 3, height / 2 - 65, w, h + 30);
                player2_deckNum -= 1;
                player2_num.setText(player2_deckNum + "张");
            }
            layeredPane.add(playedCards[i]);
            layeredPane.setLayer(playedCards[i], floor++);
            bgm.over();
            Music out=new Music("D:\\workspace\\doudizhu\\src\\Client\\music\\出牌.wav");
            out.setVolumn(6f).play();
            bgm.setVolumn(-20).setLoop(true).play();
        }
        frame.invalidate();
        frame.repaint();
        frame.setVisible(true);
    }

    //点击过的时候展示过的图片
    public void pass(String s) throws InterruptedException {
        if (s.equals(player1_id)) {
            player1_num.setIcon(new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\pass.png"));
            bgm.over();
            Music no=new Music("D:\\workspace\\doudizhu\\src\\Client\\music\\不要.wav");
            no.setVolumn(6f).play();
            sleep(1000);
            player1_num.setIcon(null);
            bgm.setVolumn(-20).play();
        } else if (s.equals(player2_id)) {
            player2_num.setIcon(new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\pass.png"));
            bgm.over();
            Music no=new Music("D:\\workspace\\doudizhu\\src\\Client\\music\\不要.wav");
            no.setVolumn(6f).play();
            sleep(1000);
            player2_num.setIcon(null);
            bgm.setVolumn(-20).play();
        }

    }

    //根据牌添加图标
    public void addIcon(JLabel label, String card, ImageIcon[] images) {
        if (card.equals("A"))
            label.setIcon(images[0]);
        else if (card.equals("2"))
            label.setIcon(images[1]);
        else if (card.equals("3"))
            label.setIcon(images[2]);
        else if (card.equals("4"))
            label.setIcon(images[3]);
        else if (card.equals("5"))
            label.setIcon(images[4]);
        else if (card.equals("6"))
            label.setIcon(images[5]);
        else if (card.equals("7"))
            label.setIcon(images[6]);
        else if (card.equals("8"))
            label.setIcon(images[7]);
        else if (card.equals("9"))
            label.setIcon(images[8]);
        else if (card.equals("X"))
            label.setIcon(images[9]);
        else if (card.equals("J"))
            label.setIcon(images[10]);
        else if (card.equals("Q"))
            label.setIcon(images[11]);
        else if (card.equals("K"))
            label.setIcon(images[12]);
        else if (card.equals("w"))
            label.setIcon(images[13]);
        else
            label.setIcon(images[14]);
    }

    public void close() {
        frame.setVisible(false);
    }

    public int[] getLocate() {
        Rectangle locate = this.frame.getBounds();
        int[] point = new int[2];
        point[0] = locate.x;
        point[1] = locate.y;
        return point;
    }
}
