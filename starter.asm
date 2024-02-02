bits    16          ; 16-bit mode
extern  kernel_main ; entry code for our kernel in C
extern  interrupt_handler
extern  scheduler
extern  run_next_process
extern  page_directory

global  load_page_directory
global  enable_paging

global  dev_write
global  dev_write_word
global  dev_read

start:
    mov     ax, cs
    mov     ds, ax

    call    load_gdt
    call    init_video_mode
    call    enter_protected_mode
    call    setup_interrupts
    call    load_task_register

    call    08h:start_kernel

load_gdt:
    cli
    lgdt    [gdtr - start]

    ret

setup_interrupts:
    call    remap_pic
    call    load_idt
    
    ret

init_video_mode:
    mov     ah, 0h
    mov     al, 03h ; text mode with 16 colors
    int     10h

    mov     ah, 01h
    mov     cx, 2000h
    int     10h

    ret

enter_protected_mode:
    mov     eax, cr0 ; 32-bit register Control Register 0 
    or      eax, 1   ; bitwise OR to set the first bit to 1 (protected mode)
    mov     cr0, eax

    ret

remap_pic:
    mov     al, 11h ; this instructions take register ax only as second operand

    send_init_cmd_to_pic_master:
        out     0x20, al
    send_init_cmd_to_pic_slave:
        out     0xA0, al

    make_irq_starts_from_intr_32_in_pic_master:
        mov     al, 32d
        out     0x21, al

    make_irq_starts_from_intr_40_in_pic_slave:
        mov     al, 40d
        out     0xA1, al

    tell_pic_master_where_pic_slave_is_connected:
        mov     al, 04h
        out     0x21, al

    tell_pic_slave_where_pic_master_is_connected:
        mov     al, 02h
        out     0xA1, al

    mov     al, 01h

    tell_pic_master_the_arch_is_x86:
        out     0x21, al
    
    tell_pic_slave_the_arch_is_x86:
        out     0xA1, al

    mov     al, 0h

    make_pic_master_enables_all_irqs:
        out     0x21, al
        
    make_pic_slave_enables_all_irqs:
        out     0xA1, al

    ret

load_idt:
    lidt    [idtr - start]
    ret     

load_task_register:
    mov     ax, 40d ; index of TSS Descriptor in GDT
    ltr     ax      ;  load task register, ltr takes one operand which is the selector for a TSS

    ret

bits    32

load_page_directory:
    mov     eax, [page_directory]
    mov     cr3, eax

    ret

enable_paging:
    mov     eax, cr0
    or      eax, 80000000h
    mov     cr0, eax

    ret

dev_write:
    push    edx 
    push    eax 
    
    ; clearing the previous values for the register by setting them to 0
    xor     edx, edx
    xor     eax, eax

    mov     dx, [esp + 12] ; port
    mov     al, [esp + 16] ; command

    out     dx, al

    pop     eax
    pop     edx

    ret

dev_write_word:
    push    edx
    push    eax

    xor     edx, edx
    xor     eax, eax

    mov     dx, [esp + 12]
    mov     ax, [esp + 16]

    out     dx, ax

    pop     eax
    pop     edx

    ret

dev_read:
    push    edx

    xor     edx, edx
    xor     eax, eax

    mov     dx, [esp + 8]

    in      ax, dx
    
    pop     edx

    ret

start_kernel:
    mov     eax, 10h
    mov     ds, eax
    mov     ss, eax

    mov     eax, 0h
    mov     es, eax
    mov     fs, eax
    mov     gs, eax

   ; sti

    call kernel_main

%include    "gdt.asm"
%include    "idt.asm"

tss:
    dd      0
