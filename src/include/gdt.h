#ifndef INCLUDE_GDT_H_
#define INCLUDE_GDT_H_

#include "types.h"

// 各个内存段所在全局描述符表下标
#define SEG_NULL    0
#define SEG_KTEXT   1
#define SEG_KDATA   2
#define SEG_UTEXT   3
#define SEG_UDATA   4
#define SEG_TSS     5

#define GD_KTEXT    ((SEG_KTEXT) << 3)      // 内核代码段
#define GD_KDATA    ((SEG_KDATA) << 3)      // 内核数据段
#define GD_UTEXT    ((SEG_UTEXT) << 3)      // 用户代码段
#define GD_UDATA    ((SEG_UDATA) << 3)      // 用户数据段
#define GD_TSS      ((SEG_TSS) << 3)        // 任务段

// 段描述符 DPL
#define DPL_KERNEL  (0)
#define DPL_USER    (3)

// 各个段的全局描述符表的选择子
#define KERNEL_CS   ((GD_KTEXT) | DPL_KERNEL)
#define KERNEL_DS   ((GD_KDATA) | DPL_KERNEL)
#define USER_CS     ((GD_UTEXT) | DPL_USER)
#define USER_DS     ((GD_UDATA) | DPL_USER)

// 全局描述符类型
typedef struct gdt_entry_t {
	uint16_t limit_low;     
	uint16_t base_low;      
	uint8_t  base_middle;  
	uint8_t  access; 
	uint8_t  granularity; 	
	uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;

// GDTR
typedef struct gdt_ptr_t {
	uint16_t limit; 	
	uint32_t base; 		
} __attribute__((packed)) gdt_ptr_t;

// 初始化全局描述符表
void init_gdt();

// GDT 加载到 GDTR 的函数
extern void gdt_flush();

#endif 	// INCLUDE_GDT_H_
