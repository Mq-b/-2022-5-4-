-- 数据准备
create table account(
    id int primary key AUTO_INCREMENT comment 'ID',
    name varchar(10) comment '姓名',
    money double(10,2) comment '余额'
) comment '账户表';
insert into account(name, money) VALUES ('张三',2000), ('李四',2000);

-- 恢复数据
update account set money=2000 where name='张三' or name='李四';


select @@autocommit;    -- 查看提交事务的方式，默认1，自动提交

set @@autocommit=0;     -- 设置为手动提交


-- 转账操作（张三给李四转账1000）
-- 1.查询张三账户余额
select * from account where name='张三';

-- 2.将张三账户余额-1000
update account set money = money -1000 where name='张三';

-- 3.将李四账户余额+1000
update account set money = money + 1000 where name='李四';


-- 提交事务
commit;

-- 回滚事务 如果报错就回滚事务，保证数据的正确性
rollback;

-- 方式二
-- 转账操作（张三给李四转账1000）
start transaction;
-- 1.查询张三账户余额
select * from account where name='张三';

-- 2.将张三账户余额-1000
update account set money = money -1000 where name='张三';

-- 3.将李四账户余额+1000
update account set money = money + 1000 where name='李四';


-- 提交事务
commit ;

-- 回滚事务
rollback ;

-- 第一种方式是关闭掉自动提交，通过commint提交事务，rollback回滚事务
-- 第二种方式是通过指令start transaction;如果事务执行成功，就执行commit ;指令，反之执行rollback ;