;boot kernel

%include "general.info"

org MBR_LOAD_ADDR

section .text
jmp start
%include "disk.fun"
start:
    push 0							;driver number
    push 1							;number of sector to read
    push BOOT_LOAD_ADDR 			;bx-es:bx
    push 0							;es-es:bx
    push 0       					;head
    push 2        					;sector
    push 0        					;cylinder
	call read_sector
    jc end
    jmp BOOT_LOAD_ADDR

end:
    jmp  $						;infinite loop

	times 510-($-$$) db 0
	dw 0xaa55