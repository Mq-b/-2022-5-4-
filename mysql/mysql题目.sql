use mysql_test;
-- 1、查询"01"课程比"02"课程成绩高的学生的信息及课程分数
select s.*,scl.s_score score01,sc2.s_score score_02
from student s  -- 查询表student别名s
join(select * from score where c_id=1)scl -- 查询score表中课程id为1的数据 取别名scl
on s.s_id=scl.s_id -- on连接条件把数据过滤为只有01课程的信息
join(select * from score where c_id=2)sc2 -- 查询score表中课程id为2的数据 取别名sc2
on s.s_id=sc2.s_id -- on连接条件把数据过滤为只有02课程的信息
where scl.s_score>sc2.s_score;
-- 用score查询表内c_id为1的数据 就能得到c_id为1的s_id 用来过滤得到student表内的课程ID为1的数据
-- 第二步一样
-- 最后查询完就使用where进行判断
-- 我们用到两个join也就是显示内连接相当于三个表 实际上我们也是这样操作的

-- 2.查询"01"课程比"02"课程成绩低的学生的信息及课程分数
select s.*,scl.s_score score01,sc2.s_score score_02
from student s
join(select * from score where c_id=1)scl
on s.s_id=scl.s_id  -- 连接条件
join(select * from score where c_id=2)sc2
on s.s_id=sc2.s_id  -- 连接条件
where scl.s_score<sc2.s_score;
-- 单纯的反转了一下符号

-- 3.查询平均成绩大于等于60分的同学的学生编号和学生姓名和平均成绩
select s.s_id,s.s_name,round(avg_score,2) as avg_score
from student s
join(select s_id,avg(s_score) as avg_score
     from score
     group by s_id  -- 分组字段列表
     having avg_score>=60   -- 分组条件列表
     )t1
on s.s_id=t1.s_id;  -- 连接条件

-- 4.查询平均成绩小于60分的同学的学生编号和学生姓名和平均成绩(包括有成绩的和无成绩的)
select s.s_id,s.s_name,ifnull(round(avg_score,2),0) as avg_score
from student s
left join(select s_id,avg(s_score) as avg_score
     from score
     group by s_id  -- 分组字段列表
     )t1
on s.s_id=t1.s_id  -- on写的是左外连接的条件
where avg_score is null or avg_score<60;

-- 5.查询所有同学的学生编号、学生姓名、选课总数、所有课程的总成绩
select s.s_id,s.s_name,ifnull(cnt_course,0) as cnt_coures,ifnull(sum_score,0)
from student s
left join(
    select s_id,count(*) as cnt_course,sum(s_score) as sum_score -- 查询选课总数和课程总成绩分别取别名
    from score
    group by s_id   -- 分组字段列表
)t1
on s.s_id=t1.s_id;  -- on条件的意思就是确保依次查询每一个学生的这些信息

-- 6.查询"李"姓老师的数量
select count(*) cnt_nameli
from teacher
where t_name like '李%';

-- 当前读 表示读取最新的数据 默认我们开启事务的时候查询到的数据就被定格 也就是快照读了 不管数据发生什么改变 我们读取到的都是一样的
select * from stu lock in share mode;