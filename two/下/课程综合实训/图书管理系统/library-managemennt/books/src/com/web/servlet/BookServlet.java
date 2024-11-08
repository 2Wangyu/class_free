package com.web.servlet;


import java.io.IOException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;

import com.google.gson.Gson;
import com.entity.BookDB;
import com.entity.TypeDB;
import com.entity.UserDB;
import com.service.BookService;
import com.service.TypeService;
import com.utils.PageTool;
import com.utils.PaginationUtils;
import com.utils.ResBean;


@WebServlet("/book")
public class BookServlet extends BaseServlet {
	
	private static final long serialVersionUID = 1L;
	
	private BookService bookService = new BookService();
	
	//获取图书的所有类别
	private TypeService typeService = new TypeService();

	//图书列表分页
	public void listByPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		//用来获取用户的身份信息
		UserDB userDB = (UserDB) request.getSession().getAttribute("userDB");
		
		
		//根据当前登陆的用户获取角色
		Integer role = userDB.getRole();
		
		//获取查询条件
		String word = request.getParameter("word");
		
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		PageTool<BookDB> pageTool = bookService.listByPage(currentPage, pageSize, word, null);
		
		//路径
		String path = "book?method=listByPage";
		
		//同样查询条件
		if (word != null && word != "") {
			path += "&word=" + word;
		}
		//生成前端分页按钮
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(), path);
		
		//获取所有的类别
		List<TypeDB> typeList = typeService.list(null, null);
		
		request.setAttribute("pagation", pagation);
		request.setAttribute("typeList", typeList);
		//查询条件不被清楚
		request.setAttribute("word", word);
		request.setAttribute("bList", pageTool.getRows());
		
		
		//根据role判断跳转的页面
		if (role == 1) {
			//普通用户
			request.getRequestDispatcher("user/select.jsp").forward(request, response);
		} else {
			//管理员
			request.getRequestDispatcher("admin/admin_book.jsp").forward(request, response);
		}
		
	}
	
	//whether 重复
	public void checkBook(HttpServletRequest request, HttpServletResponse response) throws IOException {
		String bookName = request.getParameter("bookName");
		List<BookDB> list = bookService.list(bookName);
		ResBean resBean = new ResBean();
		if (list != null && list.size() > 0) {
			resBean.setCode(400);
			resBean.setMsg("图书名称已存在");
		} else {
			resBean.setCode(200);
			resBean.setMsg("图书名称可以使用");
		}
		//将 resBean 转换成 json字符串
		Gson gson = new Gson();
		String json = gson.toJson(resBean);
		response.getWriter().print(json);
	}
	
	//add
	public void addBook(HttpServletRequest request, HttpServletResponse response) throws Exception {
		BookDB bookDB = new BookDB();
		BeanUtils.populate(bookDB, request.getParameterMap());
		bookService.addBook(bookDB);
		response.sendRedirect("book?method=listByPage");
	}
	
//upd
	public void updBook(HttpServletRequest request, HttpServletResponse response) throws Exception {
		BookDB bookDB = new BookDB();
		BeanUtils.populate(bookDB, request.getParameterMap());
		bookService.updBook(bookDB);
		response.sendRedirect("book?method=listByPage");
	}
	
	//del
	public void delBook(HttpServletRequest request, HttpServletResponse response) throws Exception {
		String bid = request.getParameter("bid");
		bookService.delBook(bid);
		response.sendRedirect("book?method=listByPage");
	}
	
	
	//借书，跳转成功后回到list界面
	public void borrowBook(HttpServletRequest request, HttpServletResponse response) throws Exception {
		//获取要借阅的图书ID
		String bid = request.getParameter("bid");
		//获取当前用户信息
		UserDB userDB = (UserDB) request.getSession().getAttribute("userDB");
		bookService.borrowBook(userDB,bid);
		response.sendRedirect("history?method=list");
	}
	
	
	//还书
	public void backBook(HttpServletRequest request, HttpServletResponse response) throws Exception {
		//获取要归还记录的ID
		String hid = request.getParameter("hid");
		bookService.backBook(hid);
		response.sendRedirect("history?method=backList");
	}
	
//推荐书籍
	public void rank(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		UserDB userDB = (UserDB) request.getSession().getAttribute("userDB");
		//根据当前登陆的用户获取角色
		Integer role = userDB.getRole();
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		PageTool<BookDB> pageTool = bookService.listByPage(currentPage, pageSize, null, 1);
		String path = "book?method=rank";
		//生成前端分页按钮
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(), path);
		request.setAttribute("pagation", pagation);
		request.setAttribute("start", pageTool.getStartIndex());
		request.setAttribute("bList", pageTool.getRows());
		//根据role判断跳转的页面
		if (role == 1) {
			//普通用户
			request.getRequestDispatcher("user/bdtimes.jsp").forward(request, response);
		} else {
			//管理员
			request.getRequestDispatcher("admin/admin_bdtimes.jsp").forward(request, response);
		}
		
	}
	
	
	
}
