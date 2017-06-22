#include "timer.h"
#include "debug.h"
#include "common.h"
#include "idt.h"
#include "sched.h"

void timer_callback(pt_regs *regs)
{
	schedule();
}

void init_timer(uint32_t frequency)
{
	register_interrupt_handler(IRQ0, timer_callback);
	//input frequency is 1193180, argument frequency means how many times interruption occus per second
	uint32_t divisor = 1193180 / frequency;
	//0x36 represents third mode of 8253/8254 chip
	outb(0x43, 0x36);

	uint8_t low = (uint8_t)(divisor & 0xFF);
	uint8_t hign = (uint8_t)((divisor >> 8) & 0xFF);

	outb(0x40, low);
	outb(0x40, hign);
}
