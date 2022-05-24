-- 要使视图可更新，视图中的行与基础表中的行之间必须存在一对一的关系。如果视图包含以下任何一
-- 项，则该视图不可更新：
-- A. 聚合函数或窗口函数（SUM()、 MIN()、 MAX()、 COUNT()等）
-- B. DISTINCT
-- C. GROUP BY
-- D. HAVING
-- E. UNION 或者 UNION ALL

-- 创建视图 使用聚合函数
create view stu_v_count as select count(*) from student;

insert into stu_v_count values(10);  # 无法插入更新