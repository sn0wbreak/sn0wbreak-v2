#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
//#include "core.h"
//#include "payload.h"
//#include <libusb-1.0/libusb.h>

char *sbfile(char *filename) // tested, worx
{
  /* example usage:
  char *testfile = sbfile("res.zip");
  printf("%s",testfile);
  return 0;
 */
  char *homedir = getenv("HOME");
  char *file = strcat(homedir, "/.sn0wbreak/");
  file = strcat(file, filename);
  return file;
}
int main ()
{
}
