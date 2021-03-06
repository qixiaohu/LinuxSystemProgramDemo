date : 显示系统日期
cal:显示日历
logout和exit：退出当前用户
netstat –a:查看联机状态
ps –aux:产看后台执行程序
Sync:把内存中的数据写入磁盘【通常在关机前执行】

shutdown
     shutdown [-t n] [-krhnfF] time [‘msg’]
     -t n:在n秒后发送警告信息msg
     -k:仅发送警告，不是真的关机
     -r:将所有的服务停止后重启（常用）
     -h:将所有的服务停在后关机（常用）
     -n:直接关机
     -f:重启后省略fsck检查
     -F:强制进行fsck检查
reboot
    reboot [-n] [-w] [-d] [-f] [-i]
    -n:重启前不进行回填操作
    -w:并非真的重启，而是把记录写入到文档  /var/log/wtmp中去
    -d:不把记录写入上述文件中
    -f:强制重启
    -i:将网络相关装置停止后再重启

nano:简版的文本编辑器

Linux系统有7个运行级别(runlevel)
	运行级别0：系统停机状态，系统默认运行级别不能设为0，否则不能正常启动
	运行级别1：单用户工作状态，root权限，用于系统维护，禁止远程登陆
	运行级别2：多用户状态(没有NFS)
	运行级别3：完全的多用户状态(有NFS)，登陆后进入控制台命令行模式
	运行级别4：系统未使用，保留
	运行级别5：X11控制台，登陆后进入图形GUI模式
	运行级别6：系统正常关闭并重启，默认运行级别不能设为6，否则不能正常启动
	切换方式：init n

忘记root密码
	1、进入运行等级一（出现菜单时按e）, 按a键在quiet前加single
	2、按enter建，按b键
	3、用“setenforce 0”来关闭grub 
	4、执行passwd 指令，然后连续两次输入两次新的密码
	5、执行reboot指令

chmod -c  777 filename :文件属主或者root用户修改文件权限，并打印结果

chattr
	设置文件的隐藏属性
	chattr [+-=] [ASacdistu] 文件或目录
	a:只能增加数据，不能删除，只有root才能设置
	i:可以让文件“不能被删除、改名、设置连接，也无法写入或新增数据”,只有root可以设置
	s:如果文件被删除，将会完全从这个硬盘中删除
	u：与s相反
	+：增加某个特殊参数
	-：删除某个特殊参数
	=：仅有后面接的参数

lsattr
	显示文件夹的隐藏属性
	格式：lsattr [-adR] 文件或目录
	-a：显示隐藏文件的属性
	-R：连同子目录的数据一并列出
	-d :连接的如果是目录，仅列出目录本身的属性而非目录内的文件名

umask命令
	用来设置新建文件权限的掩码
	格式：umask ［模式］
	说明：
	Linux系统中目录的默认权限是drwxrwxrwx，文件的默认权限是-rw-rw-rw-。因此，有以下公式：
	新目录的权限= drwxrwxrwx －默认权限掩码
	新文件的权限= -rw-rw-rw- －默认权限掩码
	注意：基于安全原因，Linux系统不允许文件的默认权限有执行权
	不带任何参数的umask命令显示当前的默认权限掩码值

	Linux系统中目录的默认权限是drwxrwxrwx，文件的默认权限是-rw-rw-rw-。因此，有以下公式：
	新目录的权限= drwxrwxrwx －默认权限掩码
	新文件的权限= -rw-rw-rw- －默认权限掩码
Linux的文件类型：
	普通文件
	目录文件
    链接文件
    设备文件
	套接字：套接字(sockets):网络数据连接
	管道：管道（FIFO,pipe）：解决多个程序同时访问		一个文件所造成的错误问题，第一个属性[p]

