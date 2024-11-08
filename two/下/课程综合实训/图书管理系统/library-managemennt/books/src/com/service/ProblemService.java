package com.service;

import com.dao.ProblemDao;
import com.entity.ProblemDB;
import com.utils.PageTool;

public class ProblemService {

	private ProblemDao problemDao = new ProblemDao();
	
	//分页查询
	public PageTool<ProblemDB> list(String currentPage, String pageSize, String word, Integer order,Integer uid){
		return problemDao.list(currentPage, pageSize, word, order,uid);
	}
	
	
	//add
	public Integer addProblem(ProblemDB ProblemDB) {
		return problemDao.addProblem(ProblemDB);
	}
	
	//upd
	public Integer updProblem(ProblemDB ProblemDB) {
		return problemDao.updProblem(ProblemDB);
	}
	
	
	//del
	public Integer delProblem(String pid) {
		return problemDao.delBook(pid);
	}
}
