package com.utils;


//C3P0工具类

import java.sql.Connection;
import java.sql.SQLException;

import javax.sql.DataSource;

import com.mchange.v2.c3p0.ComboPooledDataSource;

public class C3p0Tool {
private static DataSource dataSource = new ComboPooledDataSource();
	
//获取数据源在哪里
	public static DataSource getDataSource() {
		return dataSource;
	}
//获取连接的信号
	public static Connection getConnection() {
		try {
			return dataSource.getConnection();
		} catch (SQLException e) {
			e.printStackTrace();
			throw new RuntimeException();
		}
	}
	

}
