package com.guiguli.string_ArrayList;

import java.util.Scanner;

public class StringCase02 {
    public static void main(String[] args) {
        //1.正确登录名和密码
        String okName = "itheima";
        String okPassword = "123456";
        //2.输入
        Scanner sc = new Scanner(System.in);
        System.out.println("登录名称");
        String name = sc.next();
        System.out.println("登录密码");
        String password = sc.next();
        //3.判断
        if(okName.equals(name)&&okPassword.equals(password)){
            System.out.println("输入正确");
        }
        else{
            System.out.println("输入错误");
        }
        //4.忽略大小写比较内容Api 一般用于比较验证码这样的业务逻辑
        String sysCode="23AdFh";
        String code1="23aDfH";
        //无视大小写比较
        System.out.println(sysCode.equalsIgnoreCase(code1));
    }
}