Linux目录结构：
	Linux文件系统由文件和目录组成，文件是专门用来存储数据的对象，而目录是一种用来组织文件和其他目录的容器。
	/       ：根目录root(/)：根目录与开机、还原、系统修复等操作有关。
	/bin    : bin 就是二进制（binary）英文缩写，是存放用户可执行的二进制文件的目录。这里存放例如ls, mv, rm, mkdir, rmdir, gzip, tar, telnet及ftp等等常用的执行文件。 usr/local/bin、usr/bin
	/boot   ：这是放置Linux内核与启动相关文件的地方，这个目录底下的vmlinuz-xxx就是Linux的Kernel。如果引导加载程序选择grub的话，那么这个目录内还有/boot/grub这个子目录。
	/dev    ：存放与设备有关的文件，Unix/Linux系统均把设备当成是文件来看待，例如/dev/fd0代表软盘，就像Windows系统下的A区，而/dev/cdrom则代表光盘。这个目录底下的文件通常分为两种，分别是管理磁盘 I/O的块文件和串行设备的字符文件。
	/etc    ：这个目录是linux系统中最重要的目录之一。在这个目录下存放了系统管理时要用到的各种配置文件和子目录。我们要用到的网络配置文件，文件系统，x系统配置文件，设备配置信息，设置用户信息等都在这个目录下。
	/home   ：这是系统默认的用户根目录(home directory)，新增用户时默认会在/home下建立与用户名同名的子目录。如果建立一个用户，用户名是“jl”,那么在/home目录下就有一个对应的/home/jl路径，用来存放用户的主目录。 
	/lib    : lib是库（library）英文缩写，系统使用的函数库的目录。程序在运行过程中，可能会调用一些额外的参数，这需要函数库的支持，这些函数库就存在此处。
	/mnt    ：这个目录在一般情况下也是空的。可以临时将别的文件系统挂在这个目录下。 是软盘和光盘或者其他外部I/O设备的挂载点【默认会挂载到media目录下】，通常软盘挂在/mnt/floppy下，而光盘挂在/mnt/cdrom下。
	/proc   ：用于放置系统核心与执行程序所需的一些信息。这个目录将在启动的时候自动的被挂上，而且该目录底下不会占去硬盘空间！因为里面都是内存内的数据。
	/root   ：系统管理员的根目录
	/sbin   ：放置系统管理常用的程序，例如：fdisk, mke2fs,fsck, mkswap, mount等。与/bin不太一样的地方，这个目录下的程序通常是给root等系统管理员使用的程序。
	/tmp    ：存放临时文件的地方，重新引导后删除。/var/tmp下面的东西在重新引导之后都不删除。
	/usr    ：非常重要的一个目录，存放应用程序与命令，类似于Windows的“Program Files”, 是linux系统中占用硬盘空间最大的目录。 
	/var    : 用于存储各种快速增长或者变化的东西。
				/var/log：放置所有服务的登录文件或者错误日志
				/var/spool/mail 或/var/mail ：用户未读邮件默认存放地点是
				/var/lib：程序本身执行过程中，需要使用到的数据文件。
				/var/lock：解决冲突
				/var/spool：放置队列数据，“队列”是等待其他程序使用的数据。
				/var/run：某些程序或者服务启动后，将她们的pid放置这个目录下
				/var/cache：程序本身运行过程中产生的一些暂存文件

系统登录时候，用户会自动跳转到其home目录，root用户的home是/root，其他用户user的默认home目录是/home/user

echo $PATH  ： 查看当前系统环境变量【使用绝对路径或者相对路径直接指定某个命令的文件名来执行，会比查询PATH准确】

pwd  ： 命令将当前目录的全路径名称（从根目录）写入标准输出；全部目录使用 /（斜线）分隔；第一个 / 表示根目录，最后一个目录是当前目录 
        [-p]显示出实际路径，而非使用连接的路径

cd   ： ~user表示去user的家目录
		.（点）表示当前目录， ..（点点）表示父目录
		cd ~  返回当前用户主目录
		cd -   返回用户上次所在的目录

cat  ： filename1  >  filename2 ：将filename中的内容复制到自动新建的filename2中。【输出重定向：如果filename2已经存在则内容会被重写】
		cat file1 file2 > file3


nl [-bnw] filename
	-b:制定行号的指定方式
		-b a:表示不论是否为空行，同样列出行号
		-b t:如果有空行，空行不要列出行号
	-n:列出行号的表示方法
		-n ln:行号在字段的最左方显示
		-n rn:行号在字段的最右方显示，不加0
		-n rz:行号在字段的最右方显示，加0
	-w:行号字段占用的位数

UTF  ：  是Unicode Text Format的缩写，意为Unicode文本格式 

