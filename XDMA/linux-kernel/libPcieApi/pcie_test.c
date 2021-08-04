#include "PcieApi.h"



int main(){
	char *sample_data = "sample_data";
	open_pcie_device("/dev/pcie_xdma");
	get_pcie_base_address();
	send_packet(0,sample_data,11);
	dealloc_pcie_from_memory();
	close_pcie_device();

} 

