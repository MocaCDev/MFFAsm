#ifndef GLB
#define GLB
#include <stdlib.h>

#if defined(__linux__)
#define LINUX
#define SYSTEM_TYPE "LINUX"
#elif defined(__WIN32)
#define WIN32
#define SYSTEM_TYPE "WIN32"
#elif defined(__WIN64)
#define WIN64
#define SYSTEM_TYPE "WIN64"
#endif

/*
 * Default Values for everything
 */

// If not .SET_STACK in the mffs file, stack is set to default size.
#define DEFAULT_STACK_SIZE  0xFFFF
#define MAX_STACK_SIZE      0xFFFF0

int str_len(char *string);
int cmp_str(char *a, char *b);
int is_ascii(char c);
int is_hex(char *val);
long int convert(char *val);

#endif