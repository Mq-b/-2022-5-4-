-- while    计算从1累加到n的值 n为传入的参数值

create procedure p7(in n int)
begin
    declare total int default 0;    -- 声明一个变量total初始化0
    while n>0 do
        set total:=total+n;
        set n:=n-1;
        end while;
    select total;
end;

call p7(100);