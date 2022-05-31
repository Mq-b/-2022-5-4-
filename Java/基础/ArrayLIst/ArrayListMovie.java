package com.guiguli.string_ArrayList;

import java.util.ArrayList;

/*
    案例 集合存储自定义元素并遍历
    需求:定义电影类(名称 分值 演员) 创建三个电影对象 代表三部影片
    《肖申克的救赎》 9.7 罗宾斯
    《霸王别姬》 9.6 张国荣 张丰毅
    《阿甘正传》 9.5 汤姆.汉克斯
 */
public class ArrayListMovie {
    public static void main(String[] args) {
        Movie m1=new Movie("《肖申克的救赎》",9.7,"罗宾斯");
        Movie m2=new Movie("《霸王别姬》",9.7,"张国荣、张丰毅");
        Movie m3=new Movie("《阿甘正传》",9.5,"汤姆.汉克斯");

        ArrayList<Movie>movies=new ArrayList<>();
        movies.add(m1);
        movies.add(m2);
        movies.add(m3);
        //遍历
        for(int i=0;i<movies.size();i++){
            Movie m =movies.get(i);
            System.out.println("电影名称："+m.getName());
            System.out.println("电影得分："+m.getScore());
            System.out.println("电影主演："+m.getActotor());
            System.out.println("---------------");
        }
    }
}