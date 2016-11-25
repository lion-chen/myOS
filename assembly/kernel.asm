;kernel of myOS

%include "general.info"

org KERNEL_LOAD_ADDR


section .text
jmp start
%include "disk.fun"
%include "io.fun"
start:
    push 0							;driver number
    push SHELL_SECTOR_NUMBER		;number of sector to read
    push SHELL_LOAD_ADDR 			;bx-es:bx
    push 0							;es-es:bx
	push 0       					;head
	push 4        					;sector
	push 0        					;cylinder
	call read_sector
    jc end
    jmp SHELL_LOAD_ADDR

end:
    jmp  $						    ;infinite loop
	
	times 512-($-$$) db 0
	