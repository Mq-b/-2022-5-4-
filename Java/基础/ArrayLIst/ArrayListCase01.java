package com.guiguli.string_ArrayList;

import java.util.ArrayList;

public class ArrayListCase01 {
    public static void main(String[] args) {
        //遍历并删除元素的正确方案
        ArrayList<Integer>scores=new ArrayList<>();
        scores.add(98);
        scores.add(77);
        scores.add(66);
        scores.add(89);
        scores.add(79);
        scores.add(50);
        scores.add(100);
        System.out.println(scores);

        //把低于80分的成绩从集合中去掉
        //解决方案之一
        /*for(int i=0;i<scores.size();i++){
            if(scores.get(i)<80){
                scores.remove(i);
                i--;// 删除成功后 必须退一步 这样可以保证下次回到这个位置 如此就不会跳过数据
            }
        }*/
        //解决方案 直接倒序删除
        for(int i=scores.size()-1;i>=0;i--){
            if(scores.get(i)<80){
                scores.remove(i);
            }
        }
        System.out.println(scores);
    }
}
