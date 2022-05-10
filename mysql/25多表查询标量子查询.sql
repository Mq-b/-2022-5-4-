-- 1.查询'研发部'的所有员工信息
-- a.查询‘研发部’部门ID
select id from dept where name='销售部';

-- b.根据研发部ID，查询员工信息
select * from emp2 where dept_id = (select id from dept where name = '研发部');

-- 2.查询在'易新月'入值之后的员工信息
-- a.查询易新月的入职日期
select entrydate from emp2 where name='易新月';

-- b.查询指定入职日期之后入职的员工信息
select * from emp2 where entrydate =(select entrydate from emp2 where name='易新月')