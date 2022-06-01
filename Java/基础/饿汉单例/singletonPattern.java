package com.guiguli.singletonPattern;

public class singletonPattern {
    /*
        饿汉单例是在获取对象前 对象已经提前准备好了一个
        这个对象只能是一个 所以定义静态成员变量记住
     */
    public static singletonPattern instance = new singletonPattern();

    private singletonPattern(){

    }
}