-- 排序查询
-- 1.根据年龄对公司员工进行升序排序
select * from emp order by age asc;  -- 升序
select * from emp order by age desc; -- 降序

select * from emp order by age ;   -- 省略写法，默认升序

-- 2.根据入职时间，对员工进行降序排序
select * from emp order by entrydate desc;

-- 3.根据年龄对公司的员工精选升序排序，年龄相同，再按照入职时间进行降序排序
select * from emp order by age asc,entrydate desc;
                                    -- 再按照入职时间进行升序排序
select * from emp order by age asc,entrydate asc;
                                    -- asc可以直接省略，和上面没区别
select * from emp order by age ,entrydate ;