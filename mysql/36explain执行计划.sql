-- EXPLAIN 或者 DESC命令获取 MySQL 如何执行 SELECT 语句的信息，包括在 SELECT 语句执行
-- 过程中表如何连接和连接的顺序。

-- 语法
-- -- 直接在select语句之前加上关键字 explain / desc
-- EXPLAIN SELECT 字段列表 FROM 表名 WHERE 条件 ;

-- 多表联查 查询每一个学生的选课情况
select s.* ,c.* from student s,course c,student_course sc where s.id=sc.studentid and c.id=sc.courseid;

-- 想要查看执行计划只需要在语句前面加上explain
explain select s.* ,c.* from student s,course c,student_course sc where s.id=sc.studentid and c.id=sc.courseid;

-- id相同 执行顺序从上到下；id不同 id值越大 越先执行 如果id值相同 从上到下 ！！！！！！！！！！！！！！！！！！！

-- 查询选修了mysql课程的学生

-- 1.
select id from course c where c.name='MySQL'; -- 得到3

-- 2.
select studentid from student_course sc where sc.courseid=3; -- 得到1 2

-- 3.
select * from student s where s.id in(1,2);

-- end  套起来就行
select * from student s where s.id in(select studentid from student_course sc where sc.courseid=(select id from course c where c.name='MySQL'));

-- 要想查询执行计划只需要在前面加上explain

explain select * from student s where s.id in(select studentid from student_course sc where sc.courseid=(select id from course c where c.name='MySQL'));