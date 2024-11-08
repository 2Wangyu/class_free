package com.dao;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.dbutils.BasicRowProcessor;
import org.apache.commons.dbutils.BeanProcessor;
import org.apache.commons.dbutils.GenerousBeanProcessor;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.RowProcessor;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;

import com.entity.TypeDB;
import com.utils.C3p0Tool;
import com.utils.PageTool;

//图书分裂
public class TypeDao {


	QueryRunner queryRunner = new QueryRunner(C3p0Tool.getDataSource());
	//开启驼峰自动转换
	BeanProcessor bean = new GenerousBeanProcessor();
	RowProcessor processor = new BasicRowProcessor(bean);
	
	//图书列表分页
	public PageTool<TypeDB> listByPage(String currentPage, String pageSize){
		try {
			StringBuffer listSql = new StringBuffer("select * ");
			StringBuffer countSql = new StringBuffer("select count(*) ");
			StringBuffer sql = new StringBuffer("from t_type");
			//获取总记录数
			Long total = queryRunner.query(countSql.append(sql).toString(), new ScalarHandler<Long>());
			//初始化分页工具
			PageTool<TypeDB> pageTools = new PageTool<TypeDB>(total.intValue(), currentPage, pageSize);
			sql.append(" limit ?,?");
			//当前页的数据		
			 List<TypeDB> list = queryRunner.query(listSql.append(sql).toString(), new BeanListHandler<TypeDB>(TypeDB.class, processor),pageTools.getStartIndex(),pageTools.getPageSize());
			 pageTools.setRows(list);
			 System.out.println(pageTools);
			 return pageTools;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return new PageTool<TypeDB>(0, currentPage, pageSize);
	}
	
//查询，多条件,根据图书类型的Id或者是类型进行查询
	public List<TypeDB> list(String tid, String typeName){
		StringBuffer sql = new StringBuffer("select * from t_type where 1 = 1 ");
		
		List<Object> params = new ArrayList<>();
		
		if (tid != null && tid != "") {
			sql.append("and tid = ? ");
			params.add(tid);
		}
		if (typeName != null && typeName != "") {
			sql.append("and type_name = ?");
			params.add(typeName);
		}
		try {
			return queryRunner.query(sql.toString(), new BeanListHandler<TypeDB>(TypeDB.class, processor), params.toArray());
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	//添加图书类别
	public Integer addType(String typeName) {
		String sql = "insert into t_type (type_name) values (?)";
		Object[] params = {typeName};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	//修改图书类别
	public Integer updType(TypeDB typeDB) {
		String sql = "update t_type set type_name = ? where tid = ?";
		Object[] params = {typeDB.getTypeName(), typeDB.getTid()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	//删除图书
	public int delType(Integer tid) {
		String sql = "delete from t_type where tid = ?";
		Object[] params = {tid};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return -1;
	}
	
}
