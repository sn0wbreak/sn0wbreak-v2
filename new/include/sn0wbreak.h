#ifndef SN0WBREAK_H
#define SN0WBREAK_H

#ifdef DEBUG_ENABLED
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define INFO(x...) printf("[*] "), printf(x)
#define ERROR(x...) printf("ERROR: "), printf(x)
#define DEBUG(x...) if (DEBUG_TEST) { printf("DEBUG: "), printf(x); }

#endif