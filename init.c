extern char _bstart, _bend, _copystart, _copyload, _copyend, _irqstart, _irqload, _irqend;

void __attribute__((section(".flashtext"))) init_sections() {
    char* i;
    char* copyptr;
    // fill .bss with 0
    for(i = &_bstart; i < &_bend; i++)
        *i = 0;
    // copy data from flash to RAM
    copyptr = &_irqload;
    for(i = &_irqstart; i < &_irqend; i++)
        *i = *copyptr++;
    copyptr = &_copyload;
    for(i = &_copystart; i < &_copyend; i++)
        *i = *copyptr++;
}
