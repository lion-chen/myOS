;kernel of myOS

%include "general.info"

org SHELL_LOAD_ADDR

section .bss
UserInput resb 512
ReadData resb 512
Head resb 2
Sector resb 2
Cylinder resb 2


section .data
WelcomeInfo db "Welcome to myOS! This is shell", 0
ErrorInfo db "invalid command", 0
MkfName db "mkf", 0
OpenName db "open", 0
EchoName db "echo", 0
ClearScreenName db "clear", 0
Escape db 0x1b, 0
HeadInfo db "Please specify the head number: ", 0
CylinderInfo db "Please specify the cylinder number: ", 0
SectorInfo db "Please specify the sector number: ", 0
times 512*SHELL_SECTOR_NUMBER-($-$$) db 0


section .text
jmp shell_start
%include "io.fun"
%include "string.fun"
%include "disk.fun"
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
    je mkf
    push 0							;es
    push OpenName					;di
    push 0							;ds
    push UserInput					;si
    call compare
    cmp ax, 1
    je open
    push 0							;es
    push EchoName					;di
    push 0							;ds
    push UserInput					;si
    call compare
    cmp ax, 1
    je echo
	push 0							;es
    push ClearScreenName			;di
    push 0							;ds
    push UserInput					;si
    call compare
    cmp ax, 1
    je clearscreen
	jmp error

error:
    push 0
    push ErrorInfo
    call printsln
    jmp shell_loop

shell_end:
	jmp $
	
	%include "command.asm"