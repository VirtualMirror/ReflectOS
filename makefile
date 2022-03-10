CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
GCCFLAGS = -Wall -02 -ffreestanding -nostdinc -nostdlib -nostartfiles
GCCPATH = 

all: clean kernel8.img

boot.o: boot.s
		