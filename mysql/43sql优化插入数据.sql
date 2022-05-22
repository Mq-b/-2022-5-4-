-- insert 优化
-- 1. 批量插入
inset into tb_test values(1,'Tom'),(2,'Cat'),(3,'Jerry');

-- 2. 手动提交事务
start transaction;
-- 插入语句
commit;

-- 3.主键顺序插入提升效率     就是按照有序插入

-- 4.local批量插入

-- 如果一次性需要插入大批量数据 使用insert语句插入性能较低 此时可以使用mysql数据库提供的load指令进行插入
-- 客户端连接服务器时 加上参数--local-infile
mysql -——local-infile -u root -p
-- 设置全局参数local_infile为1 开启从本地加载文件导入数据的开关
create database itheima2;   -- 创建一个数据库
select @@local_infile;      -- 查询开关是否打开

set global local_infile=1;  -- 把开关设置为打开
-- 执行load指令将准备好的数据 加载到表结构中
load data local infile '/root/load_user_100w_sort.sql' into table tb_user fields
terminated by ',' lines terminated by '\n' ;

-- 加载100万条数据到了表中