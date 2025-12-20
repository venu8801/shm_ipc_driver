# make file to build the kernel module

obj-m += \
	src/shm_module.o

KDIR = /lib/modules/$(shell uname -r)/build
EXTRA_CFLAGS=-I$(PWD)/inc

all:
	make -C $(KDIR)  M=$(shell pwd) modules

clean:
	make -C $(KDIR)  M=$(shell pwd) clean