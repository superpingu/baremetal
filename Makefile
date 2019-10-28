TOOLPREFIX = arm-none-eabi-
CC = $(TOOLPREFIX)gcc
GDB = $(TOOLPREFIX)gdb
AS = $(TOOLPREFIX)as
OBJDUMP = $(TOOLPREFIX)objdump
OBJCOPY = $(TOOLPREFIX)objcopy
CFLAGS = -g -O2 -mcpu=cortex-m0plus -mthumb -std=gnu99 -Wall -Wextra -Werror
LDFLAGS = -T ld_ram.lds -nostdlib
ASFLAGS = -g -mcpu=cortex-m0plus
TARGET = main
CSRCS = $(TARGET).c init.c led.c uart.c matrix.c irq.c buttons.c pit.c clocks.c
# all the objects to link
OBJECTS =  $(subst .c,.o,$(CSRCS)) crt0.o image.o flash.o

.PHONY: all debug showsections showinfo showsymbols clean

all: $(TARGET)
$(TARGET): $(OBJECTS)
%.o: %.c %.d
	$(CC) -c -o $@ $< $(CFLAGS)
%.d : %.c
	$(CC) $(CFLAGS) -MM -MF $@ -MP $<
image.o: image.raw
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm $^ $@

debugserver:
	 JLinkGDBServer -if swd -device "MKL46Z256xxx4" -LocalhostOnly
debug:
	$(GDB) $(TARGET)

showsections: $(TARGET)
	$(OBJDUMP) -h $^
showinfo: $(TARGET)
	$(OBJDUMP) -f $^
showsymbols: $(TARGET)
	$(OBJDUMP) -t $^

clean:
	rm -f $(TARGET) $(OBJECTS) $(subst .c,.d,$(CSRCS))

-include $(subst .c,.d,$(CSRCS))
