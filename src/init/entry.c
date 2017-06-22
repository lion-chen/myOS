#include "common.h"
#include "console.h"
#include "string.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "keyboard.h"
#include "pmm.h"
#include "vmm.h"
#include "heap.h"
#include "task.h"
#include "sched.h"
#include "disk.h"

void kern_init();

multiboot_t *glb_mboot_ptr;

char kern_stack[STACK_SIZE]  __attribute__ ((aligned(16)));

uint32_t kern_stack_top;

__attribute__((section(".init.data"))) pgd_t *pgd_tmp  = (pgd_t *)0x1000;
__attribute__((section(".init.data"))) pgd_t *pte_low  = (pgd_t *)0x2000;
__attribute__((section(".init.data"))) pgd_t *pte_hign = (pgd_t *)0x3000;

__attribute__((section(".init.text"))) void kern_entry()
{
	pgd_tmp[0] = (uint32_t)pte_low | PAGE_PRESENT | PAGE_WRITE;
	pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t)pte_hign | PAGE_PRESENT | PAGE_WRITE;

	// logical 4M to physical 4M
	int i;
	for (i = 0; i < 1024; i++) {
		pte_low[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
	}

	// logical 0xC0000000-0xC0400000 to physical 0x00000000-0x00400000
	for (i = 0; i < 1024; i++) {
		pte_hign[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
	}
	
	asm volatile ("mov %0, %%cr3" : : "r" (pgd_tmp));

	uint32_t cr0;

	// set page enable bit of cr0 to 1
	asm volatile ("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000001;
	asm volatile ("mov %0, %%cr0" : : "r" (cr0));
	
	// change kernel stack
	kern_stack_top = ((uint32_t)kern_stack + STACK_SIZE);
	asm volatile ("mov %0, %%esp\n\t"
			"xor %%ebp, %%ebp" : : "r" (kern_stack_top));

	// update multiboot pointer
	glb_mboot_ptr = mboot_ptr_tmp + PAGE_OFFSET;

	kern_init();
}

int shell(void *arg)
{
	real_color_t tcolor = rc_white;
	uint32_t lba = 10;
	uint8_t buff[512];
	while (1) {
		console_write_color("\n>", rc_black, tcolor);
		char* command = get_chars(tcolor);
		if(!strcmp(command, "ctc")){
			console_write_color("type color: ", rc_black, tcolor);
			command = get_chars(tcolor);
			if(!strcmp(command, "green")){
				tcolor = rc_green;
			}
			else if(!strcmp(command, "white")){
				tcolor = rc_white;
			}
		}
		else{
			console_write_color("command not found", rc_black, tcolor);
		}
	}

	return 0;
}

void kern_init()
{
	init_debug();
	init_gdt();
	init_idt();

	console_clear();
	printk_color(rc_black, rc_green, "Hello, OS kernel!\n\n");

	init_timer(200);
	init_keyboard();
	init_disk();

	//8 bits hex number
	printk("kernel in memory start: 0x%08X\n", kern_start);
	printk("kernel in memory end:   0x%08X\n", kern_end);
	printk("kernel in memory used:   %d KB\n\n", (kern_end - kern_start) / 1024);

	show_memory_map();
	
	init_pmm();
	init_vmm();
	init_heap();

	printk_color(rc_black, rc_red, "\nThe Count of Physical Memory Page is: %u\n\n", phy_page_count);

	init_sched();

	kernel_thread(shell, NULL);

	enable_intr();

	while (1) {
		asm volatile ("hlt");
	}
}

