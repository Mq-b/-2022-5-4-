-- 1.计算从1累加到n的值 n为传入的参数值
create procedure p9(in n int)
begin
    declare total int default 0;

    sum:loop    -- 循环开始
       if n<=0 then
           leave sum;   -- 相当于break
       end if;
       set total:=total+n;
       set n:=n-1;
    end loop;
    select total;
end;

call p9(10);

-- 2.计算1到n之间的偶数累加的值 n为传入的值
create procedure p10(in n int)
begin
    declare total int default 0;

    sum:loop    -- 循环开始 sum相当于给这个循环命名为sum
       if n<=0 then
           leave sum;   -- 相当于break
       end if;
       if n%2=1 then
           set n:=n-1;
           iterate sum;
       end if;

       set total:=total+n;
       set n:=n-1;
    end loop;
    select total;
end;

call p10(100);