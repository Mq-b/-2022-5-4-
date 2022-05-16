-- 查询年龄大于15的员工姓名，年龄，并根据年龄进行排序
select name,age from emp where age>15 order by age asc;

-- from先执行 然后执行的while select
select name,age from emp e where e.age>15 order by age asc;

-- select语句先执行 再执行的order by 所以可以使用select的别名
select e.name ename,e.age eage from emp e where e.age>15 order by eage asc;

 如果设置了别名，那么就必须使用别名，比如设置了e，那么只能e. 不能使用emp.

# from...
# where..
# select...
# order by...
# limit...

/*
select name,age from emp where age>15 order by age asc;

select name,age from emp e where e.age>15 order by age asc;

select e.name ename,e.age eage from emp e where e.age>15 order by age asc;
*/