// utility file of the sn0wbreak project

#include <libusb-1.0/libusb.h>
#include "partial.h"
#include <stdbool.h>

// this is the info function
bool q = false;
#define INFO(x...) \
if (!q) { printf("[*] "), printf(x);}

// and error

#define ERROR(x...) \
 	do { printf("[ERROR]: "), printf(x); } while(0);


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

// zip dl info funnction

void zip_callback(ZipInfo* info, CDFile* file, size_t progress) {
int percentDone = progress * 100/file->compressedSize;
INFO("Downloading.... %d\r", percentDone);
}

int pz_get(bool listing,char *url, char *file, char *outname)
{
//INFO("listing: %d, outname: %s, url: %s, file: %s\n", listing, outname, url, file);
INFO("Initialazing partialzip....\n");
ZipInfo* zinfo = PartialZipInit(url);
if(!zinfo)
{
ERROR("Cannot find file %s\n",url);
return 0;
}
if(listing)
{
PartialZipListFiles(zinfo);
return 1;
}
INFO("Setting progress callback\n");
PartialZipSetProgressCallback(zinfo, zip_callback);
INFO("Searching for %s in %s\n",file,url);
CDFile* zfile = PartialZipFindFile(zinfo, file);
if(!zfile)
{
ERROR("Cannot find file %s in %s\n", file, url);
return 0;
}
INFO("Found %s in %s\n",file,url);
INFO("Getting file %s....\n",file);
unsigned char* data = PartialZipGetFile(zinfo, zfile);
INFO("\n");
int dataLen = zfile->size;
INFO("Filesize: %d Bytes\n",dataLen);
PartialZipRelease(zinfo);
data = realloc(data, dataLen + 1);
data[dataLen] = '\0';
FILE* outfile;
INFO("Going to open outfile %s...\n",outname);
outfile = fopen(outname, "w");
if (outfile == NULL)
{
ERROR("Failed to open file %s\n",outname);
return 0;
}
int done = 0;
INFO("Opened outfile %s successfully, going to write...\n",outname);
done = fwrite(data, sizeof(char), dataLen, outfile);
fclose(outfile);
free(data);
INFO("Alright, everything worked! The file %s should be saved now!\n",outname);
return 1;
}

