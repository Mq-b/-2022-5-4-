package com.guiguli.string_ArrayList;

import java.util.ArrayList;

public class ArrayLIstGeneric {
    public static void main(String[] args) {
        //泛型类
        ArrayList<String> list=new ArrayList<>();//泛型后面的类型声明可以不写
        list.add("java");
        list.add("MySQL");

        ArrayList<Integer>list2=new ArrayList<>();
        list2.add(23);
        list2.add(100);
        //泛型的类型只能写引用类型 不能写基本数据类型
    }
}
