// 在entity下的所有都是用来定义实体类的

package com.example.springboot.entity;


import lombok.Data;

@Data
public class User {
    private String name;
    private Integer id;
    private String username;
    private Integer age;
    private String sex;
    private String address;
    private String phone;

}
