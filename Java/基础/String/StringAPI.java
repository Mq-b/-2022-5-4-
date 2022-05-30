package com.guiguli.string_ArrayList;

public class StringAPI {
    public static void main(String[] args) {
        //1.获取String类的长度
        //public int length()
        String name = "我爱你中国love";
        System.out.println(name.length());//9 和c/c++不一样 长度不在乎汉字还是字符

        //2.使用for循环遍历 调用String类的charAt方法一个一个打印元素 接收的参数类似于索引一样
        //public char charAt(int index)
        for (int i = 0; i < name.length(); i++) {
            System.out.println(name.charAt(i));
        }
        //3.把字符串转换成字符数组
        //public char[] toCharArray()
        char[] chars = name.toCharArray();
        for (int i = 0; i < chars.length; i++) {
            System.out.println(chars[i]);
        }

        //4.字符串截取
        //public String substring(int beginIndex,int endIndex)
        String name2 = "java是最厉害的编程语言!";
        System.out.println(name2.substring(0, 9));//两个参数分别是开始索引于结束索引 前后都包含

        //5.从当前索引截取到末尾
        //public String substring(int beginIndex)
        System.out.println(name2.substring(2));//相当于上一个的重载版本

        //6.字符串替换
        //public String replace(CharSequence target,CharSequence replacement)
        String name3 = "金三胖是最厉害的80后";
        String rs3 = name3.replace("金三胖", "***");
        System.out.println(name3);
        System.out.println(rs3);
        //由此可得replace方法之后返回被修改过的字符串 无法改变原来的String对象

        //7.判断字符串是内是否包含某字串
        //public boolean contains(CharSequence s)
        System.out.println(name3.contains("金三胖"));//true
        System.out.println(rs3.contains("金三胖"));//false

        //8.判断字符串是不是以什么开始的
        //public boolean contains(CharSequence s)
        System.out.println(name3.startsWith("金三胖"));//true
        System.out.println(name3.startsWith("无敌"));//false

        //9.按照某个内容把字符串分割成字符串数组返回
        //public String[] split(String s)
        String name4 = "王宝强,贾乃亮,陈羽凡";
        String[] names = name4.split(",");
        for (String s : names) {
            System.out.println(s);
        }
    }
}
