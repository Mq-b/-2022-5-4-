package com.guiguli.string_ArrayList;

import java.util.ArrayList;
import java.util.Scanner;

public class ArrayListStudent {
    public static void main(String[] args) {
        //创建集合存储学生对象 创建学生对象封装学生信息
        ArrayList<Student>students=new ArrayList<>();
        students.add(new Student("20180302","叶孤城",23,"护理一班"));
        students.add(new Student("20180303","东方不败",23,"推拿2班"));
        students.add(new Student("20180304","西门吹雪",23,"中药学四班"));
        students.add(new Student("20180305","梅超风",26,"神经科2班"));
        //遍历
        for (int i = 0; i < students.size(); i++) {
                Student s=students.get(i);
            System.out.println(s.getStudyNumber()+"\t"+s.getName()+"\t"+s.getAge()+"\t"+s.getClassName());
        }
        //定义方法完成按照学号的搜索功能
        Scanner sc=new Scanner(System.in);
        while(true){
            System.out.println("请您输入学号查询学生对象");
            String studyName=sc.next();
            //调用方法
            Student s=getStudentId(students,studyName);
            if(s==null){
                System.out.println("查无此人");
            }else{
                System.out.println("您查询的学生信息如下");
                System.out.println(s.getStudyNumber()+"\t"+s.getName()+"\t"+s.getAge()+"\t"+s.getClassName());
            }
        }
    }
    public static Student getStudentId(ArrayList<Student>students,String studyNumber){
        for (int i = 0; i < students.size(); i++) {
            if(students.get(i).getStudyNumber().equals(studyNumber)){
                return students.get(i);
            }
        }
        return null;
    }
}
