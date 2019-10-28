.thumb
.global _start

.thumb_func
.section ".flashtext", "ax"
_start:
    ldr r0, =_stackstart
    mov sp, r0
    bl init_sections
    bl main
endloop:
    b endloop
