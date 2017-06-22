#ifndef INCLUDE_DEBUG_H_
#define INCLUDE_DEBUG_H_

#include "console.h"
#include "vargs.h"
#include "elf.h"

#define assert(x, info)                                       	\
	do {                                                	\
		if (!(x)) {                                     \
			panic(info);     			\
		}                                               \
	} while (0)


#define static_assert(x)                                	\
	switch (x) { case 0: case (x): ; }

void init_debug();

void panic(const char *msg);

void print_cur_status();

void printk(const char *format, ...);

void printk_color(real_color_t back, real_color_t fore, const char *format, ...);

#endif 	// INCLUDE_DEBUG_H_
