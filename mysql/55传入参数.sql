-- 1.根据传入参数score，判定当前分数对应的分数等级，并返回。
-- score >= 85分，等级为优秀。
-- score >= 60分 且 score < 85分，等级为及格。
-- score < 60分，等级为不及格。
create procedure p4(in score int,out result varchar(10))
begin
    if score>=85 then
        set result:='优秀';
    elseif score>=60 then
        set result:='及格';
    else
        set result:='不及格';
    end if;
end;

call p4(98,@result);
select @result;

-- 2.将传入的200分制的分数，进行换算，换算成百分制，然后返回。
create procedure p5(inout score double)
begin
    set score:=score*0.5;
end;
set @score=78;
call p5(@score);
select @score;