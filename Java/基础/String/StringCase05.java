package com.guiguli.string_ArrayList;

import java.util.Scanner;

//手机号码蔽
public class StringCase05 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        System.out.println("请输入您的手机号码");
        String tel=sc.next();

        String before=tel.substring(0,3);//0,1,2;
        String after=tel.substring(7);//从索引7开始截取全部字符串
        String s=before+"****"+after;
        System.out.println(s);
    }
}
