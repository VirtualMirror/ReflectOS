GCC := aarch64-none-elf-gcc
LCC := aarch64-none-elf-ld
OCC := aarch64-none-elf-objcopy

HDIR := -I./headers
LDIR := ./linker
BDIR := ./bootloader
SRCDIR := ./src
BINDIR := ./bin
LFILES := $(LDIR)/link.ld

ifeq ($(OS), Windows_NT)
	CPATH := C:\Users\Ruben\Documents\ReflectOS\gcc-arm-10.3-2021.07-mingw-w64-i686-aarch64-none-elf\bin
	CFLAGS := -Wall -o2 -ffreestanding -nostdinc -nostdlib -nostartfiles
	LFLAGS := -nostdlib $(OFILES) -T $(LFILES)
	EXT := .exe
else
	CPATH := /home/niko/Documenten/'Hr - Technisch Informatica'/VIRTUALMIRROR/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin
	CFLAGS := -Wall -o2 -ffreestanding -nostdinc -nostdlib -nostartfiles
	LFLAGS := -nostdlib $(OFILES) -T $(LFILES)
	EXT := .o
endif

CFILES := $(SRCDIR)/kernel.c
SFILES := $(BDIR)/boot.s
OFILES := $(BINDIR)/boot$(EXT) $(BINDIR)/kernel$(EXT)

TARGET := clean boot kernel kernel8.img
EXTS := *.o* *.elf* *.img*


all: $(TARGET)


boot: $(SFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -c $(SFILES) -o $(BINDIR)/boot$(EXT)


kernel: $(CFILES)
	$(CPATH)/$(GCC) $(CFLAGS) $(HDIR) -c $(CFILES) -o $(BINDIR)/kernel$(EXT)


kernel8.img: 
	$(CPATH)/$(LCC) $(LFLAGS) -o $(BINDIR)/reflectos.elf
	$(CPATH)/$(OCC) -O binary $(BINDIR)/reflectos.elf reflectos.img


clean:
	@echo [info] cleaning
	rm -r $(BINDIR)
	mkdir $(BINDIR)
	@echo [ok] files removed
