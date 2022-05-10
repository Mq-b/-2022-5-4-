-- 自连接 自连接查询必须取别名,一定要注意
-- 1.查询员工，从其从属领导的名字
-- 表结构 emp2 a，emp2 b2

select a.name,b.name from emp2 a,emp2 b where a.managerid=b.id;

-- 2. 查询所有员工emp级其领导的名字emp2，如果员工没有领导，也需要查询出来
-- 表结构 emp2 a，emp2 b

select a.name'员工',b.name'领导' from emp2 a left join emp2 b on a.managerid=b.id;