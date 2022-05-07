-- 数值函数
-- ceil     向上取整
select ceil(1.1);

-- floor    向下取整
select floor(1.9);

-- mod      取模运算
select mod(7,4);

-- rand     随机数0-1之间
select rand();

-- round    保留小数位,四舍五入
select round(2.345,2);

-- 案例：通过数据库函数，生成一个六位数的随机验证码
select lpad(round(rand()*1000000,0),6,'0');