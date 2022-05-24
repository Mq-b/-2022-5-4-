-- 存储函数
-- 1.从1累加到n的值
create function fun1(n int) -- 可以不写in 默认in 也只能是in
returns int deterministic   -- returns设置返回值类型以及描述
begin
    declare total int default 0;

    while n>0 do
        set total:=total+n;
        set n:=n-1;
    end while;
    return total;
end;

select fun1(100);
-- 存储函数必须返回值    存储函数能做的存储过程都能完成