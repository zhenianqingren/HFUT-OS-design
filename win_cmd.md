## CLS
cls命令是清屏命令，一般是在屏幕窗口中的内容较多的时候使用。  
执行该命令后，屏幕上的所有信息都被清除，光标重新定位至屏幕左上角。

cls /? ---查看官方帮助文档对CLS的解释说明

## DATE
date 命令用来查看和修改当前日期。  
date /? 查看 date 命令和参数的使用  
date /t 显示当前日期  
直接键入date会显示当前日期后提示修改新的日期  

## TIME
显示或设置系统时间。  
time: 显示当前时间设置和输入新时间的提示，请键入
不带参数的TIME。要保留现有时间，请按 Enter。  
如果命令扩展被启用，TIME 命令会支持/T命令行开关；该命令行开关告诉
命令只输出当前时间，但不提示输入新时间。  
\>time /t  
14:40  
\>time  
当前时间: 14:41:01.43  
输入新时间:  

## DOSKEY
编辑命令行，重新调用 Windows 命令，并创建宏。

DOSKEY [/REINSTALL] [/LISTSIZE=size] [/MACROS[:ALL | :exename]]
  [/HISTORY] [/INSERT | /OVERSTRIKE] [/EXENAME=exename] [/MACROFILE=filename]
  [macroname=[text]]

  /REINSTALL          安装新的 Doskey 副本。  
  /LISTSIZE=size      设置命令历史记录的缓冲区大小。  
  /MACROS             显示所有 Doskey 宏。  
  /MACROS:ALL         为具有 Doskey 宏的所有可执行文件显示
所有 Doskey 宏。  
  /MACROS:exename     显示指定可执行文件的所有 Doskey 宏。  
  /HISTORY            显示存储在内存中的所有命令。  
  /INSERT             指定你键入的新文本插入到旧文本中。  
  /OVERSTRIKE         指定新文本覆盖旧文本。  
  /EXENAME=exename    指定可执行文件。  
  /MACROFILE=filename 指定要安装的宏文件。  
  macroname           指定你创建的宏的名称。  
  text                指定要录制的命令。  

## FIND
在文件中搜索字符串。
FIND [/V] [/C] [/N] [/I] [/OFF[LINE]] "string" path  

  /V         显示所有未包含指定字符串的行。  
  /C         仅显示包含字符串的行数。  
  /N         显示行号。  
  /I         搜索字符串时忽略大小写。    
  "string" 指定要搜索的文本字符串。  
  path 指定要搜索的文件。  
如果没有指定路径，FIND将搜索在提示符处键入的文本或者由另一命令产生的文本。

## FINDSTR
在文件中寻找字符串。
FINDSTR [/S] [/I] [/X] [/V] [/N]
        [/T:string] [/G:file] strings [[drive:][path]filename[ ...]]
  /S         在当前目录和所有子目录中搜索匹配文件。  
  /I         指定搜索不分大小写。  
  /X         打印完全匹配的行。  
  /V         只打印不包含匹配的行。  
  /N         在匹配的每行前打印行数。   
  /T         指定打印的字符串(可包含空格)
  strings    要查找的文字。  
  path 指定要查找的文件。  
除非参数有 /T 前缀，请使用空格隔开搜索字符串.

## COMP
比较两个文件的内容。

COMP [data1] [data2] [/D] [/A] [/L] [/N=number] [/C] [/OFF[LINE]] [/M]

  file1      指定要比较的第一个文件的位置和名称。  
  file2      指定要比较的第二批文件的位置和名称。  
  /L         显示不同的行数。  
  /A         以ASCII形式比较(默认为二进制比较)
  /N=number  以ASCII比较时只比较每个文件中由N指定的行数。  
  /C         比较文件时ASCII字母不区分大小写。  

## FC
比较两个文件并显示它们之间的不同
FC [/A] [/L] [/N] [/T] [/W] file1 file2  
  /D         以十进制形式显示不同处(默认为16进制)。  
  /C         以ASCII形式比较时不分大小写。  
  /A         将文件作为ASCII文字比较。    
  /L         当以ASCII比较时显示不同的行数。  
  /T         将制表符转换为空格。  
  /W         为了比较而压缩空白(连续的制表符和连续的空格)。  
  /N=number  以ASCII比较时只比较每个文件中由N指定的行数。
  file1  指定要比较的第一个文件。  
  file2  指定要比较的第二个文件。  

## EXIT
exit /?
退出 CMD.EXE 程序(命令解释器)或当前批处理脚本。

EXIT [/B] [exitCode]

  /B          指定要退出当前批处理脚本而不是 CMD.EXE。如果从一个
              批处理脚本外执行，则会退出 CMD.EXE  

  exitCode    指定一个数字号码。如果指定了 /B，将 ERRORLEVEL
              设成那个数字。如果退出 CMD.EXE，则用那个数字设置
              过程退出代码。  

## HELP
提供 Windows 命令的帮助信息。  
HELP [command]  
    command - 显示该命令的帮助信息。  

## MORE
逐屏显示输出。
MORE [/=] [/N=n] filename
filename   指定要逐屏显示的文件。
/N=n   从第n行开始显示第一个文件
/=   显示行号
内置选项
space: 继续输出
[1~9]: 指定输出行数
q: 退出