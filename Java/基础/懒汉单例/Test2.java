package com.guiguli.singletonPattern;

public class Test2 {
    public static void main(String[] args) {
        Singlelnstance s1 =Singlelnstance.getInstance();
        Singlelnstance s2 =Singlelnstance.getInstance();
        System.out.println(s1==s2);
    }
}
