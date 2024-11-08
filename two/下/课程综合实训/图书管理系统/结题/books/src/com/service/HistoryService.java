package com.service;

import java.sql.SQLException;



import com.dao.HistoryDao;
import com.entity.HistoryDB;
import com.utils.PageTool;


public class HistoryService {
	
	private HistoryDao historyDao = new HistoryDao();

	public PageTool<HistoryDB> listByPage(String currentPage, String pageSize, Integer uid, Integer status){
		return historyDao.listByPage(currentPage, pageSize, uid, status);
	}
	
	//还书延期
	public Integer updHistory(HistoryDB historyDB) throws SQLException {
		return historyDao.updHistory(historyDB);
	}
}
