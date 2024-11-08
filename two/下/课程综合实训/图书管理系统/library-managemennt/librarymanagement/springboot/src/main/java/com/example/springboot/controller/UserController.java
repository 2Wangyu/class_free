package com.example.springboot.controller;


import com.example.springboot.common.Result;
import com.example.springboot.entity.User;
import com.example.springboot.service.IUserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

//解决跨域错误
@CrossOrigin

// 风格标识为restcontroller
@RestController

//区分不同的接口加上前缀
@RequestMapping("/user")

public class UserController {
    @Autowired
    IUserService userService;




    @GetMapping("/list")
        public Result listUsers() {
        List<User> users = userService.listUsers();
        return Result.success(users);

    }
//    public Result list() {
//        List<User> users = userService.list();
//        return Result.success(users);
//
//    }




}
