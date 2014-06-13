//utility file of the sn0wbreak project

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

/* DFU mode */
void dfu_init(void)
{
    info("Put your device in DFU.\n if you do not know what DFU mode is do not attempt this\n");
    sleep(260);
    info("device should be in DFU mode by now\n");
    info("Done\n");
}
