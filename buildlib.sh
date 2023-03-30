#!/bin/bash
gcc -c -fpic ./src/kernel/tool.c -g
gcc -c -fpic ./src/kernel/cls.c -g
gcc -c -fpic ./src/kernel/date.c -g
gcc -c -fpic ./src/kernel/doskey.c -g
gcc -c -fpic ./src/kernel/find.c -g
gcc -c -fpic ./src/kernel/comp.c -g
gcc -c -fpic ./src/kernel/exit.c -g
gcc -c -fpic ./src/kernel/more.c -g
gcc -c -fpic ./src/kernel/help.c -g
gcc -shared -fpic -o libutils.so cls.o tool.o date.o doskey.o find.o comp.o exit.o more.o help.o