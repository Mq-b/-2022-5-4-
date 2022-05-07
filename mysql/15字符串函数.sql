-- concat 字符串拼接
select concat('Hello','MySqL');

-- lower    转换为小写
select lower ('Hello');

-- upper    转换为大写
select upper('Hello');

-- lpad     左填充，三个参数，第一个参数为原始字符串，第二个为需要长度，第三个为填充的字符
select lpad('01',5,'-');

-- rpad     右填充
select rpad('01',5,'-');

-- trim     去除头部和尾部的空格
select trim(' Hello MySQL ');

-- substring    截取字符串 从1开始
select substring('Hello MySQL',1,5);


-- 案例 员工工号统一为五位数，如第一位员工工号应该为00001
update emp set workno =lpad(workno,5,'0');