#include "PcieApi.h"

static int pcie_device_file_descriptor;
static void *pcie_mapped_base_address;

int open_pcie_device(char *pcie_device) {
	if ((pcie_device_file_descriptor = open(pcie_device, O_RDWR | O_SYNC)) == -1) {
		return -1;
	}
	return 0;
}

void close_pcie_device() {
	close(pcie_device_file_descriptor);
}

void * get_pcie_base_address() {
	pcie_mapped_base_address = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, pcie_device_file_descriptor, 0);
	return pcie_mapped_base_address;
}

int dealloc_pcie_from_memory() {
	if (munmap(pcie_mapped_base_address, MAP_SIZE) == -1) {
		return -1;
	}
	return 0;
}

void write_byte(off_t pcie_offset, uint32_t data) {
	void *virt_addr;
	uint32_t writeval;
	writeval = data;
	virt_addr = pcie_mapped_base_address + pcie_offset;
	*((uint8_t *) virt_addr) = writeval;
}

void write_half_word(off_t pcie_offset, uint32_t data) {
	void *virt_addr;
	uint32_t writeval;
	writeval = data;
	virt_addr = pcie_mapped_base_address + pcie_offset;
	writeval = htols(writeval);
	*((uint16_t *) virt_addr) = writeval;
}

void write_word(off_t pcie_offset, uint32_t data) {
	void *virt_addr;
	uint32_t writeval;
	writeval = data;
	virt_addr = pcie_mapped_base_address + pcie_offset;
	writeval = htoll(writeval);
	*((uint32_t *) virt_addr) = writeval;
}

void send_packet(off_t pcie_offset, char *packet_data, uint32_t packet_length) {
	void *virt_addr;
	char *packet_data_ptr;
	uint32_t writeval;
	uint32_t num_words_to_send;
	uint32_t num_remaining_bytes;
	num_words_to_send = packet_length / 4;
	num_remaining_bytes = packet_length % 4;
	packet_data_ptr = packet_data;
	for (int i=0;i<num_words_to_send;i++){
		writeval = *((uint32_t *) packet_data_ptr);
		write_word(pcie_offset,writeval);
		packet_data_ptr = packet_data_ptr + 4;
	}
	for (int i=0;i<num_remaining_bytes;i++){
		writeval = *((uint8_t *) packet_data_ptr);
		write_byte(pcie_offset,writeval);
		packet_data_ptr = packet_data_ptr + 1;
	}

} 

