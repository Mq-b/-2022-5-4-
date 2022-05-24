-- 存储过程基本语法
-- 创建
create procedure p1()
begin
    select count(*) from student;
end;

-- 调用
call p1();
-- 查看存储过程创建的定义
select * from information_schema.ROUTINES where ROUTINE_SCHEMA='itheima';

show create procedure p1;
-- 删除
drop procedure if exists p1;

delimiter $$ -- 把结束符设置为$$ 以此解决在命令行遇到分号认为sql语句结束的问题

create procedure p1()
begin
    select count(*) from student;
end$$

delimiter ; -- 重新指定结束符为分号