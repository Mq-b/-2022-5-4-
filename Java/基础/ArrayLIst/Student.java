package com.guiguli.string_ArrayList;

public class Student {
    private String studyNumber;
    private String name;
    private int age;
    private String className;

    public void setStudyNumber(String studyNumber) {
        this.studyNumber = studyNumber;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setClassName(String className) {
        this.className = className;
    }

    public String getStudyNumber() {
        return studyNumber;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public String getClassName() {
        return className;
    }

    public Student(String studyNumber, String name, int age, String className) {
        this.studyNumber = studyNumber;
        this.name = name;
        this.age = age;
        this.className = className;
    }

    public Student(){

    }
}
