package com.guiguli.string_ArrayList;
//创建String对象的几种方式
public class StringStructure {
    public static void main(String[] args) {
        //"我爱你中国"
        String name="我爱你中国";
        System.out.println(name);
        //""
        String s1=new String();
        System.out.println(s1);
        //"我是中国人"
        String s2=new String("我是中国人");
        System.out.println(s2);
        //"abcd"
        char[] chars={'a','b','c','d'};
        String s3=new String(chars);
        System.out.println(s3);
        //"abcABC"
        byte[] bytes={97,98,99,65,66,67};
        String s4=new String(bytes);
        System.out.println(s4);
        //false new构造器创建字符串对象在堆区是分开存储的
        String s5=new String(chars);
        System.out.println(s3==s5);
        //true 双引号创建的字符串对象在字符串常量池只存储一个
        String s6="abc";
        String s7="abc";
        System.out.println(s6==s7);
    }
}
