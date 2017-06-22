#include "gdt.h"
#include "pmm.h"
#include "vmm.h"
#include "string.h"

// 全局描述符表长度
#define GDT_LENGTH 5

// 全局描述符表定义
gdt_entry_t gdt_entries[GDT_LENGTH];

// GDTR
gdt_ptr_t gdt_ptr;


// 全局描述符表构造函数，根据下标构造
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

void init_gdt()
{
	gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries;

	// Flat Mode
	gdt_set_gate(SEG_NULL,  0x0, 0x0, 0x0, 0x0); 	
	gdt_set_gate(SEG_KTEXT, 0x0, 0xFFFFFFFF, 0x9A, 0xCF); 	
	gdt_set_gate(SEG_KDATA, 0x0, 0xFFFFFFFF, 0x92, 0xCF); 	
	gdt_set_gate(SEG_UTEXT, 0x0, 0xFFFFFFFF, 0xFA, 0xCF); 	
	gdt_set_gate(SEG_UDATA, 0x0, 0xFFFFFFFF, 0xF2, 0xCF); 

	gdt_flush((uint32_t)&gdt_ptr);
}

// 全局描述符表构造函数，根据下标构造
// 参数分别是 数组下标、基地址、限长、访问标志，其它访问标志
/* 结构体定义如下：
typedef struct
{
	uint16_t limit_low;     // 段界限   15～0
	uint16_t base_low;      // 段基地址 15～0
	uint8_t  base_middle;   // 段基地址 23～16
	uint8_t  access;        // 段存在位、描述符特权级、描述符类型、描述符子类别 15～8
	uint8_t  granularity; 	// 其他标志、段界限 23～16
	uint8_t  base_high;     // 段基地址 31～24
} __attribute__((packed)) gdt_entry_t;
*/
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt_entries[num].base_low     = (base & 0xFFFF);
	gdt_entries[num].base_middle  = (base >> 16) & 0xFF;
	gdt_entries[num].base_high    = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low    = (limit & 0xFFFF);
	gdt_entries[num].granularity  = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access       = access;
}
