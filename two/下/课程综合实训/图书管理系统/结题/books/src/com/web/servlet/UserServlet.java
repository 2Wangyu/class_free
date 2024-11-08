package com.web.servlet;


import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;

import com.google.gson.Gson;
import com.entity.UserDB;
import com.service.UserService;
import com.utils.MD5;
import com.utils.PageTool;
import com.utils.PaginationUtils;
import com.utils.ResBean;


//用户
@WebServlet("/user")
public class UserServlet extends BaseServlet{
	
    private static final long serialVersionUID = 1L;
	
	private UserService userService = new UserService();

	
	//用户列表分页
	public void list(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		PageTool<UserDB> pageTool = userService.list(currentPage, pageSize, null);
		
		//生成前端分页按钮
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(), "user?method=list");
		
		request.setAttribute("pagation", pagation);
		request.setAttribute("uList", pageTool.getRows());
	
		//跳转页面
		request.getRequestDispatcher("admin/admin_user.jsp").forward(request, response);
	}
	
	
	//添加用户
	public void addUser(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException, IllegalAccessException, InvocationTargetException {

		//用一些笨办法从前端读取数据
		//		String account =request.getParameter("account");
//		String password =request.getParameter("password");
//		String name = request.getParameter("name");
//		String phone =request.getParameter("phone");
//		String maxNum =request.getParameter("maxNum");
//		String lendNum=request.getParameter("lendNum");
//		String role=request.getParameter("role");
//		
		UserDB userDB = new UserDB();
		//把前端接受到的数据全部放入userDB对象当中
		BeanUtils.populate(userDB, request.getParameterMap());
		//设置user的借阅量
		userDB.setTimes(0);
		//对密码进行加密
		userDB.setPassword(MD5.valueOf(userDB.getPassword()));
		
		//System.out.println(userDB);
		//传到后端去
		userService.addUser(userDB);
		//用户界面的刷新
		response.sendRedirect("user?method=list");
	}
	
	//校验账户是否存在过，存在则不能再创建用户
	public void checkUser(HttpServletRequest request, HttpServletResponse response) throws IOException {
		//获取账户名
		String account = request.getParameter("account");
		UserDB userDB = new UserDB();
		userDB.setAccount(account);
		List<UserDB> list = userService.getList(userDB);
		
		//对于账户添加操作成功与否进行相应的实体类
		ResBean resBean = new ResBean();
		
		if (list != null && list.size() > 0) {
			//用于检验的时候确实可以在后台打印这个数据
			//但是我们的目的是在前端能够展示出账户存在的信息，所以得换了
			//request.setAttribute("msg", );
			
			resBean.setCode(400);
			resBean.setMsg("账号被占用");
		} else {
			resBean.setCode(200);
			resBean.setMsg("账号可以使用");
		}
		//将 resBean 转换成 json字符串，方便前端显示出来
		Gson gson = new Gson();
		String json = gson.toJson(resBean);
		response.getWriter().print(json);
	}
	
//修改用户信息
	public void updUser(HttpServletRequest request, HttpServletResponse response) throws Exception {
		UserDB userDB = new UserDB();
		BeanUtils.populate(userDB, request.getParameterMap());
		userService.updUser(userDB);
		response.sendRedirect("user?method=list");
	}
	//删除用户信息
	public void delUser(HttpServletRequest request, HttpServletResponse response) throws Exception {
		String uid = request.getParameter("uid");
		userService.delUser(Integer.parseInt(uid));
		response.sendRedirect("user?method=list");
	}
	
	//借阅量最多的用户的排名
	public void rank(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		UserDB userDB = (UserDB) request.getSession().getAttribute("userDB");
		//根据当前登陆的用户获取角色
		Integer role = userDB.getRole();
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		PageTool<UserDB> pageTool = userService.list(currentPage, pageSize, 1);
		//生成前端分页按钮
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(), "user?method=rank");
		request.setAttribute("pagation", pagation);
		request.setAttribute("start", pageTool.getStartIndex());
		request.setAttribute("uList", pageTool.getRows());
		//根据role判断跳转的页面
		if (role == 1) {
			//普通用户
			request.getRequestDispatcher("user/brtimes.jsp").forward(request, response);
		} else {
			//管理员
			request.getRequestDispatcher("admin/admin_brtimes.jsp").forward(request, response);
		}
	}
	

}
