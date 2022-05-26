obj-m += g_mod.o

KDIR=/usr/src/linux-headers-5.13.0-40-generic

CFLAGS = -D__KERNEL__ -DMODULE -I$(KDIR)/include -Wall

all:
	$(MAKE) -C $(KDIR) M=$(shell pwd) $(KCONFIG) modules
	
clean:
	$(MAKE) -C $(KDIR) M=$(shell pwd) clean
	rm -f *.o