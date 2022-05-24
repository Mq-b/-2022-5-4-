-- 变量:用户变量
-- 赋值
set @myname ='itheima';
set @myage := 10;
set @mygender:='男',@myhobby:='java';    -- 也可以联合赋值

select @mycolor:='red';

select count(*) into @mycount from tb_user;     -- 查询结果赋值给自定义变量

-- 使用
select @myname,@myage,@mygender,@myhobby;

select @mycolor,@mycount;