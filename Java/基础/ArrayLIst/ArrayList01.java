package com.guiguli.string_ArrayList;

import java.util.ArrayList;

//创建ArrayLIst对象 代表集合容器 往里面添加元素
public class ArrayList01 {
    public static void main(String[] args) {
        //1.创建对象
        ArrayList list=new ArrayList();
        //2.插入数据
        list.add("java");
        list.add("MySQL");
        list.add(23);
        list.add(23.5);
        list.add(false);
        list.add('中');
        System.out.println(list);

        //3.给指定索引位置插入元素
        list.add(1,"赵敏");
        System.out.println(list);
    }
}
