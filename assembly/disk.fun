read_sector:
	push bp
	mov bp, sp
	push ax
	push cx
	push bx
		mov ch, [bp+4]        		;ch-cylinder
    	mov cl, [bp+6]        		;cl-sector
    	mov dh, [bp+8]        		;dh-head
    	mov es, [bp+0xa]			;es:bx-data buffer
    	mov bx, [bp+0xc]			;es:bx-data buffer
    	mov ah, 0x2      			;ah-function
    	mov al, [bp+0xe]        	;al-number of sector to read
    	mov dl, [bp+0x10]         	;dl-driver number
    	int 0x13          			;int 13h-interrupt to read disk
	pop bx
	pop cx
	pop ax
	leave
	ret
	
write_sector:
	push bp
	mov bp, sp
	push ax
	push cx
	push bx
		mov ch, [bp+4]        		;ch-cylinder
    	mov cl, [bp+6]        		;cl-sector
    	mov dh, [bp+8]        		;dh-head
    	mov es, [bp+0xa]			;es:bx-data buffer
    	mov bx, [bp+0xc]			;es:bx-data buffer
    	mov ah, 0x3      			;ah-function
    	mov al, [bp+0xe]        	;al-number of sector to write
    	mov dl, [bp+0x10]         	;dl-driver number
    	int 0x13          			;int 13h-interrupt to write disk
	pop bx
	pop cx
	pop ax
	leave
	ret


