obj-m += my_module.o

KDIR := /home/xiangbb/optee/linux
ARCH := arm64
CROSS_COMPILE := aarch64-linux-gnu-
PWD := $(shell pwd)

all:    
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean

