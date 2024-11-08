package Client;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class StartJFrame extends JFrame implements MouseListener {



    //注册和菜单按钮
    JButton menu=new JButton();
    JButton register = new JButton();
    JTextField username=new JTextField();
    JPasswordField password = new JPasswordField();
    int x = 450;
    int y = 210;
    int width = 633;
    int height = 353;
    public StartJFrame(int x, int y){
        this.x = x;
        this.y = y;
    }

    public void show(Player player) {

        //初始化界面
        initJFrame();
        //添加内容
        initView();
        this.setVisible(true);


    }
    public void initView() {
        //添加用户名
        Font usernameFont = new Font(null,1,16);
        JLabel usernameText = new JLabel("用户名");
        usernameText.setForeground(Color.white);
        usernameText.setFont(usernameFont);
        usernameText.setBounds(140, 55, 55, 22);
        this.getContentPane().add(usernameText);

        //添加用户名输入框
        username.setBounds(223, 46, 200, 30);
        this.getContentPane().add(username);


        //添加密码文字
        JLabel passwordText = new JLabel("密码");
        Font passwordFont = new Font(null,1,16);
        passwordText.setForeground(Color.white);
        passwordText.setFont(passwordFont);
        passwordText.setBounds(197, 95, 40, 22);
        this.getContentPane().add(passwordText);

        //密码输入框
        password.setBounds(263, 87, 160, 30);
        this.getContentPane().add(password);

        //添加菜单按钮

        menu.setBounds(123, 210, 128, 47);
        menu.setIcon(new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\login\\菜单按钮.png"));
        //去除按钮的边框
        menu.setBorderPainted(false);
        //去除按钮的背景
        menu.setContentAreaFilled(false);
        //给登录按钮绑定动作事件
        menu.addMouseListener(this);
        this.getContentPane().add(menu);


        //添加注册按钮
        register.setBounds(256, 210, 128, 47);
        register.setIcon(new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\login\\注册按钮.png"));
        //去除按钮的边框
        register.setBorderPainted(false);
        //去除按钮的背景
        register.setContentAreaFilled(false);
        //给注册按钮绑定鼠标事件
        register.addMouseListener(this);
        this.getContentPane().add(register);


        //7.添加背景图片
        JLabel background = new JLabel(new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\login\\background.jpg"));
        background.setBounds(0, 0, 633, 323);
        this.getContentPane().add(background);


    }

    public void initJFrame() {
        this.setSize(633,353);//设置大小
        this.setTitle("联机斗地主登录");//设置标题
        this.setDefaultCloseOperation(3);//关闭模式
        this.setAlwaysOnTop(true);//优先显示，除非关闭或者成功登录
        this.setLayout(null);//取消内部默认设置
    }

    @Override
    public void mouseClicked(MouseEvent e) {
//        if (e.getSource() == login) {
//            System.out.println("点击了登录按钮");
//            //获取两个文本输入框中的内容
//            String usernameInput = username.getText();
//            String passwordInput = password.getText();
//
//            //判断用户名和密码是否为空
//            if (usernameInput.length() == 0 || passwordInput.length() == 0) {
//                showJDialog("用户名或者密码为空");
//                return;
//            }
//
//            //判断集合中是否包含当前用户对象
//            //其实就是验证用户名和密码是否相同
//            //contains底层是依赖equals方法判断的，所以需要重写equals方法
//            User userInfo = new User(usernameInput, passwordInput);
//            if (StartJFrame.allUsers.contains(userInfo)) {
//                Player.name=usernameInput;
//                //关闭当前登录界面
//                this.setVisible(false);
//                //打开游戏的主界面
//                Player.inStartJFrame=false;
//            } else {
//                showJDialog("用户名或密码错误");
//            }
//
//
//
//        }
        if (e.getSource() == register) {
            System.out.println("点击了注册按钮");

//            for (int i = 0; i < StartJFrame.allUsers.size() ; i++) {
//                String s=StartJFrame.allUsers.get(i).getUsername();
//                if(s.equals(username.getText())){
//                    showJDialog("该用户名已经被注册");
//                    return;
//                }
//            }
            //判断用户名和密码是否为空
            if (username.getText().length() == 0 || password.getText().length() == 0) {
                showJDialog("用户名或者密码为空");
                return;
            }
            User.getInstance().setUsername(username.getText());
            User.getInstance().setPassword(password.getText());

            showJDialog("注册成功！");
            this.setVisible(false);
            Player.inStartJFrame=false;



        } else  {
            //创建一个弹框对象
            JDialog jDialog = new JDialog();
            //给弹框设置大小
            jDialog.setSize(600, 300);
            //让弹框置顶
            jDialog.setAlwaysOnTop(true);
            //让弹框居中
            jDialog.setLocationRelativeTo(null);
            //弹框不关闭永远无法操作下面的界面
            jDialog.setModal(true);

            //创建Jlabel对象管理文字并添加到弹框当中
           JTextArea jTextArea=new JTextArea("Menu");
            jTextArea.setBounds(0, 0, 600, 300);
            jTextArea.setText("这是一个三人联机的斗地主游戏，注册好您的账户后\n"+
                    "您可以选择房间进入，房间满三人后将无法进入"+"\n" +
                    "您可以随时看到其他玩家进入房间的情况和准备情况，\n"+
                    "您也可以退出房间，当三人进入房间且准备后将开始游戏\n"
                    +"开始发牌并抢地主，根据点数大的获得地主牌，都是0分则重新发牌\n"+
                    "地主获得三张底牌，底牌会公示，剩余两人联盟对抗地主，先出完牌者获胜\n"+
                    "斗地主胜利获得40欢乐豆，农民胜利获得20欢乐豆，将会保存你的数据至数据库，并且以word文档导出\n"+
                    "祝您游戏愉快");
            jDialog.getContentPane().add(jTextArea);
            //让弹框展示出来
            jDialog.setVisible(true);

    }}


    public void showJDialog(String content) {
        //创建一个弹框对象
        JDialog jDialog = new JDialog();
        //给弹框设置大小
        jDialog.setSize(200, 150);
        //让弹框置顶
        jDialog.setAlwaysOnTop(true);
        //让弹框居中
        jDialog.setLocationRelativeTo(null);
        //弹框不关闭永远无法操作下面的界面
        jDialog.setModal(true);

        //创建Jlabel对象管理文字并添加到弹框当中
        JLabel warning = new JLabel(content);
        warning.setBounds(0, 0, 200, 150);
        jDialog.getContentPane().add(warning);
        //让弹框展示出来
        jDialog.setVisible(true);


    }


    //按下不松

    @Override
    public void mousePressed(MouseEvent e) {
     //   if (e.getSource() == login) {
       //     login.setIcon(new ImageIcon("Client/img/tool/login/登录按下.png"));
         if (e.getSource() == register) {
            register.setIcon(new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\login\\注册按下.png"));
        }
    }
    //松开按钮
    @Override
    public void mouseReleased(MouseEvent e) {

//        if (e.getSource() == login) {
//            login.setIcon(new ImageIcon("Client/img/tool/login/登录按钮.png"));
//        }
        if (e.getSource() == register) {
            register.setIcon(new ImageIcon("D:\\workspace\\doudizhu\\src\\Client\\img\\tool\\login\\注册按钮.png"));
        }
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }




    public void close() {
        this.setVisible(false);
    }

    public void open() {
        this.setVisible(true);
    }
    public int[] getLocate(){
        Rectangle locate =this.getBounds();
        int[] point = new int[2];
        point[0] = locate.x;
        point[1] = locate.y;
        return point;
    }
}
