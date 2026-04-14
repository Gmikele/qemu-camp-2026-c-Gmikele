# src/mybash/Makefile

CC = gcc
CFLAGS = -Wall -I../../include

# 可执行文件名
TARGET := mybash
# 最终输出到 BINDIR（比如 ./bin/）
BINDIR ?= ./bin
# 中间文件目录（比如 ./obj/src/mybash/）
OBJDIR ?= ./obj
LINKLIBS ?= -L../mysed/obj -L../mywc/obj -L../mytrans/obj -L../myfile/obj

# 源文件
SRCS := main.c
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))

# 最终二进制路径
TARGET_PATH := $(BINDIR)/$(TARGET)

all: $(TARGET_PATH)

# 创建目录
$(BINDIR) $(OBJDIR):
	@mkdir -p $@

# 编译目标文件
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 链接可执行文件
$(TARGET_PATH): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $(LINKLIBS) -o $@ $^ -lmysed -lmywc -lmytrans -lmyfile

clean:
	@rm -rf $(OBJDIR)/*.o $(TARGET_PATH)
