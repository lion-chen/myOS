;this function has not be verfied
move_memory:
	push bp
	mov bp, sp
	push cx
	push di
	push si
		mov si, [bp+4]
		mov di,	[bp+6]
		mov cx, [bp+8]
		rep movsw
	pop si
	pop di
	pop cx
	leave
	ret

