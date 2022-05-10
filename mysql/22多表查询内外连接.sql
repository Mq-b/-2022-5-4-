-- 多表查询   笛卡尔积
select * from emp2,dept;

-- 隐式内连接，查询两个表的交集
select * from emp2,dept where emp2.dept_id=dept.id;

-- 显示外连接，和上面结果一样,语法不同
select *from emp2 join dept on emp2.dept_id=dept.id;

-- 1.查询每一个员工的姓名，及关联的部门的名称(隐式内连接)
select emp2.name,dept.name from emp2,dept where emp2.dept_id=dept.id;
-- 取别名的方式，没区别，但是取了别名就不能再使用表原来的名字
select e.name,d.name from emp2 e,dept d where e.dept_id=d.id ;

-- 2.查询每一个员工的姓名,及关联的部门名称(显式连接实现)
select e.name,d.name from emp e inner join dept d on e.id = d.id; -- inner可以省略


 -- 外链接演示
-- 1.查询emp2表的所有数据，和对象的部门信息(左外连接)
select e.*,d.name from emp2 e left outer join dept d on e.dept_id=d.id;

-- 2.查询dept表的所有数据，和对应的员工信息(右外连接)
select e.*,d.name from emp2 e right outer join dept d on e.dept_id=d.id;
