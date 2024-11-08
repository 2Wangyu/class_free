package com.example.springboot.service.IMPL;

import com.example.springboot.mapper.UserMapper;
import com.example.springboot.service.IUserService;
import java.util.List;
import com.example.springboot.entity.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class UserService implements IUserService {

    @Autowired
    public UserMapper userMapper;

    @Override
    public List<User> listUsers(){
        return userMapper.listUsers();
    }
//    @Override
//    public List<User> list(){
//        return userMapper.list();
//    }

}
