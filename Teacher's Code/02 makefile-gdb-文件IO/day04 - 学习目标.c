============================================
                   ѧϰĿ��
============================================
		* �����ļ�IO������ʹ��
		* �˽������ͷ������ĸ���
		* �����ļ�������غ�����ʹ��
		* ����Ŀ¼������غ�����ʹ��
		* ����dup��dup2������ʹ��
		* ����fcntl������ʹ��
============================================
                    ֪ʶ��
============================================
1. �ļ�IO����
		1>. open/close
				����ԭ��:
					int open(const char *pathname, int flags);
       				int open(const char *pathname, int flags, mode_t mode);
       	����:
       		pathname -- �ļ���
       		flags:
       			��ѡ��: ����
       				O_RDONLY O_WRONLY O_RDWR
       			��ѡ��:
       				O_CREAT -- �����ļ�, open������Ҫָ��3������
       					O_EXCL -- ����ļ��Ƿ����, ��Ҫ��O_CREATһ��ʹ��
       				O_APPEND -- ׷���ļ�
       				O_NONBLOCK -- ���÷�����
       				O_TRUNC -- �ļ��ض�
       		mode: �˽�������ֵ, ����ָ��O_CREAT����
		2>. read
				����ԭ��:	
					ssize_t read(int fd, void *buf, size_t count);
				����ֵ:
					>0: �������ֽ���
					=0: ���ļ����
					-1: ��ʧ��
				����:
					fd : �ļ�������, open�ķ���ֵ
					buf: ������, �洢����
					count: ��������С
		3>. write
				����ԭ��:  
					ssize_t write(int fd, const void *buf, size_t count);
				����ֵ:
					>0: д����ֽ���
					=0: û������д��
					-1: дʧ��
				����:
					fd: open�ķ���ֵ
					buf: ���ļ���д�������
					count: д����ֽ���
		4>. lseek
				����ԭ��:
					off_t lseek(int fd, off_t offset, int whence);
				��������:
					fd: �ļ�������
					offset: ƫ����
					whence: SEEK_SET SEEK_CUR SEEK_END
										
				����ʹ��:
					1). ��ȡ�ļ�����
							int len = lseek(fd, 0, SEEK_END);
					2). ��ȡ�ļ�ָ���λ��
							int pos = lseek(fd, 0, SEEK_CUR);
					3). �ļ�ָ���ƶ����ļ�ͷ
							lseek(fd, 0, SEEK_SET);
					4). �ļ���չ ****** �ļ�ԭ��100K, --> 1000k
							 1. lseek(fd, 1000, SEEK_END);
							 2. ��Ҫ���ļ�����һ��д����, ���򲻻���չ
							 		write(fd, "1", 1);
2. �����ͷ�����
		1>. ���ļ���дĬ�����������Ƿ�����?
					����
		2>. �����ͷ��������ļ������Ի���read����������?
					�ļ�������
3. �ļ�������غ���
		�������ʧ��: -1
		�ɹ� >0 ==0
		1>. ��ȡ�ļ�����
				 	int stat(const char *path, struct stat *buf);
       	 	int lstat(const char *path, struct stat *buf);
       	 	����: 
       	 		stat -> ׷�ٺ���
       	 		lstat -> ��׷�ٺ���
    2>. ����ָ���ļ��Ƿ����ĳ������ -- ��ǰ�û�, ʹ���ĸ��û������������, ����û����ǵ�ǰ�û�
					int access(const char *pathname, int mode);
					����:
						pathname: �ļ���
						mode: 4��Ȩ��
							R_OK -- �� 
							W_OK -- д 
							X_OK -- ִ�� 
							F_OK -- �ļ��Ƿ����
						����ֵ:
							0 - ��ĳ��Ȩ��, �����ļ�����
							-1 - û��, ���ļ�������
		3>. �޸��ļ�Ȩ��
					int chmod(const char *filename, int mode);
					����:
						filename: �ļ���
						mode: �ļ�Ȩ��, �˽�����
							./a.out filename mod
		4>. �޸��ļ������ߺ�������
					int chown(const char *path, uid_t owner, gid_t group);
					��������:
						path -- �ļ�·��
						owner -- ����ֵ, �û�ID /etc/passwd
						group -- ....., ��ID		/etc/group
		5>. �޸��ļ���С
					int truncate(const char *path, off_t length);
					����: 
						path -- �ļ���
						length -- �ļ������մ�С
							1. ��ԭ��С, ɾ����ߵĲ���
							2. ��ԭ����, �����չ
							
		6>. ����һ��Ӳ���� ln  �ļ���  Ӳ����
					int link(const char *oldpath, const char *newpath);
		7>. ����һ��������
					int symlink(const char *oldpath, const char *newpath);
		8>. �������Ӷ�Ӧ���ļ��������Ƕ�����(�ú���ֻ�ܶ��������ļ�)
					ssize_t readlink(const char *path, char *buf, size_t bufsize);
					��������:
						path: �ļ���
						buf: ���������д洢��·��, �ŵ�buf��
						bufsize: buf������
		9>. ɾ��һ���ļ�
					int unlink(const char *pathname);
					�ص�: ���ļ����ڴ�״̬, ���ļ�����unlink, �ļ����ᱻ����ɾ��, ��fd���رյ�ʱ��,�ļ���ɾ��
		10>. �ļ�������
					int rename(const char *oldpath, const char *newpath);
