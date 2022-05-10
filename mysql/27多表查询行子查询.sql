-- 行子查询
-- 1.查询与”张无忌“的薪资级直属领导相同的员工信息；
-- a.查询“张无忌”的薪资及直属领导
select salary,managerid from emp2 where name='张无忌';

-- b.查询与“张无忌”的薪资及直属领导相同的员工信息；
select * from emp2 where (salary,managerid)=(select salary,managerid from emp2 where name='张无忌');