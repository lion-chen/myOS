#include "debug.h"
#include "pmm.h"
#include "vmm.h"
#include "heap.h"

static void alloc_chunk(uint32_t offset, uint32_t pnum);

static uint32_t heap_max = HEAP_START;

//heap manager
static uint32_t heap_table[1024];

void init_heap()
{	
	int i;
	for(i=0;i<1024;i++)
		heap_table[i]=0;
}

void *kmalloc(uint32_t len)
{
	return (void *)(HEAP_START+kmalloc_i(len)*PAGE_SIZE);
}

int kmalloc_i(uint32_t len)
{
	//align
	int i,j,n=0,pnum=len/0x1000;
	if(len%0x1000!=0)
		pnum++;
	for(i=0; i<1024; i++){
		if(heap_table[i]!=0)
			continue;
		while(heap_table[i+n]==0){
			n++;
			if(n>=pnum)
				break;
		}
		if(n<pnum){
			i+=n;
			continue;
		}
		for(j=i;j<i+n;j++)
			heap_table[j] = n;
		alloc_chunk(i, pnum);
		return i;
	}
	return 0;
}

void kfree(int address)
{	
	int start = (address - HEAP_START) / PAGE_SIZE;
	int i, n = heap_table[start];
	for(i=0;i<n;i++){
		heap_table[i] = 0;
	}
}

void alloc_chunk(uint32_t offset, uint32_t pnum)
{
	// start = start page address
	offset = offset * PAGE_SIZE;
	uint32_t start = offset + HEAP_START;
	uint32_t len = pnum * PAGE_SIZE;
	while (start + len > heap_max) {
		uint32_t page = pmm_alloc_page();
		map(pgd_kern, heap_max, page, PAGE_PRESENT | PAGE_WRITE);
		heap_max += PAGE_SIZE;
	}
}

void test_heap()
{
	printk_color(rc_black, rc_magenta, "Test kmalloc() && kfree() now ...\n\n");

	int addr1 = kmalloc(50);
	printk("kmalloc    50 byte in 0x%X\n", addr1);
	int addr2 = kmalloc(500);
	printk("kmalloc   500 byte in 0x%X\n", addr2);
	int addr3 = kmalloc(5000);
	printk("kmalloc  5000 byte in 0x%X\n", addr3);
	int addr4 = kmalloc(50000);
	printk("kmalloc 50000 byte in 0x%X\n\n", addr4);

	printk("free mem in 0x%X\n", addr1);
	kfree(addr1);
	printk("free mem in 0x%X\n", addr2);
	kfree(addr2);
	printk("free mem in 0x%X\n", addr3);
	kfree(addr3);
	printk("free mem in 0x%X\n\n", addr4);
	kfree(addr4);
}

