section .text
makefile:
	push 0
	push HeadInfo
	call prints
	push 0
	push Head
	call scan
	call newline
	push 0
	push SectorInfo
	call prints
	push 0
	push Sector
	call scan
	call newline
	push 0
	push CylinderInfo
	call prints
	push 0
	push Cylinder
	call scan
	call newline
	
	push 0
	push Head
	call readw
	mov bx, ax
	push 0
	push Sector
	call readw
	mov cx, ax
	push 0
	push Cylinder
	call readw
	mov dx, ax
	
    push 0
    push UserInput
    call scan
    call newline
	
    push 0x80						;driver number
    push 1							;number of sector to read
    push UserInput       			;bx-es:bx
    push 0							;es-es:bx
	push bx
	push cx
	push dx
    call write_sector
    jmp shell_loop

openfile:
	push 0
	push HeadInfo
	call prints
	push 0
	push Head
	call scan
	call newline
	push 0
	push SectorInfo
	call prints
	push 0
	push Sector
	call scan
	call newline
	push 0
	push CylinderInfo
	call prints
	push 0
	push Cylinder
	call scan
	call newline
	
	push 0
	push Head
	call readw
	mov bx, ax
	push 0
	push Sector
	call readw
	mov cx, ax
	push 0
	push Cylinder
	call readw
	mov dx, ax
	
    push 0x80						;driver number
    push 1							;number of sector to read
    push ReadData       			;bx-es:bx
    push 0							;es-es:bx
	push bx
	push cx
	push dx
    call read_sector
    push 0
    push ReadData
    call printsln
    jmp shell_loop
	
	