-- 创建视图 使用聚合函数
create view stu_v_count as select count(*) from student;

insert into stu_v_count values(10)


-- 案例
-- 1.为了保证数据库表的安全性 开发人员在操作tb_user表时 只能看到用户的基本字段 屏蔽手机号和邮箱号两个字段
create view tb_user_view as select id,name ,profession ,age,gender,status,createtime from tb_user;

select * from tb_user_view;

-- 2. 查看每个学生所选修的课程(三张表联查) 这个功能在很多的业务中都有使用 为了简化操作 定义一个数量
select s.name,s.no,c.name from student s,student_course sc,course c where s.id=sc.studentid and sc.courseid=c.id;

create view tb_stu_course_view as select s.name student_name,s.no student_no,c.name course_name
from student s,student_course sc,course c where s.id=sc.studentid and sc.courseid=c.id;