package com.web.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.entity.UserDB;
import com.service.UserService;
import com.utils.MD5;

@WebServlet("/login")
public class LoginServlet extends BaseServlet{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private UserService userService = new UserService();
	
	//throws ServletException, IOException
	public void login(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException  {
		
		//获取账户和密码
		String account = request.getParameter("account");
		String password = request.getParameter("password");
		
		//测试是否打印到控制台上，即是否连上了
//		System.out.println(account);
//		System.out.println(password);
		
		//查到的用户需要放到session当中
		HttpSession session = request.getSession();
		
		UserDB userDB = userService.login(account, MD5.valueOf(password));
		if (userDB == null) {
			//账号密码错误
			request.setAttribute("msg", "账号密码错误");
			request.getRequestDispatcher("login.jsp").forward(request, response);
		} else {
			//登陆成功
			session.setAttribute("userDB", userDB);
			
			//登录成功后跳转主界面
			request.getRequestDispatcher("index.jsp").forward(request, response);
		}
	}

}
