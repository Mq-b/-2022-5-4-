package com.guiguli.singletonPattern;

public class Singlelnstance {
    /*
    定义一个静态的成员变量负责存储一个对象
    加载一次 只有一份。
    注意 最好私有化 这样可以避免给别人挖坑
     */
    private static Singlelnstance instance;

    /*
    提供一个方法 对外返回单例对象
     */
    public static Singlelnstance getInstance() {
        if (instance == null) {
            //第一次拿对象 此时创建对象
            instance = new Singlelnstance();
        }
        return instance;
    }

    /*
    私有化构造器
     */
    private Singlelnstance() {

    }
}
