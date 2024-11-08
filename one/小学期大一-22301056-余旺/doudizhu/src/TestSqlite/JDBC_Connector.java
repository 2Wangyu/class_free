package TestSqlite;
import java.sql.*;

//数据库的使用
public class JDBC_Connector {
        static int n=1;
        Connection c=null;
        Statement statement =null;
        private String name;
        private String password;
        private int happybean;
        public JDBC_Connector(String name,String password,int happybean){
                this.name=name;
                this.password=password;
                this.happybean=happybean;
        }
        public void add() throws ClassNotFoundException {
                try {
                        //显示玩的日期
                        String date=new String("2023-07-25");
                        //连接到数据库当中
                        Class.forName("org.sqlite.JDBC");
                        c = DriverManager.getConnection("jdbc:sqlite:"+"D:\\桌面\\sqlite\\User.db");
                        c.setAutoCommit(false);
                        statement = c.createStatement();
                        //sql的形式添加进去
                        String sql="insert into User" +"(name,password,happybean,date) values('"+name+"','"+password+"','"+happybean+"','"+date+"')";
                        n++;
                        statement.executeUpdate(sql);


                        //关闭
                        statement.close();
                        c.commit();
                        c.close();
                } catch ( Exception e ) {
                        System.err.println( e.getClass().getName() + ": " + e.getMessage() );
                        System.exit(0);
                }
        }
        public void check(){
                try {
                        //和数据库相互连接
                        Class.forName("org.sqlite.JDBC");
                        c = DriverManager.getConnection("jdbc:sqlite:"+"D:\\桌面\\sqlite\\User.db");
                        c.setAutoCommit(false);

                        statement = c.createStatement();
                        ResultSet rs = statement.executeQuery( "SELECT * FROM User;" );
                        // System.out.println("Name/t/t/t/t");
                        //遍历数据库中的内容
                        while ( rs.next() ) {
                                //Integer id = rs.getInt("id");
                                String name = rs.getString("name");
                                String password = rs.getString("password");
                                Double happybean = rs.getDouble("happybean");
                                String date=rs.getString("date");
                                System.out.println( "Name: " + name + " Password: " + password + " Happybean: " + happybean+" Date:"+date);
                        }
                        rs.close();
                        statement.close();
                        c.close();
                } catch ( Exception e ) {
                        System.err.println( e.getClass().getName() + ": " + e.getMessage() );
                        System.exit(0);
                }
        }
//        public static void main(String[] args)  {
//                        JDBC_Connector a=new JDBC_Connector("yu","wang",1000);
//                        a.check();
//
//        }
}





