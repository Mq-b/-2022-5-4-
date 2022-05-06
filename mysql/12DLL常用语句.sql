-- 修改表名
alter table user rename to temp;

-- 修改字段数据类型
alter table temp modify ID int;

-- 修改字段名和字段类型,注释
alter table temp change id ID tinyint unsigned comment '序号';

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