4. Ŀ¼������غ���
		1>. �޸ĵ�ǰ����(Ӧ�ó���)��·�� cd
					int chdir(const char *path);
					����: �л���·��
		2>. ��ȡ��ǰ���̵Ĺ���Ŀ¼ pwd
					char *getcwd(char *buf, size_t size);
					����ֵ:
						�ɹ�: ��ǰ�Ĺ���Ŀ¼
						ʧ��: NULL
					����:
						buf: ������, �洢��ǰ�Ĺ���Ŀ¼
						size: ��������С
		3>. ����Ŀ¼ mkdir
					int mkdir(const char *pathname, mode_t mode);
					����:
						pathname: ������Ŀ¼��
						mode: Ŀ¼Ȩ��, �˽��Ƶ���, ʵ��Ȩ��: mode & ~umask
		4>. ɾ��һ����Ŀ¼
					int rmdir(const char *pathname);
					����: ��Ŀ¼������
		5>. ��һ����Ŀ¼
					DIR *opendir(const char *name);
					����: Ŀ¼��
					����ֵ: ָ��Ŀ¼��ָ��
		6>. ��Ŀ¼
					struct dirent *readdir(DIR *dirp);
					����: opendir�ķ���ֵ
					����ֵ: 
		7>. �ر�Ŀ¼
					int closedir(DIR *dirp);
5. �����ļ�������
		1>. dup
		2>. dup2
6. �ı��Ѿ��򿪵��ļ�������: fcntl
		1>. ����һ�����е��ļ�������
				int fd1 = fcntl(fd, F_DUPFD, 0);	// ����ֵΪ�µ��ļ�������
		2>. ��ȡ/�����ļ�״̬��־
				1. ��ȡ�ļ�״̬��ʶ
						int flag = fcntl(fd, F_GETFL, 0);
				2. �����ļ�״̬��ʶ
						flag |= O_APPEND;
						fcntl(fd, F_SETFL, flag);
				���Ը��ĵļ�����ʶ: O_APPEND��O_NONBLOCK �����ã�

============================================
                    ��ϰ
============================================
1. makefile
		ʹ��: make -- ���ɵĵ�һ�������е�Ŀ��
		һ������: 
			Ŀ��:����
				����
		��������: - ���к������з���ֵ
			1>. src = $(wildcard /home/itcast/ *.c)
			2>. obj = $(patsubst %.c, %.o, $(src))
		�����Զ�����: -- ֻ����������ʹ��
			$<: �����еĵ�һ��
			$^: ��������
			$@: Ŀ��
			target = app
			$(target):main.c add.c
				gcc $^ -o $@
2. gdb
		1>. ��ʲô: ������Թ���
		2>. �ܸ�ʲô? ���Դ���, -g
		3>. ��ô��: ������������
			0. ����gdb: gdb ������
			1. �鿴����: l �к�
			2. ���öϵ�: b  �к�
					�����ϵ�: b �к� if ����==ֵ
			3. �鿴�ϵ���Ϣ: i(info) b
			4. ɾ���ϵ�: del/d/delete �ϵ�ı��   (����[n]  ���[m n l]  ��Χ[m-n])
		4>. ��gdb������:
					1. run(r) -- ͣ�ڶϵ��λ��
					2. start -- ִֻ��һ��
					3. c(continue) - ������, ����һ���ϵ�λ��ֹͣ
		5>. �������:
					1. n(next) -- ��������, ������뺯���ڲ�
					2. s(step) -- ........, ����뺯���ڲ�
							�Ӻ������ڲ�����: finish
					3. p(print) ������ - ��ӡ������ֵ
					4. ptype ������  -- ��ӡ����������
					5. display ������ - ׷�ٴ�ӡ������ֵ
							ȡ��׷�� -- undisplay ���
								��ȡ���: info display
					6. ���ñ�����ֵ: set var ������=ָ����ֵ
					7. unitl - ����ѭ��
			6>. �˳�gdb: q(quit)
