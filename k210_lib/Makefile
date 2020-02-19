# Makefile for my project
# Huang Rui <vowstar[]gmail.com>

PROJ := libc.a

CC := riscv64-linux-gcc
AS := riscv64-linux-as
AR := riscv64-linux-ar
INSTALLDAT = install -m644
INSTALLBIN = install -m755

OUTPUT_DIR := build
CSOURCES := $(wildcard *.c)

SSOURCES := $(wildcard *.S)

CFLAGS := \
	-Wall -Wextra -Wshadow -Wmissing-prototypes -Wmissing-declarations \
	-fno-common -Os

SFLAGS :=

LDFLAGS := -Wl,-elf2flt

COBJS := $(patsubst %.c, $(OUTPUT_DIR)/%.o, $(notdir $(CSOURCES)))
	

SOBJS := $(patsubst %.S, $(OUTPUT_DIR)/%.o, $(notdir $(SSOURCES)))

all: $(OUTPUT_DIR)/$(PROJ) $(OUTPUT_DIR)/libtcc1.a $(SOBJS) $(COBJS)

$(OUTPUT_DIR)/%.o: %.c | builddir
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT_DIR)/%.o: %.S | builddir
	$(AS) -c -o $@ $< $(SFLAGS)

$(OUTPUT_DIR)/$(PROJ): $(COBJS) | builddir
	$(AR) -crs $@ $^

$(OUTPUT_DIR)/libtcc1.a: $(SOBJS) | builddir
	$(AR) -crs $@ $(OUTPUT_DIR)/dummy.o

install: all
	@mkdir -p $(DESTDIR)/usr/lib/tcc/
	@mkdir -p $(DESTDIR)/usr/include/
	$(INSTALLDAT) $(OUTPUT_DIR)/crt1.o $(DESTDIR)/usr/lib/crt1.o
	$(INSTALLDAT) $(OUTPUT_DIR)/crti.o $(DESTDIR)/usr/lib/crti.o
	$(INSTALLDAT) $(OUTPUT_DIR)/crtn.o $(DESTDIR)/usr/lib/crtn.o
	$(INSTALLDAT) $(OUTPUT_DIR)/libc.a $(DESTDIR)/usr/lib/libc.a
	$(INSTALLDAT) $(OUTPUT_DIR)/libtcc1.a $(DESTDIR)/usr/lib/tcc/libtcc1.a
	$(INSTALLDAT) stdio.h $(DESTDIR)/usr/include/stdio.h
	$(INSTALLDAT) syscall.h $(DESTDIR)/usr/include/syscall.h

builddir:
	@mkdir -p $(OUTPUT_DIR)

clean:
	@rm -rf $(OUTPUT_DIR)

.PHONY: clean all install builddir
