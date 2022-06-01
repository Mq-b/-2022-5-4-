package com.guiguli.singletonPattern;

public class Test {
    public static void main(String[] args) {
        singletonPattern s1= singletonPattern.instance;
        singletonPattern s2= singletonPattern.instance;
        System.out.println(s1==s2);
    }
}
