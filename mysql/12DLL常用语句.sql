-- 修改表名
alter table user rename to temp;

-- 修改字段数据类型
alter table temp modify ID int;     -- modify后跟字段名 表示要修改这个字段的类型，然后加上类型即可

-- 修改字段名和字段类型,注释
alter table temp change id ID tinyint unsigned comment '序号';     --ALTER TABLE 表名 CHANGE 旧字段名 新字段名 类型 (长度) [ COMMENT 1 注释 ] [ 约束 ];

-- 查询操作
-- 查询当前数据库所有表
show tables;

-- 查询表结构
desc temp;

-- 查询指定表的建表语句
show create table temp;

-- 修改数据
update temp set id=100 where age=10;

-- 删除字段
alter table temp  drop ID;

-- 添加字段
ALTER TABLE temp ADD ID INT(4);

/*
alter table user rename to temp;

alter table temp modify ID int

show tables

desc temp

show create table temp;

update temp set id=100 where age=10;

alter table temp drop ID;

alter table temp add id int(4);
*/