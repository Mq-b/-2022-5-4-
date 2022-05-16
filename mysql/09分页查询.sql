-- 分页查询
-- 1.查询第1页员工数据，每页展示5条记录
select * from emp limit 0,5;

select * from emp limit 5;

-- 2.查询第二页员工数据，每页展示5条记录    （页码-1）*页展示记录数
select * from emp limit 5,5

/*
select * from emp limit 0,5;

select * from emp limit 5;

select * from emp limit 5,5;
*/