MEMORY
    {
        FLASH_IRQ (rx) : ORIGIN = 0, LENGTH = 192
        FLASH_CONFIG (r) : ORIGIN = 0x400, LENGTH = 32
        FLASH_PROGRAM (rx) : ORIGIN = 0x1000, LENGTH = 258047
        RAML (!rx) : ORIGIN = 0x1fffe000, LENGTH = 8K
        RAMH (wx) : ORIGIN = 0x20000000, LENGTH = 24K
    }

SECTIONS
    {
        .flash_config : {
            *(.flash_config)
        } > FLASH_CONFIG

        _stackstart = ORIGIN(RAMH);

        .flashtext : {
            *(.flashtext)
        } > FLASH_PROGRAM
        .rodata : {
            *(.rodata)
        } > FLASH_PROGRAM

        .irq ORIGIN(RAMH) : {
            *(.irq)
        } > RAMH AT> FLASH_IRQ
        .text : {
            *(.text)
        } > RAMH AT> FLASH_PROGRAM
        .data : {
            *(.data)
        } > RAMH AT> FLASH_PROGRAM

        _irqstart = ADDR(.irq);
        _irqend = ADDR(.irq) + SIZEOF(.irq);
        _irqload = LOADADDR(.irq);
        _copystart = ADDR(.text);
        _copyend = ADDR(.data) + SIZEOF(.data);
        _copyload = LOADADDR(.text);

        .bss : {
            _bstart = . ;
            *(.bss) *(COMMON)
            _bend = . ;
        } > RAMH
    }

ENTRY(_start)
