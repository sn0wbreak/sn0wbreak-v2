#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

#define DEBUG_ENABLED

#include "libirecovery.h"
#include "sn0wbreak.h"

int main(int argc, char **argv)
{
	irecv_init();
	irecv_client_t client = NULL;
	if (irecv_open_with_ecid_and_attempts(&client, 0, 5) != IRECV_E_SUCCESS)
	{
		ERROR("Could not connect to iDevice! Make sure you are in DFU mode...\n");
		return -1;
	}
	irecv_device_t device = NULL;
	if (irecv_devices_get_device_by_client(client, &device) != IRECV_E_SUCCESS)
	{
		ERROR("Something went wrong, could not get iDevice info!\n");
		return -1;
	}
	printf("Product Type: %s\nHardware Model: %s\nBoard ID: %d\nChip ID: %d\n", device->product_type, device->hardware_model, device->board_id, device->chip_id);
    return 0;
}
