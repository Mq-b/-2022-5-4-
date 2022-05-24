-- 根据传入的参数uage，来查询用户表tb_user中，所有的用户年龄小于等于uage的用户姓名
-- （name）和专业（profession），并将用户的姓名和专业插入到所创建的一张新表
-- (id,name,profession)中。
create procedure p11(in uage int)
begin
    declare uname varchar(100);     -- 声明两个局部变量用于数据中转
    declare upro  varchar(100);
    declare u_cursor cursor for select name,profession from tb_user where age<=uage;    -- 要先声明局部变量才能声明游标
    declare exit handler for SQLSTATE '02000'close u_cursor;       -- 满足02000状态码就执行退出处理 关闭游标 个人觉得像捕获处理异常
    declare exit handler for not found close u_cursor;         -- 和上面一句一样 not found表示 没有找到   都是条件处理程序
    drop table if  exists tb_user_pro;      -- 表如果已经存在就先删除
    create table if not exists tb_user_pro(
        id int primary key auto_increment,
        name varchar(100),
        profession varchar(100)
    );
    open u_cursor;      -- 开启游标
    while true do       -- 循环遍历游标的数据插入到新表
        fetch u_cursor into uname,upro; -- 获取游标的数据到两个字段
        insert into tb_user_pro values(null,uname,upro); -- 插入到表中
    end while;
    close u_cursor;      -- 关闭游标
end;

call p11(30);