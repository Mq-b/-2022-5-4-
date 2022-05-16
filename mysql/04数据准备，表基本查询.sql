-- 查询数据 -----------------------------------------
drop table employee;
-- 数据准备
create table emp(
    id          int                 comment '编号',
    workno      varchar(10)         comment '工号',
    name        varchar(10)         comment '姓名',
    gender      char(1)             comment '性别',
    age         tinyint unsigned    comment '年龄',
    idcard      varchar(18)         comment '身份证号',
    workaddress varchar(50)         comment '工作地址',
    entrydate   date                comment '入职时间'
)comment '员工表';

insert into emp(id, workno, name, gender, age, idcard, workaddress, entrydate)
values (1,'1','柳岩','女',20,'123456789012345678','北京','2000-01-01'),
       (2,'2','张无忌','男',18,'123456789012345678','北京','2005-09-01'),
       (3,'3','韦一笑','男',38,'123456789012345678','上海','2005-08-01'),
       (4,'4','赵薇','女',18,'123456789012345678','北京','2009-12-01'),
       (5,'5','周芷若','女',30,null,'北京','2009-12-01'),
       (6,'6','牛马','男',40,'12345678901234567X','山东','2005-6-7');



-- 基本查询
-- 1、查询指定字段 name，workno，age 返回
select name,workno,age from emp;

-- 2、查询所有字段返回
select id,workno,gender,age,idcard,workaddress,entrydate from emp;

select *from emp;

-- 3、查询所有员工的工作地址，起别名
select workaddress as '工作地址' from emp;
select workaddress  '工作地址' from emp;

-- 4、查询公司员工的上班地址(不要重复)
select distinct workaddress '工作地址' from emp;    -- distinct关键字用来去除重复

/*
select name,workno,gender,age,idcard,workaddress,entrydate from emp;

select * from emp;

select workaddress '工作地址' from emp;

select distinct workaddress '工作地址' from emp;
*/