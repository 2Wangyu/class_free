package Client;

import java.util.Objects;
//单例化，每一个客户端仅仅允许有一个用户
//用于储存所有玩家的个人信息，姓名，密码和欢乐豆数量
public class User {
    private String username;
    private String password;
    //对于欢乐豆的数量默认为200，
    // 农民输掉豆子20，赢豆子加20
    // 地主输了输掉40豆子，赢获得40豆子
    private int happybeen=1000;

    public int getHappybeen() {
        return happybeen;
    }

    public void setHappybeen(int happybeen) {
        this.happybeen = happybeen;
    }

    private User() {

    }

    private static User user=null;
    public static  User getInstance(){
        if(user==null)
        {
            user=new User();

        }
        return user;
    }





    public String getUsername() {
        return username;
    }


    public void setUsername(String username) {
        this.username = username;
    }


    public String getPassword() {
        return password;
    }


    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return Objects.equals(username, user.username) && Objects.equals(password, user.password);
    }

    @Override
    public int hashCode() {
        return Objects.hash(username, password);
    }


}


