create table salgrade(
    grade int,
    losal int,
    hisal int
) comment '薪资等级表';
insert into salgrade values (1,0,3000);
insert into salgrade values (2,3001,5000);
insert into salgrade values (3,5001,8000);
insert into salgrade values (4,8001,10000);
insert into salgrade values (5,10001,15000);
insert into salgrade values (6,15001,20000);
insert into salgrade values (7,20001,25000);
insert into salgrade values (8,25001,30000);

-- 1.查询员工的姓名，年龄，职位，部门（隐式内连接）
-- 表 emp2，dept
 select e.name,e.age,e.job,d.name from emp2 e,dept d where e.dept_id=d.id;


-- 2.查询年龄小于30岁的员工的姓名，年龄，职位，部门信息（显示内连接）
-- 表 emp2，dept
 select e.name,e.age,e.job,d.name from emp2 e join dept d on e.dept_id=d.id where e.age<30;
 select e.name,e.age,e.job,d.name from emp2 e join dept d on e.dept_id=d.id and e.age<30;


-- 3.查询所有员工的部门ID，部门名称
-- 表 emp2，dept
select d.id,d.name from emp2 e,dept d where e.dept_id=d.id; -- 去重之前

select distinct d.id,d.name from emp2 e,dept d where e.dept_id=d.id; -- 加上distinct关键字即可


-- 4.查询所有年龄大于40岁的员工,及其所属的部门名称；如果员工没有分配部门，也需要展示出来
-- 表：emp2，dept
-- 外连接
select e.*,d.name from emp2 e left join dept d on e.dept_id=d.id;


-- 5.查询所有员工的工资等级
-- 表：emp2，salgrade
select e.*,s.grade,s.losal,s.hisal from emp2 e,salgrade s where e.salary>=s.losal and e.salary<=s.hisal;

select e.*,s.grade,s.losal,s.hisal from emp2 e,salgrade s where e.salary between s.losal and s.hisal;


-- 6.查询“研发部”所有员工的信息及工资等级
-- 表:emp2，salgrade，dept
select e.*, s.grade
from emp2 e,
     dept d,
     salgrade s
where e.dept_id = d.id
  and (e.salary between s.losal and s.hisal)
  and d.name = '研发部';


-- 7.查询'研发部'员工的平均工资
-- 表emp2，dept
select avg(e.salary) avg
from emp2 e ,
     dept d
where e.dept_id=d.id
    and d.name='研发部';


-- 8.查询工资比‘灭绝’高的员工信息
select * from emp2 e
    where salary> (select e.salary from emp2 e where e.name='灭绝');


-- 9.查询比平均薪资高的员工信息
select * from emp2 e
    where salary> (select avg(e.salary) from emp2 e);


-- 10.查询低于本部门平均工资的员工信息
select * ,((select avg(e1.salary) from emp2 e1 where e1.dept_id=e2.dept_id)) avg
from emp2 e2
where salary<(select avg(e1.salary) from emp2 e1 where e1.dept_id=e2.dept_id);
-- 我们详细说一下，第二个字段写这么多只是为了显示我们查询到的平均工资来验证，我们看最后的条件，e1.dept_id=e2.dept_id
-- 就是要求子查询和左边的查询是同一个部门的工资，满足要求之后就返回当前此部门的平均工资，外部查询也就可以直接比较


-- 11.查询所有部门信息，并统计部门的员工人数
select d.id,d.name,  (select count(*) from emp2 e where e.dept_id=d.id) '人数' from dept d;


-- 12.查询所有学生的选课情况，展示出学生名称，学号，课程名称
-- 表：student,course,stdent_course
select s.name,s.no,c.name from student s , student_course sc ,course c where s.id=sc.studentid and sc.courseid=c.id;