package com.web.servlet;

import java.io.IOException;
import java.util.Date;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;

import com.entity.ProblemDB;
import com.entity.UserDB;
import com.service.ProblemService;
import com.utils.PageTool;
import com.utils.PaginationUtils;


@WebServlet("/problem")
public class ProblemServlet extends BaseServlet {
	
	private static final long serialVersionUID = 1L;
	
	private ProblemService problemService = new ProblemService();


	//问题的列表的分页
	public void listByPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		UserDB userDB = (UserDB) request.getSession().getAttribute("userDB");
		//根据当前登陆的用户获取角色
		Integer role = userDB.getRole();
		String word = request.getParameter("word");
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		PageTool<ProblemDB> pageTool = null;
		if (role == 1) {
			pageTool = problemService.list(currentPage, pageSize, word, 1, userDB.getUid());
		} else {
			//管理员
			pageTool = problemService.list(currentPage, pageSize, word, 1, null);
		}
		String path = "problem?method=listByPage";
		if (word != null && word != "") {
			path += "&word=" + word;
		}
		//生成前端分页按钮
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(), path);
		request.setAttribute("pagation", pagation);
		request.setAttribute("start", pageTool.getStartIndex());
		request.setAttribute("pList", pageTool.getRows());
		//根据role判断跳转的页面
		if (role == 1) {
			//普通用户
			request.getRequestDispatcher("user/myproblem.jsp").forward(request, response);
		} else {
			//管理员
			request.getRequestDispatcher("admin/admin_feedback.jsp").forward(request, response);
		}
		
	}
	
	//add
	public void addProblem(HttpServletRequest request, HttpServletResponse response) throws Exception {
		ProblemDB problemDB = new ProblemDB();
		BeanUtils.populate(problemDB, request.getParameterMap());
		UserDB userDB = (UserDB) request.getSession().getAttribute("userDB");
		problemDB.setUid(userDB.getUid());
		problemDB.setStatus(0);//未解决
		problemDB.setTime(new Date());
		problemService.addProblem(problemDB);
		response.sendRedirect("problem?method=listByPage");
	}
	
	//upd
	public void updProblem(HttpServletRequest request, HttpServletResponse response) throws Exception {
		ProblemDB problemDB = new ProblemDB();
		BeanUtils.populate(problemDB, request.getParameterMap());
		problemService.updProblem(problemDB);
		response.sendRedirect("problem?method=listByPage");
	}
	
	//del
	public void delProblem(HttpServletRequest request, HttpServletResponse response) throws Exception {
		String pid = request.getParameter("pid");
		problemService.delProblem(pid);
		response.sendRedirect("problem?method=listByPage");
	}
	
}
