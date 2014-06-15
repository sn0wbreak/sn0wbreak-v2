  // utility file of the sn0wbreak project

  #include <libusb-1.0/libusb.h>
  #include "partial.h"
  #include <stdbool.h>
  #include <math.h>

  // set the default quiet mode to 0

  bool q = false;

  // this is the info function
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
    if(!file_exists(file))
    {
      mkdir(file,0755);
    }
    return strcat(file, filename);
    (char *)filename = NULL;
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
    printf("Downloading.... %d%%\r", percentDone);
  }

  // best function ever to partial zip an url
  // example usage:
  // example 1:
  // pz_get(false,"http://sn0wbreak.com/res.zip", "Cydia.tar", "/tmp/Cydia.tar");
  // above fets the file Cydia.tar form the archive http://sn0wbreak.com/res.zip and saves it to /tmp/Cydia.tar
  // example 2:
  // pz_get(true,"http://sn0wbreak.com/res.zip", NULL,NULL);
  // lists all files in the archive http://sn0wbreak.com/res.zip

  // Big thanks to planetbeing for the partialzip library

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
      printf("Files in %s:\n",url);
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

/* dat fuk not work
// function to format a number of bytes to MiB GiB KiB etc

char *formatsize(int bytes)
{
if(bytes > 1024 * 1024 * 1024)
{
char end[4] = " GiB";
int size = bytes / 1024 / 1024 / 1024;
printf("%d%s",size,end);
}
else if(bytes > 1024 * 1024)
{
char end[4] = " MiB";
int size = bytes / 1024 / 1024;
printf("%d%s",size,end);
}
else if(bytes > 1024)
{
char end[4] = " KiB";
int size = bytes / 1024;
printf("%d%s",size,end);
}
else if(bytes < 1024)
{
char end[6] = " Bytes";
printf("%d%s",bytes,end);
}
}
*/ //end of not working shit

// file_exists function, returns true if a file exists
  int file_exists(const char filename[]) {
    struct stat stbuf;
    if (stat(filename, &stbuf) == -1) {
      return (0);
    }
    return (1);
  }

// setup function (not working atm)

  void set_up(void) // PoC
  {
    char *files[] = {"ibss.dfu","ibec.dfu","devt.dfu","rdisk.dmg"};
int *fackinglength = sizeof(files) / sizeof(*files);
    for(int i = 0;i<fackinglength;i++)
    {
      char *file = files[i];
      char *oname = sbfile(file); //TODO: get the shit working
      if(!file_exists(oname))
      {
        INFO("Going to download %s and save it to %s\n",file,oname);
        //pz_get(false,"http://sn0wbreak.com/res-v2.zip",file,oname); //TODO: cache & fetching of the device type (iPhone3,?)
      }
      file = NULL;
      oname = NULL;
    }
  }
