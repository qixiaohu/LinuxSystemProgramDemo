#obj=main.o sub.o add.o mul.o
target=app
# makefile中维护的变量
CPPFLAGS=-I ./
#makefile 中的函数
src=$(wildcard ./*.c)
obj=$(patsubst %.c, %.o, $(src))
$(target):$(obj)
	gcc $(obj) -o $(target)

# makefile 中的模式规则
%.o:%.c
	gcc -c $< -o $@ $(CPPFLAGS)

# 声明伪目标
.PHONY:clean
clean:
	-mkdir /abc
	-rm -f $(obj) $(target)

hello:
	echo "hello, makefile"
