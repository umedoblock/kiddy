TARGET         = lcd_kiddy
OBJ            = lcd_kiddy.o hd44780.o
MCU_TARGET     = atmega88
MCU_TARGET     = atmega168a
OPTIMIZE       = -O2

DEFS           =
LIBS           =

# You should not have to change anything below here.

CC             = avr-gcc

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS       = -Wl,-Map,$(TARGET).map

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump
SIZE           = avr-size

#all: $(TARGET).elf lst text eeprom
all: $(TARGET).elf lst text size

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o $(TARGET).elf *.eps *.png *.pdf *.bak
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

# m164p    = ATmega164P         [/etc/avrdude.conf:4295]
# m168     = ATmega168          [/etc/avrdude.conf:8091]
# m168p    = ATmega168P         [/etc/avrdude.conf:8280]
# m168pb   = ATmega168PB        [/etc/avrdude.conf:8292]

write:
	avrdude -c avrispmkII -p m168p -P usb -U flash:w:./$(TARGET).hex -F -vv
#	avrdude -c avrispmkII -p m168p -P /dev/ttyUSB0 -b 2400 -U flash:w:./${TARGET).hex -F -vv
#	avrdude -c avrispmkII -p m88 -P usb -U flash:w:./$(TARGET).hex -F -vv

lst:  $(TARGET).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# .c.o:
# >--$(CC) $(OPTIMIZE) $(CFLAGS) -c $<
# lc7d_kiddy.o: 
hd44780.o: hd44780.h
# Display size of file.^M

size:
	@echo
	$(SIZE) -C --mcu=$(MCU_TARGET) $(TARGET).elf

# Rules for building the .text rom images

text: hex bin srec

hex:  $(TARGET).hex
bin:  $(TARGET).bin
srec: $(TARGET).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

eeprom: ehex ebin esrec

ehex:  $(TARGET)_eeprom.hex
ebin:  $(TARGET)_eeprom.bin
esrec: $(TARGET)_eeprom.srec

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

%_eeprom.srec: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@

%_eeprom.bin: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@

# Every thing below here is used by avr-libc's build system and can be ignored
# by the casual user.

JPEGFILES               = lcd_kiddy-setup.jpg

JPEG2PNM                = jpegtopnm
PNM2EPS                 = pnmtops
JPEGRESOLUTION          = 180
EXTRA_CLEAN_FILES       = *.hex *.bin *.srec *.eps

dox: ${JPEGFILES:.jpg=.eps}

%.eps: %.jpg
	$(JPEG2PNM) $< |\
	$(PNM2EPS) -noturn -dpi $(JPEGRESOLUTION) -equalpixels \
	> $@
