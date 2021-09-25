
GCCPARAMS = -m32 -nostdlib -nodefaultlibs -lgcc -fno-builtin -fno-exceptions -fno-leading-underscore -ffreestanding
ASPARAMS = --32
LDPARAMS = -melf_i386
OUTDIR   = obj/
BINDIR   = bin/


objects = $(OUTDIR)loader.o  \
	  $(OUTDIR)gdt.o     \
	  $(OUTDIR)stdio.o   \
	  $(OUTDIR)string.o     \
 	  $(OUTDIR)cpu.o     \
	  $(OUTDIR)kernel.o 

prepare:
	mkdir $(OUTDIR)
	mkdir $(BINDIR)

%.o: %.c		
	gcc $(GCCPARAMS) -c -o $@ $<
	cp *.o $(OUTDIR)
	rm -f *.o

%.o: %.s
	as $(ASPARAMS) -o $@ $<
	cp *.o $(OUTDIR)
	rm -f *.o


kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $(BINDIR)$@ $(objects)

install: kernel.bin
	sudo cp $(BINDIR)$< /boot/kernel.bin

kernel.iso: $(BINDIR)kernel.bin
	rm -rf iso
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "GUGUOS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
	echo '  boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso
	
run: kernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm "GUGUOS" &	


clean:
	rm -Rf $(OUTDIR)
	rm -Rf $(BINDIR)
	rm -f *.o
	rm -f *.bin
	rm -f *.iso

all:
	make clean
	make prepare
	make gdt.o
	make stdio.o
	make string.o
	make cpu.o
	make kernel.o
	make loader.o
	make kernel.bin
	make install
	make kernel.iso
