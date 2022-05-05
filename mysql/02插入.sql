#插入指定字段
insert into user(id, work_no, name, gender, age, idc_ard, entrydate) values(1,'1','Itcast','男',10,'1234567890123456789','2020-01-01');
insert into user(id, work_no, name, gender, age, idc_ard, entrydate) values(2,'2','Itcast2','男',1,'1234567890123456789','2020-01-01');
#显示
select * from  user;
#插入全部字段
insert  into user values(2,'2','张无忌','男',18,'1234567890123456789','2020-01-01');
#批量添加多个值可以逗号隔开
insert  into user values(3,'2','韦一笑','男',18,'1234567890123456789','2020-01-01'),(4,'2','赵敏','男',18,'1234567890123456789','2020-01-01')
