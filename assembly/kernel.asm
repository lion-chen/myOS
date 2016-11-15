;kernel of myOS

%include "general.info"

org KERNEL_LOAD_ADDR

section .bss
UserInput resb 64
ReadData resb 510


section .data
WelcomeInfo db "Welcome to myOS! This is shell",0
ErrorInfo db "invalid command", 0
MkfName db "mkf",0
OpenName db "open",0


section .text
jmp shell_start
%include "io.fun"
%include "disk.fun"
%include "string.fun"
shell_start:
	call clear_screen
	push 0
	push WelcomeInfo
	call printsln

shell_loop:
	push '>'
	call printc
	push 0
	push UserInput
	call scan
	call newline
	push 0							;es
    push MkfName					;di
    push 0							;ds
    push UserInput					;si
    call compare
    cmp ax, 1
    je makefile
    push 0							;es
    push OpenName					;di
    push 0							;ds
    push UserInput					;si
    call compare
    cmp ax, 1
    je openfile
	jmp error

makefile:
    push 0
    push UserInput
    call scan
    call newline
    push 0x80						;driver number
    push 1							;number of sector to read
    push UserInput       			;bx-es:bx
    push 0							;es-es:bx
    push 0       					;head
    push 1                          ;sector
    push 2        					;cylinder
    call write_sector
    jmp shell_loop

openfile:
    push 0x80						;driver number
    push 1							;number of sector to read
    push ReadData       			;bx-es:bx
    push 0							;es-es:bx
    push 0       					;head
    push 1        					;sector
    push 2        					;cylinder
    call read_sector
    push 0
    push ReadData
    call printsln
    jmp shell_loop

error:
    push 0
    push ErrorInfo
    call printsln
    jmp shell_loop

shell_end:
	jmp $