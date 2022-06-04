package com.guiguli.Final;
//3的演示
public class test03 {
    public static void main(String[] args) {
        final double rate=3.14;
        /*rate=100;*/ //错误 rate只能被赋值一次

    }

    public static final String name="归故里";//常量无法被修改 有且只能被赋值一次 也必须赋值一次初始化

    public final String Name="牛逼";  //给普通成员变量加final没啥意义

    public static void buy(final double z){
        //z=0.1;    //第二次赋值
    }
}
