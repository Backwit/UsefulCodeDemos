#输出程序名称
OUTDIR = ./out
OUTEXE = search

TARGET = $(OUTDIR)/$(OUTEXE)
$(warning "TARGET... $(TARGET)")

#wildcard把 指定目录 ./ 和 ../lib 下的所有后缀是cpp的文件全部展开。
SRCS = $(wildcard *.cpp)
$(warning "SRCS: $(SRCS)")

#OBJS将$(SRCS)下的.cpp文件转化为.o文件
OBJS = $(SRCS:%.cpp =%.o)    
$(warning "OBJS: $(OBJS)")

#代表所使用的编译器
CC = g++  

#头文件查找路径
INCLUDES = -I./include -I. 

#链接库查找地址
LIBS = #-L../redis-2.8.3/deps/hiredis -lhiredis

#附加参数
CCFLAGS = -std=c++11 -g -Wall -O0   

all:$(TARGET)

$(TARGET) : $(OBJS)
	@if [ ! -d $(OUTDIR) ] ; then mkdir -p $(OUTDIR) ; fi;
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS) $(CCFLAGS)

%.o : %.c
	$(CC) -c $< $(CCFLAGS)

#清除中间文件及生成文件
clean:
	rm -rf $(OUTDIR)   

.PHONY:clean
