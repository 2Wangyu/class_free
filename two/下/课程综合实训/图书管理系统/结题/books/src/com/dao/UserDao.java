package com.dao;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;

import org.apache.commons.dbutils.BasicRowProcessor;
import org.apache.commons.dbutils.BeanProcessor;
import org.apache.commons.dbutils.GenerousBeanProcessor;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.RowProcessor;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;
import org.junit.Test;

import com.entity.UserDB;
import com.utils.C3p0Tool;
import com.utils.PageTool;

//这一部分都是后端的代码
//用户的数据连接层

public class UserDao {
	
	QueryRunner queryRunner = new QueryRunner(C3p0Tool.getDataSource());
	//开启驼峰自动转换，解决无法成功查询数据的问题，即数据库名称和这里定义的实体类中的名字是不是一模一样的
	BeanProcessor bean = new GenerousBeanProcessor();
	RowProcessor processor = new BasicRowProcessor(bean);
	
	//@Test,用于测试
	//用户登录操作
	public UserDB login(String account, String password) {
		//String sql = "select * from t_user where uid=1";
			
		String sql = "select * from t_user where account = ? and password = ?";
		Object[] params = {account, password};
		try {
			//processor参数支持名称不完全统一
			return queryRunner.query(sql, new BeanHandler<UserDB>(UserDB.class, processor), params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
		
		
	}	
	
	//获取用户，以便于校验是否有重复的用户进行创建
	public List<UserDB> getList(UserDB userDB){
		String sql = "select * from t_user where account = ?";
		Object[] params = {userDB.getAccount()};
		try {
			return queryRunner.query(sql, new BeanListHandler<UserDB>(UserDB.class, processor),params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	//更新图书的借阅信息，借书的次数和最大的借阅量会进行改变
	public Integer updNum(UserDB userDB, Connection conn) throws SQLException {
		QueryRunner qr = new QueryRunner();
		String sql = "update t_user set times = ?, max_num = ? where uid = ?";
		Object[] params = {userDB.getTimes(),userDB.getMaxNum(),userDB.getUid()};
		return qr.update(conn, sql, params);
	}
	
	
	
	
	
	//@Test
	//删除用户的操作
	public int delUser(Integer uid) {
		String sql = "delete from t_user where uid = ?";
		Object[] params = {uid};
		try {
			//用于测试
//			int i=queryRunner.update(sql);
//			System.out.println(i);
			
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return -1;
	}
	
	
	 //用户列表 分页
	
	public PageTool<UserDB> list(String currentPage, String pageSize, Integer order){
		//String sql="select * from t_user";
		
		try {
			StringBuffer listSql = new StringBuffer("select * ");
			StringBuffer countSql = new StringBuffer("select count(*) ");
			StringBuffer sql = new StringBuffer("from t_user");
			
			//用于最多借阅图书用户的查找
			if (order != null && order == 1) {
				sql.append(" where role = 1 order by times desc");
			}
			//获取总记录数，即数据库中一共存了多少条记录
			Long total = queryRunner.query(countSql.append(sql).toString(), new ScalarHandler<Long>());
			
			//初始化分页工具
			PageTool<UserDB> pageTools = new PageTool<UserDB>(total.intValue(), currentPage, pageSize);
			
			//两个参数，currentpage,pageSize
		     sql.append(" limit ?,?");
			
		     //当前页的数据		
			 List<UserDB> list = queryRunner.query(listSql.append(sql).toString(), new BeanListHandler<UserDB>(UserDB.class, processor),pageTools.getStartIndex(),pageTools.getPageSize());
			 pageTools.setRows(list);
			 //用于测试
			 System.out.println(pageTools);
			 
			 return pageTools;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		//return 0查询记录总数为0
		return new PageTool<UserDB>(0, currentPage, pageSize);
	}
	
//添加用户的操作
	public Integer addUser(UserDB userDB) {
		//这里的名称必须与数据库一致，这是最终的调试的时候的发现的错误
		String sql = "insert into t_user (account,password,name,phone,times,lend_num,max_num,role) values (?,?,?,?,?,?,?,?)";
		Object[] params = {userDB.getAccount(),userDB.getPassword(),userDB.getName(),userDB.getPhone(),userDB.getTimes(),userDB.getLendNum(),userDB.getMaxNum(),userDB.getRole()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	//由管理员操作用户的信息修改，不能够修改他的密码
	public Integer updUser(UserDB userDB) {
		String sql = "update t_user set phone = ?, lend_num = ?, max_num = ? where uid = ?";
		Object[] params = {userDB.getPhone(),userDB.getLendNum(),userDB.getMaxNum(),userDB.getUid()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	
	
}
