package com.service;

import java.util.List;

import com.dao.UserDao;
import com.entity.UserDB;
import com.utils.PageTool;

//用户的业务层
public class UserService {
	
	
	private UserDao userDao = new UserDao();

	//用户的登录操作
	public UserDB login(String account, String password) {
		return userDao.login(account, password);
	}
	//分页操作的业务层
	public PageTool<UserDB> list(String currentPage, String pageSize, Integer order){
		return userDao.list(currentPage, pageSize, order);
	}
	
	 //添加用户的操作
		public Integer addUser(UserDB userDB) {
			return userDao.addUser(userDB);
		}
		
		//检验账户是否创建过而需要这个操作
		public List<UserDB> getList(UserDB userDB){
			return userDao.getList(userDB);
		}
		

//修改用户信息
		public Integer updUser(UserDB userDB) {
			return userDao.updUser(userDB);		
		}
	//删除用户信息
		public Integer delUser(Integer uid) {
			return userDao.delUser(uid);
		}

}
