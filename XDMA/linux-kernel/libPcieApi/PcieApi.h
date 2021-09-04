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

/*******************************************************************************
 * The size of the region of memory mapped to the pcie device for reads and
 * writes. There are 32 channels each 1024 bytes
 ******************************************************************************/
#define MAP_SIZE (32*1024UL)

/*******************************************************************************
 * The size in bytes of a channel
 ******************************************************************************/
#define CHANNEL_SIZE 1024

/*******************************************************************************
 * This function opens up the file corresponding to the pcie device. The pcie
 * device file should be located under the /dev directory on the file system.
 *
 * @param pcie_device The path for the location of the pcie device file. 
 * @return The file descriptor for the opened pcie device file.
 ******************************************************************************/
int open_pcie_device(char *pcie_device);

/*******************************************************************************
 * This function maps a region of memory for reads/writes to pcie. A data write
 * to an address in this memory region initiates a send over pcie. A data read
 * from an address in this memory region initiates a read from pcie. The base
 * address of this memory region is abstracted. In send/receive functions, the 
 * pcie offset will be used for data reads/writes at an offset from the memory
 * region base address. 
 *
 * @param pcie_device_file_descriptor The file descriptor for the opened pcie 
 *                                    device file.
 ******************************************************************************/
void init_pcie_device(int pcie_device_file_descriptor);


/*******************************************************************************
 * This function unmaps the memory map allocated for the pcie device and closes
 * the pcie device file.
 *
 * @param pcie_device_file_descriptor The path for the location of the pcie 
 *                                     device file.
 ******************************************************************************/
void close_pcie_device(int pcie_device_file_descriptor);

/*******************************************************************************
 * This function writes a single byte to the pcie device at a specified offset
 *
 * @param pcie_offset The offset from the base address of the pcie memory region 
 * @param data The least significant byte of this input is written to the 
 *             pcie memory region
 ******************************************************************************/
void write_byte(off_t pcie_offset, uint32_t data);

/*******************************************************************************
 * This function writes a word to the pcie device at a specified offset
 *
 * @param pcie_offset The offset from the base address of the pcie memory region 
 * @param data This input is written to the pcie memory region
 ******************************************************************************/
void write_word(off_t pcie_offset, uint32_t data);

/*******************************************************************************
 * This function sends a packet over pcie at a provided channel.
 *
 * @param channel The pcie channel to write to 
 * @param packet_data This input is the packet contents to be written to the 
 *                     pcie memory region
 * @param packet_length The size in bytes of the packet contents
 ******************************************************************************/
void send_packet(uint32_t channel, char *packet_data, uint32_t packet_length); 

