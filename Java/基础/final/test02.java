package com.guiguli.Final;

public class test02 {
    public static void main(String[] args) {
        B c=new B();
        c.func();
        c.func();
    }

}
//2的错误演示
class A{
    public /*final*/ void func() {
        System.out.println(123);
    }
}
class B extends A{
    public void func() {
        System.out.println(321);
    }
}