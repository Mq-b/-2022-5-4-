-- 变量:系统变量  session是当前会话 意思不会影响其他会话
-- 查看系统变量
show session variables;

show session variables like 'auto%';
show global variables like'auto%';

select @@global.autocommit;     -- 查看全局
select @@session.autocommit;    -- 查看当前会话

-- 设置系统变量   设置会话的提交
set session autocommit =1;

insert into course(id,name)values(6,'ES');

-- 设置全局系统变量 会话提交        但是重启之后依然会变回默认值
set global autocommit =0;