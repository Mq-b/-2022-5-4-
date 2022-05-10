-- union all，union
-- 1.将薪资低于5000的员工，和年龄大于50岁的员工全部查询出来

select * from emp2 where salary<5000    -- 使用union all关键字是直接把两次查询结果合并
union all
select* from emp2 where age>50;

select * from emp2 where salary<5000    -- 对查询的结果合并，去重
union
select* from emp2 where age>50;