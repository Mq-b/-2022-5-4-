-- 变量:局部变量
-- 声明
-- 赋值
create procedure p2()
begin
    declare stu_count int default 0;   -- 声明局部变量
    --  set stu_count:=100;            -- 赋值
    select count(*) into stu_count from student;    -- 使用into把查询到的赋值给局部变量
    select stu_count;       -- 查询局部变量
end;

call p2();

-- 局部变量的作用域在begin和end之间 超出作用域就无效