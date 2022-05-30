package com.guiguli.string_ArrayList;

public class StringCase01 {
    public static void main(String[] args) {
        //一句代码创建两个对象 先new一个String对象构造 再赋值
        String s1=new String("abc");
        String s2="abc";
        //false 因为new String()创建的字符串不是常量 不在编译期就确定 所以new String()创建的字符串不放入常量池中 他们有自己的地址空间
        System.out.println(s1==s2);

        String s3="abc";
        String s4="a"+"b"+"c";
        //true  java存在编译优化机制 程序在编译时 "a"+"b"+"c"会直接转成"abc"
        System.out.println(s3==s4);
    }
}
