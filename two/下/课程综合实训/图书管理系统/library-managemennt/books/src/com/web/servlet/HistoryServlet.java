package com.web.servlet;

import java.io.IOException;

import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.entity.HistoryDB;
import com.entity.UserDB;
import com.service.HistoryService;
import com.utils.DateUtils;
import com.utils.PageTool;
import com.utils.PaginationUtils;

//借阅记录
@WebServlet("/history")
public class HistoryServlet extends BaseServlet {

	private static final long serialVersionUID = 1L;
	
	private HistoryService historyService = new HistoryService();

//查询正在借书的图书
	public void list(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		UserDB userDB = (UserDB) request.getSession().getAttribute("userDB");
		//根据当前登陆的用户获取角色
		Integer role = userDB.getRole();
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		//普通用户只能查询自己的  管理员查询所有  
		PageTool<HistoryDB> pageTool = null;
		if (role == 1) {
			//普通用户
			pageTool = historyService.listByPage(currentPage, pageSize, userDB.getUid(), 1);
		} else {
			//管理员
			pageTool = historyService.listByPage(currentPage, pageSize, null, 1);
		}		
		String path = "history?method=list";
		//生成前端分页按钮
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(), path);
		request.setAttribute("pagation", pagation);
		request.setAttribute("hList", pageTool.getRows());
		//根据role判断跳转的页面
		if (role == 1) {
			//普通用户
			request.getRequestDispatcher("user/borrow.jsp").forward(request, response);
		} else {
			//管理员
			request.getRequestDispatcher("admin/admin_borrow.jsp").forward(request, response);
		}
		
	}
	
	//查询归还的图书
	public void backList(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		UserDB userDB = (UserDB) request.getSession().getAttribute("userDB");
		//根据当前登陆的用户获取角色
		Integer role = userDB.getRole();
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		//普通用户只能查询自己的  管理员查询所有  
		PageTool<HistoryDB> pageTool = null;
		if (role == 1) {
			//普通用户
			pageTool = historyService.listByPage(currentPage, pageSize, userDB.getUid(), 2);
		} else {
			//管理员
			pageTool = historyService.listByPage(currentPage, pageSize, null, 2);
		}		
		String path = "history?method=backList";
		//生成前端分页按钮
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(), path);
		request.setAttribute("pagation", pagation);
		request.setAttribute("hList", pageTool.getRows());
		//根据role判断跳转的页面
		if (role == 1) {
			//普通用户
			request.getRequestDispatcher("user/history.jsp").forward(request, response);
		} else {
			//管理员
			request.getRequestDispatcher("admin/admin_history.jsp").forward(request, response);
		}
		
	}
	
//还书延期的功能
	public void delay(HttpServletRequest request, HttpServletResponse response) throws SQLException, ServletException, IOException {
		String hid = request.getParameter("hid");
		String endTime = request.getParameter("endtime");
		HistoryDB historyDB = new HistoryDB();
		historyDB.setHid(Integer.parseInt(hid));
		historyDB.setEndTime(DateUtils.stringToDate(endTime));
		historyService.updHistory(historyDB);
		request.getRequestDispatcher("history?method=list").forward(request, response);
	}
}
