-- 多表查询
-- 表1
create table student(
    id int auto_increment primary key comment '主键ID',
    name varchar(10) comment '姓名',
    no varchar(30) comment '学号'
)comment '学生表';
insert into student values
(null,'黛绮丝','20000100101'),
(null,'谢逊','2000100102'),
(null,'殷天正','2000100103'),
(null,'韦一笑','2000100104');

desc student ; -- 显示表结构
-- 表2
create table course(
    id int auto_increment primary key comment '主键ID',
    name varchar(10) comment '课程名称'
)comment '课程表';
insert into course values (null,'Java'),(null,'PHP'),(null,'MySql'),(null,'Hadoop');
-- 中间表
create table student_course(
   id int auto_increment comment '主键' primary key,
   studentid int not null  comment '学生ID',
   courseid  int not null  comment '课程ID',
   constraint fk_courseid foreign key (courseid) references  course(id),
   constraint fk_studentid foreign key (studentid) references student(id)
)comment '学生课程中间表';
insert into student_course values(null,1,1),(null,1,2),(null,1,3),(null,2,2),(null,2,3),(null,3,4);

-- 一对一
create table tb_user(
    id int auto_increment primary key comment '主键ID',
    name varchar(10) comment '姓名',
    age int comment '年龄',
    gender char(1) comment '1:男，2:女',
    phone char(11) comment '手机号'
)comment '用户基本信息表';

create table to_user_edu(
    id int auto_increment primary key comment '主键ID',
    degree varchar(20) comment '学历',
    major varchar(50) comment '专业',
    primaryshcool varchar(50) comment '小学',
    middleschool varchar(50) comment '中学',
    university varchar(50) comment '大学',
    userid int unique comment '用户ID',
    constraint fk_userid foreign key(userid) references tb_user(id)
)comment '用户基本信息表';

insert into tb_user(id,name,age,gender,phone)values
            (null,'黄渤',45,'1','1880000111'),
            (null,'冰冰',35,'2','1880000222'),
            (null,'马云',55,'1','1880000888'),
            (null,'李红艳',50,'1','1880000999');

insert into to_user_edu (id, degree, major, primaryshcool, middleschool, university, userid) values
        (null,'本科','舞蹈','静安区第一小学','静安区第一中学','北京舞蹈学院',1),
        (null,'硕士','表演','朝阳区第一中学','朝阳区第一中学','北京电影学院',2),
        (null,'本科','英语','杭州市第一小学','杭州市第一小学','杭州师范大学',3),
        (null,'本科','应用数学','阳泉第一小学','阳泉区第一中学','清华大学',4);
