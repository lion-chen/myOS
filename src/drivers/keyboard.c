#include "keyboard.h"
#include "debug.h"
#include "common.h"
#include "idt.h"
#include "sched.h"
#include "console.h"

static char buff[1024];
static int len = 0;
static int INPUT = 1;
static real_color_t tcolor;

char* get_chars(real_color_t tc){
	tcolor = tc;
	while(1){
		if(INPUT == 1)
			continue;
		else{
			INPUT = 1;
			return buff;		
		}	
	}
}

void keyboard_handler(pt_regs *regs)
{
	/*uint8_t keymap[58]={0,0,'1','2','3','4','5','6','7','8','9','0','-','=',	0,0,'q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s','d',
'f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n',
'm',',','.','/',0,'*',0,'\t'};*/
uint8_t keymap[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
	unsigned char status;
	uint8_t keycode;

	/* write EOI(end of interrupt) */
	outb(0x20, 0x20);
	INPUT = 1;
	status = inb(0x64);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = inb(0x60);
		if(keycode < 0 || keycode > 0x80)
			return;
		if(keycode == 0x1c) {
			len = 0;
			INPUT = 0;
			console_putc_color('\n', rc_black, tcolor);
			return;
		}
		console_putc_color(keymap[keycode],rc_black, tcolor);
		buff[len++] = keymap[keycode];
		buff[len] = '\0';
	}
}

void init_keyboard()
{
	// register handler
	register_interrupt_handler(IRQ1, keyboard_handler);
}
