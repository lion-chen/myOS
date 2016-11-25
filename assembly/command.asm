%include "file.asm"

mkf:
    jmp makefile

open:
    jmp openfile
	
echo:
	push 0
	push UserInput
	call scan
	call newline
	push 0							;es
    push Escape						;di
    push 0							;ds
    push UserInput					;si
    call compare
    cmp ax, 1
    je shell_loop
	push 0
	push UserInput
	call printsln
	jmp echo
	
clearscreen:
	call clear_screen
	jmp shell_loop