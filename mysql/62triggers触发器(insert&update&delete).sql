-- 触发器
-- 需求:通过触发器日志记录user表的数据变更日志(uesr_logs)，包含增加 修改 删除

-- 准备工作:日志表 user_logs
create table user_logs(
     id int(11) not null auto_increment,
     operation varchar(20) not null comment'操作类型,insert/update/delete',
     operate_time datetime not null comment'操作时间',
     operate_id int(11) not null comment'操作的ID',
     operate_params varchar(500)comment'操作参数',
     primary key(`id`)
 )engine=innodb default charset=utf8;

-- 插入数据触发器
create trigger tb_user_insert_trigger
    after insert on tb_user for each row -- 行级触发器
begin
    insert into user_logs(id, operation, operate_time, operate_id, operate_params) VALUES
    (null,'insert',now(),new.id,concat('插入的数据内容为:id=',new.id,',name=',new.name,',phone=',new.phone,',email=',new.email,',profession=',new.profession));
end;

-- 查看
show triggers;  -- 返回当前表的触发器

-- 删除
drop trigger tb_user_insert_trigger;

-- 插入数据到tb_user 测试
insert into tb_user values (26,'三皇子','18809091212','erhuangzi@163.com','软件工程',23,'1','1',now());

select * from user_logs;

-- 修改数据的触发器     -- old表示更新之前的数据 new表示更新之后的数据
create trigger tb_user_update_trigger
    after update on tb_user for each row -- 行级触发器   影响了多少行就触发多少次
begin
    insert into user_logs(id, operation, operate_time, operate_id, operate_params) VALUES
    (null,'update',now(),new.id,
    concat('更新之前的数据:id=',old.id,',name=',old.name,',phone=',old.phone,',email=',old.email,',profession=',old.profession,
        ' | 更新之后的数据:id=',new.id,',name=',new.name,',phone=',new.phone,',email=',new.email,',profession=',new.profession));
end;

show triggers;  -- 查看
-- 测试
update tb_user set profession='会计' where id =23;

update tb_user set profession='会计' where id<=5;


-- 删除数据的触发器
create trigger tb_user_delete_trigger
    after delete on tb_user for each row -- 行级触发器   影响了多少行就触发多少次
begin
    insert into user_logs(id, operation, operate_time, operate_id, operate_params) VALUES
    (null,'delete',now(),old.id,        -- 数据一旦被删除就没有id了 所以使用old获取删除之前的
    concat('删除之前的数据:id=',old.id,',name=',old.name,',phone=',old.phone,',email=',old.email,',profession=',old.profession));
end;

show triggers;
-- 测试
delete from tb_user where id=25;

delete from tb_user where id=26;

-- 总结一下 我们是先创建了一个表user_logs用来存储触发器的数据触发器的创建和视图什么的差不多 但是我们创建了之后
-- 先写上触发条件   比如  after insert on tb_user for each row 就是说tb_user的insert操作会触发 这里的for each row是指每一行
-- 也就是行级触发器 对任何一行的insert操作都会触发触发器 然后就会执行begin 到end里面的语句 我们这里都写成了插入数据到user_logs表内