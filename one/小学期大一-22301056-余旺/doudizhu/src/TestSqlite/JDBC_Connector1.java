package TestSqlite;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

//用于写入每个玩家的出牌逻辑
public class JDBC_Connector1 {

    Connection c=null;
    Statement statement =null;
    private static JDBC_Connector1 jdbcConnector1=null;
    public static JDBC_Connector1 getInstance(){
        if(jdbcConnector1==null)
        {
            jdbcConnector1=new JDBC_Connector1();

        }
        return jdbcConnector1;
    }
    public void add(String name,String content) throws ClassNotFoundException {

        try {
            //显示玩的日期
            String date=new String("2023-07-25");
            //连接到数据库当中
            Class.forName("org.sqlite.JDBC");
            c = DriverManager.getConnection("jdbc:sqlite:"+"D:\\桌面\\sqlite\\Userlogic.db");
            c.setAutoCommit(false);
            statement = c.createStatement();
            //sql的形式添加进去
            String sql="insert into Userlogic" +"(name,content,date) values('"+name+"','"+content+"','"+date+"')";

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
            c = DriverManager.getConnection("jdbc:sqlite:"+"D:\\桌面\\sqlite\\Userlogic.db");
            c.setAutoCommit(false);

            statement = c.createStatement();
            ResultSet rs = statement.executeQuery( "SELECT * FROM Userlogic;" );
            // System.out.println("Name/t/t/t/t");
            //遍历数据库中的内容
            while ( rs.next() ) {
                //Integer id = rs.getInt("id");
                String name = rs.getString("name");
                String content= rs.getString("content");
                String date=rs.getString("date");
                System.out.println( "Name: " + name + " Content: " + content+" Date:"+date);
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
//            try {
//                JDBC_Connector1.getInstance().add("123","456");
//                JDBC_Connector1.getInstance().check();
//            } catch (ClassNotFoundException e) {
//                throw new RuntimeException(e);
//            }
//
//        }
}

