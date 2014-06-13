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
