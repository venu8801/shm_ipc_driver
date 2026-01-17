# make file to build the kernel module

export ARCH = arm64
export CROSS_COMPILE=aarch64-linux-gnu-

obj-m += \
	src/shm_module.o

EXTRA_CFLAGS=-I$(PWD)/inc

ifneq ($(ARCH), arm64)
	KDIR = /lib/modules/$(shell uname -r)/build
endif

KDIR = /home/venu/projects/linux

all:
	make -C $(KDIR)  M=$(shell pwd) modules

clean:
	make -C $(KDIR)  M=$(shell pwd) clean