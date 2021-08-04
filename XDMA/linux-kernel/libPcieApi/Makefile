CC ?= gcc

all: pcie_api shared

pcie_api:
	$(CC) -fPIC -c -std=c99 -o PcieApi.o PcieApi.c -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -D_LARGE_FILE_SOURCE

shared:
	$(CC) -shared -o libPcieApi.so PcieApi.o

install:
	mv libPcieApi.so /lib/x86_64-linux-gnu/

pcie_test:
	gcc -o pcie_test pcie_test.c -lPcieApi

clean:
	rm -rf *.o *.so pcie_test

