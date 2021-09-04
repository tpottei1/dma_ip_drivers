#include "PcieApi.h"

static void *pcie_mapped_base_address;


int open_pcie_device(char *pcie_device) {
	int pcie_device_file_descriptor = 0;
	pcie_device_file_descriptor = open(pcie_device, O_RDWR | O_SYNC) == -1;
	return pcie_device_file_descriptor;
}

void close_pcie_device(int pcie_device_file_descriptor) {
	int err = 0;
	err = munmap(pcie_mapped_base_address, MAP_SIZE) == -1;
	close(pcie_device_file_descriptor);
}

void init_pcie_device(int pcie_device_file_descriptor) {
	pcie_mapped_base_address = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, pcie_device_file_descriptor, 0);
}


void write_byte(off_t pcie_offset, uint32_t data) {
	void *virt_addr;
	uint32_t writeval;
	writeval = data;
	virt_addr = pcie_mapped_base_address + pcie_offset;
	*((uint8_t *) virt_addr) = writeval;
}

void write_word(off_t pcie_offset, uint32_t data) {
	void *virt_addr;
	uint32_t writeval;
	writeval = data;
	virt_addr = pcie_mapped_base_address + pcie_offset;
	writeval = htoll(writeval);
	*((uint32_t *) virt_addr) = writeval;
}

void send_packet(uint32_t channel, char *packet_data, uint32_t packet_length) {
	void *virt_addr;
	off_t write_offset;
	char *packet_data_ptr;
	uint32_t writeval;
	uint32_t num_words_to_send;
	uint32_t num_remaining_bytes;
	num_words_to_send = packet_length / 4;
	num_remaining_bytes = packet_length % 4;
	packet_data_ptr = packet_data;
	write_offset = channel * CHANNEL_SIZE;
	for (int i=0;i<num_words_to_send;i++){
		writeval = *((uint32_t *) packet_data_ptr);
		write_word(write_offset,writeval);
		packet_data_ptr = packet_data_ptr + 4;
		write_offset = write_offset + 4;
	}
	for (int i=0;i<num_remaining_bytes;i++){
		writeval = *((uint8_t *) packet_data_ptr);
		write_byte(write_offset,writeval);
		packet_data_ptr = packet_data_ptr + 1;
		write_offset = write_offset + 1;
	}

} 

