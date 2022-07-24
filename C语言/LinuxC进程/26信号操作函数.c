/*
信号集操作函数：

	sigset_t set;  自定义信号集。

	sigemptyset(sigset_t *set);	清空信号集

	sigfillset(sigset_t *set);	全部置1

	sigaddset(sigset_t *set, int signum);	将一个信号添加到集合中

	sigdelset(sigset_t *set, int signum);	将一个信号从集合中移除

	sigismember（const sigset_t *set，int signum); 判断一个信号是否在集合中。 在--》1， 不在--》0

设置信号屏蔽字和解除屏蔽：

	int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

		how:	SIG_BLOCK:	设置阻塞

			SIG_UNBLOCK:	取消阻塞

			SIG_SETMASK:	用自定义set替换mask。

		set：	自定义set

		oldset：旧有的 mask。

查看未决信号集：

	int sigpending(sigset_t *set);

		set： 传出的 未决信号集。
*/