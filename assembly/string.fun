compare:
	push bp
	mov bp, sp
	push si
	push ds
	push cx
	push es
	push di
		push word [bp+0x6]
		push word [bp+0x4]
		call strlen
		mov cx, ax
		add cx, 0x1
		mov si, [bp+0x4]
		mov ax, [bp+0x6]
		mov ds, ax
		mov di, [bp+0x8]
		mov ax, [bp+0xa]
		mov es, ax
		repe cmpsb
		jcxz equals
		mov ax, 0
		jmp compare_over
		equals:
			mov ax, 1
			jmp compare_over
		compare_over:
	pop di
	pop es
	pop cx
	pop ds
	pop si
	leave
	ret
	
strlen:
	push bp
	mov bp, sp
	push si
	push ds
	push cx
		mov si, [bp+4]
		mov ax, [bp+6]
		mov ds, ax
		mov cx, 0
		strlen_loop:
		add cx, 1
		lodsb
		cmp al, 0
		jne strlen_loop
		sub cx, 1
		mov ax, cx
	pop cx
	pop ds
	pop si
	leave
	ret