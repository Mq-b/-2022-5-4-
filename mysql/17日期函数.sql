-- 日期函数

-- curdate()    日期
select curdate();

-- curtime()    时间
select curtime();

-- now()    日期+时间
select now();

-- YEAR,HONTH,DAY
select MONTH(NOW());    -- 月份

select YEAR(NOW());     -- 年份

select DAY(NOW());      -- 日

-- date_add 第一个参数返回日期，然后加上第二个参数的日期，最后返回它们的和
select date_Add(now(),INTERVAL 70 MONTH);   -- 往后推70月
select date_Add(now(),INTERVAL 70 YEAR);   -- 往后推70年

-- datediff 返回两个日期之间的天数，第一个时间减去第二个时间，可以为负
select datediff('2021-12-01','2021-11-01');
select datediff('2021-11-01','2021-12-01');

-- 案例:查询所有员工的入职天数，并根据入职天数倒序排序。
select name,datediff(curdate(),entrydate) as 'entrydays' from emp order by entrydays desc;
-- 首先字段name，和入职天数，入职天数通过datediff函数计算，现在日期减去入职如期即可得出，然后为了方便和打印直观，as取别名，from emp后开始设置排序条件，
-- order by entrydays desc 这里排序使用的就是字段的别名