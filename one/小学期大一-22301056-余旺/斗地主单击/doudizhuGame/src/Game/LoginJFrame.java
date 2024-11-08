package Game;

import domain.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.ArrayList;

public class LoginJFrame extends JFrame implements MouseListener {

    static ArrayList<User> allUsers=new ArrayList<>();

    static {
        allUsers.add(new User("yuwang","123"));
    }
    //注册和登录按钮
    JButton login=new JButton();
    JButton register = new JButton();
    JTextField username=new JTextField();
    JPasswordField password = new JPasswordField();


    public LoginJFrame(){
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

        //添加登录按钮
        login.setBounds(123, 210, 128, 47);
        login.setIcon(new ImageIcon("D:\\桌面\\斗地主\\doudizhuGame\\image\\login\\登录按钮.png"));
        //去除按钮的边框
        login.setBorderPainted(false);
        //去除按钮的背景
        login.setContentAreaFilled(false);
        //给登录按钮绑定鼠标事件
        login.addMouseListener(this);
        this.getContentPane().add(login);

        //添加注册按钮
        register.setBounds(256, 210, 128, 47);
        register.setIcon(new ImageIcon("D:\\桌面\\斗地主\\doudizhuGame\\image\\login\\注册按钮.png"));
        //去除按钮的边框
        register.setBorderPainted(false);
        //去除按钮的背景
        register.setContentAreaFilled(false);
        //给注册按钮绑定鼠标事件
        register.addMouseListener(this);
        this.getContentPane().add(register);


        //7.添加背景图片
        JLabel background = new JLabel(new ImageIcon("D:\\桌面\\斗地主\\doudizhuGame\\image\\login\\background.jpg"));
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
        if (e.getSource() == login) {
            System.out.println("点击了登录按钮");
            //获取两个文本输入框中的内容
            String usernameInput = username.getText();
            String passwordInput = password.getText();

            //判断用户名和密码是否为空
            if (usernameInput.length() == 0 || passwordInput.length() == 0) {
                showJDialog("用户名或者密码为空");
                return;
            }

            //判断集合中是否包含当前用户对象
            //其实就是验证用户名和密码是否相同
            //contains底层是依赖equals方法判断的，所以需要重写equals方法
            User userInfo = new User(usernameInput, passwordInput);
            if (allUsers.contains(userInfo)) {
                //关闭当前登录界面
                this.setVisible(false);
                //打开游戏的主界面
                new GameJFrame();
            } else {
                showJDialog("用户名或密码错误");
            }
        } else if (e.getSource() == register) {
            System.out.println("点击了注册按钮");
            allUsers.add(new User(username.getText(),password.getText()));
            showJDialog("注册成功！");
            this.setVisible(false);
            new GameJFrame();
//
//            System.out.println(allUsers);
        }

        }


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
        if (e.getSource() == login) {
            login.setIcon(new ImageIcon("D:\\桌面\\斗地主\\doudizhuGame\\image\\login\\登录按下.png"));
        } else if (e.getSource() == register) {
            register.setIcon(new ImageIcon("D:\\桌面\\斗地主\\doudizhuGame\\image\\login\\注册按下.png"));
        }
    }
    //松开按钮
    @Override
    public void mouseReleased(MouseEvent e) {

        if (e.getSource() == login) {
            login.setIcon(new ImageIcon("D:\\桌面\\斗地主\\doudizhuGame\\image\\login\\登录按钮.png"));
        } else if (e.getSource() == register) {
            register.setIcon(new ImageIcon("D:\\桌面\\斗地主\\doudizhuGame\\image\\login\\注册按钮.png"));
        }
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }
}




