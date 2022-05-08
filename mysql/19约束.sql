create table user(
    id int primary key auto_increment comment '主键',
    name varchar(10) not null unique comment '姓名',
    age int check(age>0 && age<=120) comment'年龄',
    status char(1) default '1' comment '状态',
    gender char(1) comment '性别'
)comment '用户表';

-- 插入数据     不插入id，会进行主动的自增操作auto_increment
insert into user(name,age,status,gender) values('Tom1',19,'1','男'),('Tom2',25,'0','男');
insert into user(name,age,status,gender) values('Tom3',19,'1','男');

insert into user(name,age,status,gender) values(null,19,'1','男');   -- 错误，name字段设置了not null非空约束
insert into user(name,age,status,gender) values('Tom3',19,'1','男');   -- 错误，name字段设置了unique关键字，唯一约束

insert into user(name,age,status,gender) values('Tom4',80,'1','男');
insert into user(name,age,status,gender) values('Tom5',-1,'1','男');    -- 错误，age字段设置了check(age>0 && age<=120)约束
insert into user(name,age,status,gender) values('Tom5',121,'1','男');   -- 错误，和上面一样

insert into user(name,age,gender) values('Tom5',120,'男');   -- status设置了default '1'，不传递值则默认为1



