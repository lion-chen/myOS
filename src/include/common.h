#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "types.h"

void outb(uint16_t port, uint8_t value);

uint8_t inb(uint16_t port);

uint16_t inw(uint16_t port);

void insl(uint32_t buf, uint16_t port, uint32_t count);

void outsl(uint32_t buf, uint16_t port, uint32_t count);

void enable_intr();

void disable_intr();

#endif // INCLUDE_COMMON_H_
