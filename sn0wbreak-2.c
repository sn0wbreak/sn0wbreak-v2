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
#include "toolz.c"

int main ()
{
pz_get(false,"http://sn0wbreak.com/res.zip", "Cydia.tar", sbfile("Cydia.tar-2"));
}
