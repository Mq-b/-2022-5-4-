-- pofile详情
-- 通过have_profiling参数 能够看到当前MySQL是否支持profile操作
SELECT @@have_profiling;

-- 默认profiling是关闭的 可用通过set语句再session/global级别开启profiling
SET profiling=1;

-- 执行一系列的业务SQL的操作 然后通过如下指令查看指令的执行耗时:

--查看每一条SQL的耗时情况
show profiles;

-- 查看指定的query id的SQL语句各个阶段的耗时情况 id我们自己填入 根据上一句查询到的
show profile for query query -- id;

-- 查看指定query_id的SQL语句CPU的使用情况
show profile cpu for query --id;