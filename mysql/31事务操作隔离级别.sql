-- 查看事务隔离级别
select @@transaction_isolation;

-- 设置事务隔离级别
set session transaction isolation level  read uncommitted;

set session transaction isolation level  repeatable read; -- 默认隔离级别

insert into emp(id, workno, name, gender, age, idcard, workaddress, entrydate)
values (7,'1','柳岩2','女',20,'123456789012345670','北京','2000-01-01');