package com.service;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.Date;
import java.util.List;

import com.dao.BookDao;
import com.dao.HistoryDao;
import com.dao.UserDao;
import com.entity.BookDB;
import com.entity.HistoryDB;
import com.entity.UserDB;
import com.utils.C3p0Tool;
import com.utils.PageTool;
import com.utils.DateUtils;
import com.utils.MyException;



public class BookService {

	private BookDao bookDao = new BookDao();
	
	private HistoryDao historyDao = new HistoryDao();
	
	private UserDao userDao = new UserDao();
	
	//分页查询
	public PageTool<BookDB> listByPage(String currentPage, String pageSize, String word, Integer order){
		return bookDao.list(currentPage, pageSize, word, order);
	}
	
	//判断是否存在重复书
	public List<BookDB> list(String bookName){
		return bookDao.list(bookName, null);
	}
	//添加
	public Integer addBook(BookDB bookDB) {
		return bookDao.addBook(bookDB);
	}
	//upd
	public Integer updBook(BookDB bookDB) {
		return bookDao.updBook(bookDB);
	}
	//del
	public int delBook(String bid) {
		return bookDao.delBook(bid);
	}

	//借阅书籍
	public void borrowBook(UserDB userDB, String bid) {
		//获取连接，数据库的链接
		Connection conn = C3p0Tool.getConnection();
		
		
		try {
			//设置事物不自动提交
			conn.setAutoCommit(false);
			
			
			
			// 根据bid获取完整的
			List<BookDB> list = bookDao.list(null, bid);
			
			BookDB bookDB = list.get(0);
			
			//保证用户数据和数据库同步更新
			userDB = userDao.getList(userDB).get(0);
			
			// t_history 创建图书借阅历史记录
			HistoryDB historyDB = new HistoryDB();
			historyDB.setUid(userDB.getUid());
			historyDB.setName(userDB.getName());
			historyDB.setAccount(userDB.getAccount());
			historyDB.setBid(bookDB.getBid());
			historyDB.setBookName(bookDB.getBookName());
			Date d = new Date();
			historyDB.setBeginTime(d);
			historyDB.setEndTime(DateUtils.dateAdd(d, userDB.getLendNum()));//还书时间  借书时间 + lend_num
			historyDB.setStatus(1);
			historyDao.addHistory(historyDB, conn);
			
			// t_book 改变图书的库存  book.num--  book.times++
			Integer num = bookDB.getNum();
			//库存判断
			if (num <= 0) {
				throw new MyException("库存不足");
			}
			bookDB.setNum(--num);
			bookDB.setTimes(bookDB.getTimes() + 1);
			bookDao.changeNum(bookDB,conn);
			
			// t_user 改变用户图书借阅信息  user.times++   max_num--
			userDB.setTimes(userDB.getTimes() + 1);
			//可借阅数量判断
			if (userDB.getMaxNum() <= 0) {
				throw new MyException("借阅次数已满");
			}
			userDB.setMaxNum(userDB.getMaxNum() - 1);
			userDao.updNum(userDB,conn);
			//事物提交
			conn.commit();
		} catch (Exception e) {
			//事物回滚			
			try {
				conn.rollback();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			//判断自定义异常
			if (e instanceof MyException) {
				throw new MyException(e.getMessage());
			} else {
				e.printStackTrace();
				throw new MyException("借阅失败");
			}
		}
		
	}
	
	
	//归还书籍
	public void backBook(String hid) {
		//获取连接
		Connection conn = C3p0Tool.getConnection();
		try {
			//设置事物不自动提交
			conn.setAutoCommit(false);
			//根据hid获取historyDB, 修改status为2
			HistoryDB historyDB = historyDao.list(hid).get(0);
			historyDB.setStatus(2);
			historyDao.updHistory(historyDB, conn);
			
			//根据historyDB获取图书bid
			Integer bid = historyDB.getBid();
			//根据bid获取图书信息，修改库存 + 1
			BookDB bookDB = bookDao.list(historyDB.getBookName(), bid+"").get(0);
			bookDB.setNum(bookDB.getNum() + 1);
			bookDao.changeNum(bookDB, conn);
			
			//根据historyDB获取用户account
			String account = historyDB.getAccount();
			//根据uid获取用户信息,修改max_num +1
			UserDB userDB = new UserDB();
			userDB.setAccount(account);
			userDB = userDao.getList(userDB).get(0);
			userDB.setMaxNum(userDB.getMaxNum() + 1);
			userDao.updNum(userDB, conn);
			//事物提交
			conn.commit();
		} catch (Exception e) {
			//事物回滚			
			try {
				conn.rollback();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			//判断自定义异常
			if (e instanceof MyException) {
				throw new MyException(e.getMessage());
			} else {
				e.printStackTrace();
				throw new MyException("还书失败");
			}
		}
		
	}
}
