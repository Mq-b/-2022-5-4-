-- 总结，cascaded是强制向上级联，local是有检查选项才级联

-- 说人话就是  创建视图的时候使用了 where 条件 with cascaded check option 
-- 的话除了要满足这一个视图的条件还得强制满足之前的没有加上cascaded的视图的条件

-- local则不少强制的 只有上一个视图也是使用的local才会判断 否则不会