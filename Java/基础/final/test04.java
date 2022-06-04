package com.guiguli.Final;
//final修饰引用数据类型可以改变引用类型变量的内容 但是不能改变地址
public class test04 {
    public static void main(String[] args) {
        final Test S=new Test("离谱");
        //S=null;   无法改变地址值
        System.out.println(S.getName());
        //可以改变内容
        S.setName("物理");
        System.out.println(S.getName());
    }
}
class Test{
    public String name;

    public Test(String name) {
        this.name = name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}