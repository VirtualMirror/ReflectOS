GCC := aarch64-none-elf-gcc
LCC := aarch64-none-elf-ld
OCC := aarch64-none-elf-objcopy

HDIR := ./headers
LDIR := ./linker
BDIR := ./bootloader
SRCDIR := ./src
BINDIR := ./bin

KERNELFILES := $(SRCDIR)/kernel.c
IOFILES := $(SRCDIR)/io.c
BUFFILES := $(SRCDIR)/buffer.c
GRAPHFILES := $(SRCDIR)/graphics.c
HFILES := $(HDIR)/io.h
SFILES := $(BDIR)/boot.S
LFILES := $(LDIR)/link.ld

ifeq ($(OS), Windows_NT)
	EXT := .o
	OFILES := $(BINDIR)/boot$(EXT) $(BINDIR)/kernel$(EXT) $(BINDIR)/io$(EXT)
	CPATH := C:\Users\Ruben\Documents\Studie\ReflectOS\gcc-arm-10.3-2021.07-mingw-w64-i686-aarch64-none-elf\bin
	CFLAGS := -Wall -O1 -ffreestanding -nostdinc -nostdlib -nostartfiles
	LFLAGS := -nostdlib $(OFILES) -T $(LFILES)
else
	EXT := .o
	OFILES := $(BINDIR)/boot$(EXT) $(BINDIR)/kernel$(EXT) $(BINDIR)/io$(EXT) $(BINDIR)/buffer$(EXT) $(BINDIR)/graphics$(EXT)
	CPATH := /home/niko/Documenten/'Hr - Technisch Informatica'/VIRTUALMIRROR/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin
	CFLAGS := -Wall -O1 -ffreestanding -nostdinc -nostdlib -nostartfiles
	LFLAGS := -nostdlib $(OFILES) -T $(LFILES)
endif

TARGET := clean boot kernel io buffer graphics kernel8.img
CLEAN := rm -r $(BINDIR); mkdir $(BINDIR); rm ./reflectos.img;
EXTS := *.o* *.elf* *.img*


all: $(TARGET)


boot: $(SFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -c $(SFILES) -o $(BINDIR)/boot$(EXT)


kernel: $(KERNELFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -I$(HDIR) -c $(KERNELFILES) -o $(BINDIR)/kernel$(EXT)


io: $(IOFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -I$(HDIR) -c $(IOFILES) -o $(BINDIR)/io$(EXT)


buffer: $(BUFFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -I$(HDIR) -c $(BUFFILES) -o $(BINDIR)/buffer$(EXT)


graphics: $(GRAPHFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -I$(HDIR) -c $(GRAPHFILES) -o $(BINDIR)/graphics$(EXT)


kernel8.img: 
	$(CPATH)/$(LCC) $(LFLAGS) -o $(BINDIR)/reflectos.elf
	$(CPATH)/$(OCC) -O binary $(BINDIR)/reflectos.elf kernel8.img


clean:
	@echo [info] cleaning
	$(clean)
	@echo [ok] files removed