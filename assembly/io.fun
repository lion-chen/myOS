clear_screen:
	push bp
	mov bp, sp 
		mov ah,	0x0
		mov al, 0x3
		int 0x10
	leave
	ret
	
newline:
	push bp
	mov bp, sp
		push 0xa
		call printc
		push 0xd
		call printc
	leave
	ret
	
printc:	
	push bp
	mov bp, sp		
	push ax
		mov ah, 0x0e
		mov al, [bp+0x4]
		int 0x10
	pop ax
	leave
	ret
	
prints:
	push bp
	mov bp, sp
	push si
	push ds
	push ax
		mov si, [bp+0x4]
		mov ax, [bp+0x6]
		mov ds, ax
		mov ah, 0x0e
		prints_loop:
		lodsb
		cmp al, 0
		je prints_loop_over
		int 0x10
		jmp prints_loop
		prints_loop_over:
	pop ax
	pop ds
	pop si
	leave
	ret
	
printsln:
	push bp
	mov bp, sp
		push word [bp+0x6]
		push word [bp+0x4]
		call prints
		call newline
	leave
	ret

scan:
	push bp
	mov bp, sp
	push ax
	push di
	push es
		cld
		mov di, [bp+0x4]
		mov ax, [bp+0x6]
		mov es, ax
		scan_loop:
		mov ah, 0
		int 0x16
		push ax
		call printc
		cmp al, 0xd
		je scan_loop_over
		stosb
		jmp scan_loop
		scan_loop_over:
		mov al, 0
		stosb
	pop es
	pop di
	pop ax
	leave
	ret

readw:
	push bp
	mov bp, sp
	push ds
	push si
	    mov si, [bp+0x4]
	    mov ds, [bp+0x6]
		lodsw
	pop si
	pop ds
	leave
	ret