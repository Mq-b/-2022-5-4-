-- 聚合函数
-- 1.统计该企业员工数量
select count(*) from emp;
select count(idcard) from emp;  -- null值不参与聚合函数运算

-- 2.统计该企业员工的平均年龄
select avg(age) from emp;

-- 3.统计该企业员工的最大年龄
select max(age) from emp;

-- 4.统计该企业员工的最小年龄
select min(age) from emp;

-- 5.统计北京地区员工的年龄之和
select sum(age) from emp where workaddress ='北京';

/*
select count(*) from emp;
select coutn(idcard) from emp;

select avg(age) from emp;

select max(age) from emp;

select min(age) from emp;

select sum(age) from emp where workaddress='北京';
*/