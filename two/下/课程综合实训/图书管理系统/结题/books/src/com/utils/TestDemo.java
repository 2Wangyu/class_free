package com.utils;


import java.sql.SQLException;

import com.dao.BookDao;
import com.dao.HistoryDao;
import com.dao.UserDao;
import com.entity.BookDB;
import com.entity.HistoryDB;
import com.entity.UserDB;


public class TestDemo {


	public static void main(String[] args) throws SQLException {
		HistoryDao historyDao = new HistoryDao();
		HistoryDB historyDB = new HistoryDB();
		historyDB.setHid(1);
		historyDB.setStatus(2);
		System.out.println(historyDao.updHistory(historyDB, C3p0Tool.getConnection()));
	}
}
