package com.guiguli.string_ArrayList;

import java.util.Random;

//使用String 完成随机生成的五位验证码
public class StringCase03 {
    public static void main(String[] args) {
        String datas="abcdefghijklmnopqrstopwxyzABCDEFGHIJKLMNOPQRSTOPWXYZ0123456789";
        //循环五次 每次生成一个随机的索引 提取对应的字符连接起来即可
        Random r=new Random();
        String code="";
        for(int i=0;i<5;i++){
            //随机
            int index=r.nextInt(datas.length());
            char c=datas.charAt(index);
            code+=c;
        }
        System.out.println(code);
    }
}
