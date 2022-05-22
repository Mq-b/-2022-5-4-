-- 视图是一张虚拟的表 我们可以像操作表一样操作视图
-- 创建视图
create or replace view stu_v_1 as select id,name from student where id<=10;

-- 查询视图
-- 查看创建视图的语句:show create view 视图名称
show create view stu_v_1;

-- 查询视图的数据
select * from stu_v_1;

select * from stu_v_1 where id<3;

-- 修改视图
create or replace view stv_v_1 as select id,name,no from student where id <= 10;
alter view stu_v_1 as select id,name from student where id<=10;

-- 删除视图
drop view if exists stu_v_1;