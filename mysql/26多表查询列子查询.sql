-- 列子查询
-- 1.查询'销售部'和'市场部'的所有员工信息
-- a.查询'销售部'和'市场部'的部门ID
select id from dept where name='销售部' or name='市场部';

-- b.根据部门ID，查询员工信息
select * from emp2 where dept_id in (select id from dept where name='销售部' or name='市场部');


-- 2.查询比财务部所有人工资都高的员工信息
select * from emp2 where salary >all (select salary from emp2 where dept_id = (select id from dept where name='财务部'));

-- 3.查询比研发部任意一人工资高的员工信息
-- a.查询研发部所有人员工信息
select salary from emp2 where dept_id = (select id from dept where name='研发部');

-- b.比研发部其中任意一人工资高的员工信息
select * from emp2 where salary > any ( select salary from emp2 where dept_id =(select id from dept where name = '研发部') );
select * from emp2 where salary > some ( select salary from emp2 where dept_id =(select id from dept where name = '研发部') );

-- all表示子查询的列表必须都满足才满足条件，any和some没区别，子查询只要满足一个就是满足要求