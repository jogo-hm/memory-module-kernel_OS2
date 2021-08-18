# File: Makefile
obj-m += mem_201505550.o # Name of the file to output
all:
    # Do when compiled
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd)
modulesclean:
    # Do when de module is clean
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean