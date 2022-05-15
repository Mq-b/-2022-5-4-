-- 查询建表语句 -- 默认存储引擎:InnoDB
show create table account;

-- 查询当前数据库所支持的存储引擎
show engines;

-- 创建表my_myisom,并指定MyISAM存储
create table my_misom(
    id int,
    name varchar(10)
)engine = MyISAM;

-- 创建表my_memory,并指定Memory存储
create table my_memory(
    id int,
    name varchar(10)
)engine = Memory;

show variables like 'innodb_file_per_table';