HEADERDIR = ./headers
LINKERDIR = ./linker
BOOTDIR = ./bootloader
SRCDIR = ./src
BINDIR = ./bin
CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
GCCFLAGS = -Wall -o2 -ffreestanding -nostdinc -nostdlib -nostartfiles 
GCCPATH = /home/niko/Documenten/'Hr - Technisch Informatica'/VIRTUALMIRROR/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin

all: clean kernel8.img

boot.o: $(BOOTDIR)/boot.s
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c $(BOOTDIR)/boot.s -o $(BINDIR)/boot.o

kernel.o: kernel.c 
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -I$(HEADERDIR) -c kernel.c -o $(BINDIR)/kernel.o


kernel8.img: boot.o $(OFILES)
	@echo hellow


clean:
	@echo Dit werkt