#include "PcieApi.h"



int main(){
	int pcie_device_file_descriptor = 0;
	char *sample_data = "sample_data";
	pcie_device_file_descriptor = open_pcie_device("/dev/pcie_xdma");
	init_pcie_device(pcie_device_file_descriptor);
	send_packet(0,sample_data,11);
	close_pcie_device(pcie_device_file_descriptor);

} 

