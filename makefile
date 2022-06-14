GCC := aarch64-none-elf-gcc
LCC := aarch64-none-elf-ld
OCC := aarch64-none-elf-objcopy

HDIR := ./headers
LDIR := ./linker
BDIR := ./bootloader
SRCDIR := ./src
BINDIR := ./bin

KERNELFILES := $(SRCDIR)/kernel.c
IOFILES := $(SRCDIR)/io/io.c
BUFFILES := $(SRCDIR)/graphics/buffer.c
GRAPHFILES := $(SRCDIR)/graphics/graphics.c
KEYFILES := $(SRCDIR)/io/keyboard.c
TIMERFILES := $(SRCDIR)/system/timer.c
MEMFILES := $(SRCDIR)/system/memory.c
SCHEFILES := $(SRCDIR)/system/scheduler.c

MNFILES := $(SRCDIR)/structures/message_list.c

HOMESCREEN := $(SRCDIR)/views/home_view.c

HFILES := $(HDIR)/io.h
SFILES := $(BDIR)/boot.S
LFILES := $(LDIR)/link.ld

ifeq ($(OS), Windows_NT)
	EXT := .o
	OFILES := $(BINDIR)/boot$(EXT) $(BINDIR)/kernel$(EXT) $(BINDIR)/io$(EXT)
	CPATH := C:\Users\Ruben\Documents\Studie\ReflectOS\ReflectOS\gcc-arm-10.3-2021.07-mingw-w64-i686-aarch64-none-elf\bin
	CFLAGS := -Wall -O1 -ffreestanding -nostdinc -nostdlib -nostartfiles
	LFLAGS := -nostdlib $(OFILES) -T $(LFILES)
else
	EXT := .o
	OFILES := $(BINDIR)/*.o
	CPATH := /run/media/niko/Data/'Hr - Technisch Informatica'/VIRTUALMIRROR/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin
	CFLAGS := -Wall -O1 -ffreestanding -nostdinc -nostdlib -nostartfiles
	LFLAGS := -nostdlib $(OFILES) -T $(LFILES)
endif

TARGET := clean boot kernel io buffer graphics keyboard timer memory scheduler msg_list home_view kernel8.img
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


keyboard: $(KEYFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -I$(HDIR) -c $(KEYFILES) -o $(BINDIR)/keyboard$(EXT)


timer: $(TIMERFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -I$(HDIR) -c $(TIMERFILES) -o $(BINDIR)/timer$(EXT)


memory: $(MEMFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -I$(HDIR) -c $(MEMFILES) -o $(BINDIR)/memory$(EXT)

scheduler: $(SCHEFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -I$(HDIR) -c $(SCHEFILES) -o $(BINDIR)/scheduler$(EXT)

msg_list: $(MNFILES)
	$(CPATH)/$(GCC) $(CFLAGS) -I$(HDIR) -c $(MNFILES) -o $(BINDIR)/msg_list$(EXT)

home_view: $(HOMESCREEN)
	$(CPATH)/$(GCC) $(CFLAGS) -I$(HDIR) -c $(HOMESCREEN) -o $(BINDIR)/home_view$(EXT)


kernel8.img: 
	$(CPATH)/$(LCC) $(LFLAGS) -o $(BINDIR)/reflectos.elf
	$(CPATH)/$(OCC) -O binary $(BINDIR)/reflectos.elf kernel8.img


clean:
	@echo [info] cleaning
	$(clean)
	@echo [ok] files removed