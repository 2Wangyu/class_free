package com.web.servlet;


import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.utils.MyException;

//24.6.7
//开始学习servlet


//对于所有的servlet都要继承于此

public class BaseServlet extends HttpServlet{
	
	private static final long serialVersionUID=1L;
	
	
	//重写方法，在source,override imple。。。,选择倒数第二个
	@Override
	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		
		
		try {
			//super.service(arg0, arg1);
			//设置请求和响应的编码
			request.setCharacterEncoding("UTF-8");
			response.setCharacterEncoding("UTF-8");
			response.setContentType("text/html;charset=utf-8");
			
			//登录界面login.jsp 31行对应
			//获取方法名，字符串
			String m=request.getParameter("method");
			
		    //获取类
			Class<? extends BaseServlet> clazz =this.getClass();
			
			//获取要执行的方法
			
			Method method=clazz.getDeclaredMethod(m, HttpServletRequest.class,HttpServletResponse.class);
		    method.setAccessible(true);
		    method.invoke(this,request,response);
		
		}catch (InvocationTargetException e) {
			if (e.getTargetException() instanceof MyException) {
				//判断是否是自定义的异常，如果是，则...
				
				//自定义异常
				request.setAttribute("msg", e.getTargetException().getMessage());
			} else {
				request.setAttribute("msg", "网络异常");
				e.printStackTrace();
			}
			
			request.getRequestDispatcher("error.jsp").forward(request, response);
		}catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println("baseServlet异常处理");
			request.setAttribute("msg","网络异常波动，待处理");
			//跳转到报错的页面
			request.getRequestDispatcher("error.jsp").forward(request, response);
			
		}
		
		
		
		
	}

	
	 
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

}
