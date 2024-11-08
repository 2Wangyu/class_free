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
import com.entity.TypeDB;
import com.service.TypeService;

import com.utils.PageTool;
import com.utils.PaginationUtils;
import com.utils.ResBean;

@WebServlet("/type")
public class TypeServlet extends BaseServlet{
private static final long serialVersionUID = 1L;
	
	private TypeService typeService = new TypeService();
	
//列表分页
	public void listByPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		PageTool<TypeDB> pageTool = typeService.listByPage(currentPage, pageSize);
		//生成前端分页按钮
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(), "type?method=listByPage");
		request.setAttribute("pagation", pagation);
		request.setAttribute("tList", pageTool.getRows());
		request.getRequestDispatcher("admin/admin_booktype.jsp").forward(request, response);
	}
	
//同样的校验
	public void checkType(HttpServletRequest request, HttpServletResponse response) throws IOException {
		/* String tid = request.getParameter("tid"); */
		String typeName = request.getParameter("typeName");
		List<TypeDB> list = typeService.list(null, typeName);
		ResBean resBean = new ResBean();
		if (list != null && list.size() > 0) {
			resBean.setCode(400);
			resBean.setMsg("类别名称已存在");
		} else {
			resBean.setCode(200);
			resBean.setMsg("类别名称可以使用");
		}
		//将 resBean 转换成 json字符串
		Gson gson = new Gson();
		String json = gson.toJson(resBean);
		response.getWriter().print(json);
	}
	
//添加
	public void addType(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String typeName = request.getParameter("typeName");
		typeService.addType(typeName);
		request.getRequestDispatcher("type?method=listByPage").forward(request, response);
	}
	
//修改
	public void updType(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String tid = request.getParameter("tid");
		String typeName = request.getParameter("typeName");
		TypeDB typeDB = new TypeDB();
		typeDB.setTid(Integer.parseInt(tid));
		typeDB.setTypeName(typeName);
		typeService.updType(typeDB);
		request.getRequestDispatcher("type?method=listByPage").forward(request, response);
	}
	
//删除
	public void delType(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String tid = request.getParameter("tid");
		typeService.delType(Integer.parseInt(tid));
		request.getRequestDispatcher("type?method=listByPage").forward(request, response);
	}
}
