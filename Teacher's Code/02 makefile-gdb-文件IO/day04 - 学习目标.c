============================================
                   学习目标
============================================
		* 掌握文件IO函数的使用
		* 了解阻塞和非阻塞的概念
		* 掌握文件操作相关函数的使用
		* 掌握目录操作相关函数的使用
		* 掌握dup、dup2函数的使用
		* 掌握fcntl函数的使用
============================================
                    知识点
============================================
1. 文件IO函数
		1>. open/close
				函数原型:
					int open(const char *pathname, int flags);
       				int open(const char *pathname, int flags, mode_t mode);
       	参数:
       		pathname -- 文件名
       		flags:
       			必选项: 互斥
       				O_RDONLY O_WRONLY O_RDWR
       			可选项:
       				O_CREAT -- 创建文件, open函数需要指定3个参数
       					O_EXCL -- 检查文件是否存在, 需要与O_CREAT一起使用
       				O_APPEND -- 追加文件
       				O_NONBLOCK -- 设置非阻塞
       				O_TRUNC -- 文件截断
       		mode: 八进制整型值, 必须指定O_CREAT属性
		2>. read
				函数原型:	
					ssize_t read(int fd, void *buf, size_t count);
				返回值:
					>0: 读出的字节数
					=0: 读文件完毕
					-1: 读失败
				参数:
					fd : 文件描述符, open的返回值
					buf: 缓冲区, 存储数据
					count: 缓冲区大小
		3>. write
				函数原型:  
					ssize_t write(int fd, const void *buf, size_t count);
				返回值:
					>0: 写入的字节数
					=0: 没有数据写入
					-1: 写失败
				参数:
					fd: open的返回值
					buf: 往文件中写入的数据
					count: 写入的字节数
		4>. lseek
				函数原型:
					off_t lseek(int fd, off_t offset, int whence);
				函数参数:
					fd: 文件描述符
					offset: 偏移量
					whence: SEEK_SET SEEK_CUR SEEK_END
										
				函数使用:
					1). 获取文件长度
							int len = lseek(fd, 0, SEEK_END);
					2). 获取文件指针的位置
							int pos = lseek(fd, 0, SEEK_CUR);
					3). 文件指针移动到文件头
							lseek(fd, 0, SEEK_SET);
					4). 文件拓展 ****** 文件原来100K, --> 1000k
							 1. lseek(fd, 1000, SEEK_END);
							 2. 需要对文件进行一次写操作, 否则不会拓展
							 		write(fd, "1", 1);
2. 阻塞和非阻塞
		1>. 对文件读写默认是阻塞还是非阻塞?
					阻塞
		2>. 阻塞和非阻塞是文件的属性还是read函数的属性?
					文件的属性
3. 文件操作相关函数
		如果操作失败: -1
		成功 >0 ==0
		1>. 获取文件属性
				 	int stat(const char *path, struct stat *buf);
       	 	int lstat(const char *path, struct stat *buf);
       	 	区别: 
       	 		stat -> 追踪函数
       	 		lstat -> 不追踪函数
    2>. 测试指定文件是否具有某种属性 -- 当前用户, 使用哪个用户调用这个函数, 这个用户就是当前用户
					int access(const char *pathname, int mode);
					参数:
						pathname: 文件名
						mode: 4中权限
							R_OK -- 读 
							W_OK -- 写 
							X_OK -- 执行 
							F_OK -- 文件是否存在
						返回值:
							0 - 有某种权限, 或者文件存在
							-1 - 没有, 或文件不存在
		3>. 修改文件权限
					int chmod(const char *filename, int mode);
					参数:
						filename: 文件名
						mode: 文件权限, 八进制数
							./a.out filename mod
		4>. 修改文件所有者和所属组
					int chown(const char *path, uid_t owner, gid_t group);
					函数参数:
						path -- 文件路径
						owner -- 整形值, 用户ID /etc/passwd
						group -- ....., 组ID		/etc/group
		5>. 修改文件大小
					int truncate(const char *path, off_t length);
					参数: 
						path -- 文件名
						length -- 文件的最终大小
							1. 比原来小, 删掉后边的部分
							2. 比原来大, 向后拓展
							
		6>. 创建一个硬链接 ln  文件名  硬件名
					int link(const char *oldpath, const char *newpath);
		7>. 创建一个软连接
					int symlink(const char *oldpath, const char *newpath);
		8>. 读软连接对应的文件名，不是读内容(该函数只能读软链接文件)
					ssize_t readlink(const char *path, char *buf, size_t bufsize);
					函数参数:
						path: 文件名
						buf: 读软链接中存储的路径, 放到buf中
						bufsize: buf的容量
		9>. 删除一个文件
					int unlink(const char *pathname);
					特点: 当文件处于打开状态, 对文件进行unlink, 文件不会被马上删除, 当fd被关闭的时候,文件被删除
		10>. 文件重命名
					int rename(const char *oldpath, const char *newpath);
