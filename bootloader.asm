start:
    mov     ax, 07C0h
    mov     ds, ax

    mov     si, title_string
    call    print_string

    mov     si, message_string
    call    print_string

    call    load_kernel_from_disk
    jmp     0900h:0000
    
load_kernel_from_disk:
    mov     ax, [curr_sector_to_load]
    sub     ax, 2
    mov     bx, 512d
    mul     bx
    mov     bx, ax

    mov     ax, 0900h
    mov     es, ax  ; should contain buffer segment

    mov     ah, 02h ; 02h is a service number that reads sectors from hard disk and loads it into memory
    mov     al, 1h ; this value is the number of sectors we want to read
    mov     ch, 0h  ; the number of the track we want to read from
    mov     cl, [curr_sector_to_load] ; the sector number we would like to read
    mov     dh, 0h  ; the head number
    mov     dl, 80h ; we are reading from hard disk #0
    int     13h 

    jc      load_kernel_error

    sub     byte [number_of_sectors_to_load], 1
    add     byte [curr_sector_to_load], 1
    cmp     byte [number_of_sectors_to_load], 0

    jne     load_kernel_from_disk

    ret

load_kernel_error:
    mov     si, load_error_string
    call    print_string

    jmp $ ; infinite loop

print_string:
    mov     ah, 0Eh

print_char:
    lodsb ; this instruction is used to load a byte from the memory addressed by the DS:SI into AL and increases the value by 1
    
    cmp     al, 0
    je      printing_finished
    
    int     10h

    jmp     print_char

printing_finished:
    mov     al, 10d ; print new line
    int     10h

    ; reading current cursor position
    mov     ah, 03h
    mov     bh, 0
    int     10h

    ; move cursor to the beginning
    mov     ah, 02h
    mov     dl, 0
    int     10h

    ret

title_string        		db  "The Bootloader of OKernel.", 0
message_string      		db  "The kernel is loading...", 0
load_error_string   		db  "The kernel cannot be loaded", 0
number_of_sectors_to_load 	db 	15d ; 255 sectors = 127.5KB
curr_sector_to_load 		db 	2d
    
times 510-($-$$) db 0 ; pdding to read 510 bytes

dw 0xAA55   ; magic number
