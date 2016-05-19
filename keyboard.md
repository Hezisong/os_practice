
初始化
cons_init-->kbd_init-->kbd_intr
当我们初始化之后，我们就可以响应中断，来处理键盘的输入。

中断处理
trap_dispatch()
case IRQ_OFFSET + IRQ_KBD
cons_getc()-->kbd_intr()-->cons_intr()

时间开销：主要在中断处理中
