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
