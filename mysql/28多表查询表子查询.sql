-- A. 查询与 "鹿杖客" , "宋远桥" 的职位和薪资相同的员工信息
-- 分解为两步执行:
# ①. 查询 "鹿杖客" , "宋远桥" 的职位和薪资
select job,salary from emp2 where name='鹿杖客' or name='宋远桥';

# ②. 查询与 "鹿杖客" , "宋远桥" 的职位和薪资相同的员工信息
select * from emp2 where (job,salary) in (select job,salary from emp2 where name='鹿杖客' or name='宋远桥');

-- 2.查询入职日期是‘2006-01-01’之后的员工信息，及其部门
-- a.入职日期是‘2006-01-01’之后的员工信息
select * from emp2 where entrydate>'2006-01-01';

-- b.查询这部门员工，对应的部门信息;
select e.*,d.* from(select * from emp2 where entrydate>'2006-01-01') e left join dept d on e.dept_id=d.id;