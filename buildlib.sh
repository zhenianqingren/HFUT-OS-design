#!/bin/bash
gcc -c -fpic ./src/kernel/tool.c -g -O0
gcc -c -fpic ./src/kernel/cls.c -g
gcc -c -fpic ./src/kernel/date.c -g
gcc -c -fpic ./src/kernel/doskey.c -g
gcc -c -fpic ./src/kernel/find.c -g
gcc -c -fpic ./src/kernel/comp.c -g
gcc -c -fpic ./src/kernel/exit.c -g
gcc -c -fpic ./src/kernel/more.c -g
gcc -c -fpic ./src/kernel/help.c -g
gcc -shared -fpic -o libutils.so cls.o tool.o date.o doskey.o find.o comp.o exit.o more.o help.o
# fPIC 的全称是 Position Independent Code， 用于生成位置无关代码。
# 加了 fPIC 实现真正意义上的多个进程共享 so 文件。
# 多个进程引用同一个 PIC 动态库时，可以共用内存。这一个库在不同进程中的虚拟地址不同，但操作系统显然会把它们映射到同一块物理内存上。
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/mice/learn/LinuxC_Programming/OSdesign/HFUT-OS-design/