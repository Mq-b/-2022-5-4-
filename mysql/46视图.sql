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
create or replace view stu_v_1 as select id,name from student where id <= 20;
alter view stu_v_1 as select id,name from student where id<=10;

-- 删除视图
drop view if exists stu_v_1;

-- ----------------------------------------------------------------------------
create or replace view stu_v_1 as select id,name from student where id<=20 with local check option; -- 视图的检查选项

select * from stu_v_1;

insert into stu_v_1 values(6,'Tom');
-- 视图中不存储数据 视图对应的是基表 插入数据是插入到基表student
insert into stu_v_1 values(30,'Tom');

-- cascaded
create or replace view stu_v_1 as select id,name from student where id<=20;

insert into stu_v_1 values(5,'Tom');

insert into stu_v_1 values(25,'Tom'); #这个视图不会检查我们的增删改查操作 所以可以插入

create or replace view stu_v_2 as select id,name from stu_v_1 where id>=10 with cascaded check option;

insert into stu_v_2 values(7,'Tom'); # 无法插入

insert into stu_v_2 values(26,'Tom'); # 无法插入

insert into stu_v_2 values(15,'Tom'); # 可插入

create or replace view stu_v_3 as select id,name from stu_v_2 where id<=15

insert into stu_v_3 values(11,'Tom'); # 可插入

insert into stu_v_3 values(17,'Tom'); # 可插入

insert into stu_v_3 values(28,'Tom'); # 无法插入