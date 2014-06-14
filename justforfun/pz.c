/* 
A simple tool to use my pz_get function
compile with: gcc pz.c ../partial.c -lcurl -lz
Copyright (c) The sn0wbreak team 2014
*/

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
#include "../toolz.c"

int main(int argc, char *argv[])
{
if(argv[1] == NULL)
{
printf("Usage: %s <zipfile> [<extractfile> <outfile> [-q]]\nIf only zipfile is specified, I will return a listing of all files in zipfile,\notherwise I'll extract extractfile to outfile.\nIf -q is specified I will supress all information except errors.\nNote that -q is only for extracting files.\n\nI'll return 0 on success, 1 on usage errors, and -1 on errors.\n",argv[0]);
return 1;
}
if(argv[2] == NULL)
{
INFO("Listing files for %s\n",argv[1]);
pz_get(true,argv[1], NULL,NULL);
return 0;
}
else
{
if(argv[3] == NULL)
{
ERROR("Please specify an outilfe\n");
return -1;
}
if(argv[4] != NULL)
{
q=true;
}
INFO("Going to extract %s from %s and save it to %s\n",argv[2],argv[1],argv[3]);
if(pz_get(false,argv[1], argv[2],argv[3]))
{
return 0;
}
else
{
return -1;
}
}
}
