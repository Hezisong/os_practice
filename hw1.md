分析和实验funcall.c，需要完成的内容包括：-[X]
修改代码，可正常显示小组两位同学的学号（用字符串）
ret = write(1, "2013011296",11);
生成funcall.c的汇编码，理解其实现并给汇编码写注释 尝试用xem的简单调试功能单步调试代码
./xem -g funcall
h: print help commands.
q: quit. c: continue.
s: single step for one instruction.
i: display registers.
x: display memory, the input address is hex number
回答如下问题： funcall中的堆栈有多大？是内核态堆栈还是用户态堆栈
MEM_SZ-FS_SZ-(Size of the file)=124MB-184B 是内核态堆栈 user: 0 [user mode or not]
funcall中的全局变量ret放在内存中何处？如何对它寻址？
SG 0x0 (D 0), ret在内存0xb8处 相对pc寻址
funcall中的字符串放在内存中何处？如何对它寻址？
LEAG 0x0 (D 0), s在内存0xa0处 相对于sp寻址
局部变量i在内存中的何处？如何对它寻址？
通过LL 0x4 (D 4)和SL 0x4 (D 4)读写变量i 相对于sp寻址
当前系统是处于中断使能状态吗？
no iena:0[interrupt flag]
funcall中的函数参数是如何传递的？函数返回值是如何传递的？
使用堆栈传递，从右往左压入 通过寄存器a传递
分析并说明funcall执行文件的格式和内容 　
hdr数据 程序指令text 程序数据data　
 
分析和实验os0.c，需要完成的内容包括： -[X]
生成os0.c的汇编码，理解其实现并给汇编码写注释 尝试用xem的简单调试功能单步调试代码
回答如下问题：
何处设置的中断使能？ STI (set trap, and process the interrupt)
系统何时处于中断屏蔽状态？STI之前，以及进入alltrap到从中退出的过程中
如果系统处于中断屏蔽状态，如何让其中断使能？STI
系统产生中断后，CPU会做哪些事情？ 保存中断的地址到kkernel mode的sp中，pc会跳到中断向量的地址ivec处执行
CPU执行RTI指令的具体完成工作是哪些？ return from interrupt, set pc, sp, may switch user/kernel mode; if has pending interrupt, process the interrupt