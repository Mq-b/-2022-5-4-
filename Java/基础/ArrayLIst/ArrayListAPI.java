package com.guiguli.string_ArrayList;

import java.util.ArrayList;

public class ArrayListAPI {
    public static void main(String[] args) {
        ArrayList<String>list=new ArrayList<>();
        list.add("java");
        list.add("java");
        list.add("MySQL");
        list.add("MyBatis");
        list.add("HTML");

        //1.public E get(int index) 获取某个索引位置处的元素值
        System.out.println(list.get(3));

        //2.public int size() 获取集合的大小(元素个数)
        System.out.println(list.size());

        //3.完成集合遍历
        for(var i:list) System.out.println(i);
        //或者像下面这样
        for(int i=0;i<list.size();i++){
            System.out.println(list.get(i));
        }

        //4.public E remove(int index) 删除某个索引位置处的元素值 并返回被删除的元素值
        System.out.println("\n");
        System.out.println(list.remove(1));
        System.out.println(list);

        ///5.public boolean remove(object o)) 重载版本 直接删除元素值 删除成功返回true 删除失败返回false
        System.out.println(list.remove("MySQL"));
        System.out.println(list);

        //6.public E set(int index,E element) 修改某个索引处的元素值
        list.set(0,"java!!!!");
        System.out.println(list);
    }
}