4. 目录操作相关函数
		1>. 修改当前进程(应用程序)的路径 cd
					int chdir(const char *path);
					参数: 切换的路径
		2>. 获取当前进程的工作目录 pwd
					char *getcwd(char *buf, size_t size);
					返回值:
						成功: 当前的工作目录
						失败: NULL
					参数:
						buf: 缓冲区, 存储当前的工作目录
						size: 缓冲区大小
		3>. 创建目录 mkdir
					int mkdir(const char *pathname, mode_t mode);
					参数:
						pathname: 创建的目录名
						mode: 目录权限, 八进制的数, 实际权限: mode & ~umask
		4>. 删除一个空目录
					int rmdir(const char *pathname);
					参数: 空目录的名字
		5>. 打开一个空目录
					DIR *opendir(const char *name);
					参数: 目录名
					返回值: 指向目录的指针
		6>. 读目录
					struct dirent *readdir(DIR *dirp);
					参数: opendir的返回值
					返回值: 
		7>. 关闭目录
					int closedir(DIR *dirp);
5. 复制文件描述符
		1>. dup
		2>. dup2
6. 改变已经打开的文件的属性: fcntl
		1>. 复制一个已有的文件描述符
				int fd1 = fcntl(fd, F_DUPFD, 0);	// 返回值为新的文件描述符
		2>. 获取/设置文件状态标志
				1. 获取文件状态标识
						int flag = fcntl(fd, F_GETFL, 0);
				2. 设置文件状态标识
						flag |= O_APPEND;
						fcntl(fd, F_SETFL, flag);
				可以更改的几个标识: O_APPEND、O_NONBLOCK （常用）

============================================
                    复习
============================================
1. makefile
		使用: make -- 生成的第一条规则中的目标
		一个规则: 
			目标:依赖
				命令
		两个函数: - 所有函数都有返回值
			1>. src = $(wildcard /home/itcast/ *.c)
			2>. obj = $(patsubst %.c, %.o, $(src))
		三个自动变量: -- 只能在命令中使用
			$<: 依赖中的第一个
			$^: 所有依赖
			$@: 目标
			target = app
			$(target):main.c add.c
				gcc $^ -o $@
2. gdb
		1>. 是什么: 代码调试工具
		2>. 能干什么? 调试代码, -g
		3>. 怎么用: 熟练掌握命令
			0. 启动gdb: gdb 程序名
			1. 查看代码: l 行号
			2. 设置断点: b  行号
					条件断点: b 行号 if 变量==值
			3. 查看断点信息: i(info) b
			4. 删除断点: del/d/delete 断点的编号   (单个[n]  多个[m n l]  范围[m-n])
		4>. 让gdb跑起来:
					1. run(r) -- 停在断点的位置
					2. start -- 只执行一行
					3. c(continue) - 继续跑, 在下一个断点位置停止
		5>. 代码调试:
					1. n(next) -- 单步调试, 不会进入函数内部
					2. s(step) -- ........, 会进入函数内部
							从函数体内部出来: finish
					3. p(print) 变量名 - 打印变量的值
					4. ptype 变量名  -- 打印变量的类型
					5. display 变量名 - 追踪打印变量的值
							取消追踪 -- undisplay 编号
								获取编号: info display
					6. 设置变量的值: set var 变量名=指定的值
					7. unitl - 跳出循环
			6>. 退出gdb: q(quit)
