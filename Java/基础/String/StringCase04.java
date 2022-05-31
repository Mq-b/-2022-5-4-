package com.guiguli.string_ArrayList;

import java.util.Scanner;

public class StringCase04 {
    public static void main(String[] args) {
        //1.定义正确的登录名称和密码
        String okLoginName="admin";
        String okPassword="itheima";

        //2.定义一个循环 循环三次 让用户登录
        Scanner sc=new Scanner(System.in);
        for(int i=1;i<=3;i++){
            System.out.println("请输入登录名称：");
            String loginName=sc.next();
            System.out.println("请输入登录密码：");
            String password=sc.next();

            //3.判断
            if(okLoginName.equals(loginName)){
                if(okPassword.equals(password)){
                    System.out.println("登录成功！欢迎进入系统随意浏览---");
                }else{
                    System.out.println("您的密码不正确！您还剩余"+(3-i)+"次机会");
                }
            }else{
                System.out.println("您的登录名称不正确！您还剩余"+(3-i)+"次机会");
            }
        }
    }
}
