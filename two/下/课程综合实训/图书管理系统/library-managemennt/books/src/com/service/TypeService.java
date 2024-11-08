package com.service;


import java.util.List;

import com.dao.TypeDao;
import com.entity.TypeDB;
import com.utils.PageTool;


//图书类别
public class TypeService {

	

	private TypeDao typeDao = new TypeDao();
	//分页查询
	public PageTool<TypeDB> listByPage(String currentPage, String pageSize){
		return typeDao.listByPage(currentPage, pageSize);
	}
	//多条件查询
	public List<TypeDB> list(String tid,String typeName) {
		return typeDao.list(tid, typeName);
	}
	//添加
	public Integer addType(String typeName) {
		return typeDao.addType(typeName);
	}
	//修改
	public Integer updType(TypeDB typeDB) {
		return typeDao.updType(typeDB);
	}
	//删除
	public int delType(Integer tid) {
		return typeDao.delType(tid);
	}
}
