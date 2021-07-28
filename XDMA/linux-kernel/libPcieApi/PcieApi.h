#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <byteswap.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>

#include <sys/types.h>
#include <sys/mman.h>

/* ltoh: little to host */
/* htol: little to host */
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define ltohl(x)       (x)
#define ltohs(x)       (x)
#define htoll(x)       (x)
#define htols(x)       (x)
#elif __BYTE_ORDER == __BIG_ENDIAN
#define ltohl(x)     __bswap_32(x)
#define ltohs(x)     __bswap_16(x)
#define htoll(x)     __bswap_32(x)
#define htols(x)     __bswap_16(x)
#endif

#define MAP_SIZE (32*1024UL)

int open_pcie_device(char *pcie_device);

void close_pcie_device();

void * get_pcie_base_address();

int dealloc_pcie_from_memory();

void write_byte(off_t pcie_offset, uint32_t data);

void write_half_word(off_t pcie_offset, uint32_t data);

void write_word(off_t pcie_offset, uint32_t data);

void send_packet(off_t pcie_offset, char *packet_data, uint32_t packet_length); 