文件查找命令：
	which ：通过PATH进行搜索【eg:which pwd】
		-a 将所有可找到的命令列出，不仅仅列出第一个找到的命令 
	whereis : 会在特定目录中查找符合条件的文件【eg:whereis -b passwd】
		-b 　只查找二进制文件 
		-m 　只查找说明文件 
		-s   只找源文件
		-u   查找其他特殊的文件
	find ： 在目录结构中搜索文件，并执行指定的操作【直接搜索硬盘】【eg：find / -name bin】
		语法：find  起始目录  查找条件  [操作] 
		起始目录：find命令所查找的目录路径；例如可用.来表示当前目录，用/来表示系统根目录
		查找条件：匹配机制，如可以按照文件名、文件权限、修改时间等进行文件查找
		操作：按指定条件查找后进行的特定处理方法，如将查找到的文件在屏幕上显示出来，或对其进行权限修改，或将查找到的文件删除等等
		可以为find命令同时指定多个查找条件进行查找，指定多个条件的查找条件可以是一个用逻辑运算符not、and或or组成的复合条件
		and  逻辑与，在命令中用“-a” 表示，是默认选项，可以省略
		or  逻辑或，在命令中用“-o” 表示
		not  逻辑非，在命令中用“！”表示
			-name ‘字串’  按照文件名查找文件
			- lname ‘字串’   查找文件名匹配所给字串的所有符号链接文件
			-gid n  查找属于ID号为n的用户组的所有文件
			-uid n  查找属于ID号为n的用户的所有文件
			-group ’字串’  查找属于用户组名为所给字串的所有的文件
			-user ’字串’ 查找属于用户名为所给字串的所有的文件 
			-empty  查找大小为0的目录或文件 
			-path ’字串’  查找路径名匹配所给字串的所有文件
			-perm 权限  查找具有指定权限的文件和目录，权限的表示可以如755，644   
			-nogroup  查找无有效所属组的文件，即该文件所属的组在/etc/groups中不存在
			-nouser  查找无有效属主的文件，即该文件的属主在/etc/passwd中不存在
			-type  查找某一类型的文件
			-size n [bck] 查找文件长度为n块的文件，带有c时表示文件长度以字节计
			-depth 在查找文件时，首先查找当前目录中的文件，然后再在其子目录中查找     
			
        可执行的操作：	【eg:find / -name install.log -exec ls -l{}\】
        	-exec 命令 {} \； 对符合条件的文件执行所给的命令 
							1、{}表示命令的参数即为所找到的文件
							2、命令的末尾必须以“\ ；”结束
			-ok 命令 {} \； 同-exec，但会询问用户是否执行该命令

文件系统  ：组成：superblock 、inode 、 block
	磁盘的起始块为超级块（superblock）
	每个文件系统开始的那个块称为超级块，用来记录该分区的相关信息。
	与硬盘分区表不同之处  ：superblock是存储一个硬盘上某个分区的文件信息，而硬盘分区表记录的是整个硬盘上的所有分区的分布信息

在格式化完毕之后块和inode也已经规划好，inode 的数量与大小也是在格式化时就已经固定了

inodetable的作用  ： 块是记录文件内容数据的地方，而inode则是记录文件属性、及该文件放置在哪个块上。所以，每个文件都仅会占用一
					 个inode，因此，文件系统能够建立的文件数量与 inode 的数量有关。Inode大小固定为128bytes
	inodetable记录的信息
 		该文件的存取模式(read/write/excute)；
		该文件的拥有者与群组(owner/group)；
		该文件的容量；
		该文件建立或状态改变的时间(ctime)；
		最近一次的读取时间(atime)；
		最近修改的时间(mtime)；
		定义文件特性的旗标(flag)，如 SetUID…；
		该文件真正内容的指向 (pointer)；
	系统读取文件时需要先找到 inode，并分析 inode 所记录的权限与用户是否符合，若符合才能够开始实际读取 block 的内容
	目录：1、inode记录该目录相关属性
		  2、块记录这个目录下的相关文件（或目录）的关联性
	文件：1、inode记录文件相关属性，但不记录文件名称
		  2、块记录文件的数据内容
	Linux文件读取过程：当Linux系统要找到某个文件时，他首先由根目录/获取该文件的上层目录所在的inode，再由该目录所记录的文件关
					   联性获取该文件的inode，找到这个文件的属性及数据放置的地方，然后再去找数据存放的Block进而将数据取出利用。
	例如块设定为4K，如果一个文件为8K左右，一块1GB的硬盘，如果以8K来规划他的inode表的话，他的inode就会有 131072 个。
	分区被格式化为一个文件系统之后，基本上他一定会有 inode table与data area两个区块。

硬链接的限制：1、不能跨文件系统，因为不同的文件系统有不同的inode表
			  2、不能 link 目录









		




















