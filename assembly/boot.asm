;boot kernel

%include "general.info"

org BOOT_LOAD_ADDR

section .data
BootInfo db "myOS is booting, please wait..."


section .text
jmp start
%include "disk.fun"
%include "io.fun"
start:
	push BootInfo
	call printsln
    push 0							;driver number
    push 1							;number of sector to read
    push KERNEL_LOAD_ADDR 			;bx-es:bx
    push 0							;es-es:bx
	push 0       					;head
	push 3        					;sector
	push 1        					;cylinder
	call read_sector
    jc end
    jmp KERNEL_LOAD_ADDR

end:
    jmp  $						    ;infinite loop
