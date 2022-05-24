-- 这玩意和do while一样

-- 计算1累加到n
create procedure p8(in n int)
begin
    declare total int default 0;
    repeat
        set total:=total+n;
        set n:=n-1;
    until   n<=0    -- 设置退出条件
    end repeat;

    select total;
end;

call p8(100)