#include "global.h"

int str_len(char *string)
{
  int i = 0;
  while(string[i] != '\0')
    i++;
  
  return i;
}

int cmp_str(char *a, char *b)
{
  if(str_len(a) > str_len(b) || str_len(b) > str_len(a)) return 1;

  int is_same = 1; // false by default

  int i = 0;
  while(i < str_len(a))
  {
    if(i == str_len(a) - 1 && a[i] == b[i]) is_same = 0;
    if(!(a[i] == b[i]))
    {
      break;
    }
    i++;
  }

  return is_same;
}

int is_ascii(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= 0x48 && c <= 0x57) ? 0 : 1;
}

int is_hex(char *val)
{
  for(int i = 0; i < str_len(val); i++)
  {
    if(val[i] == 'x') return 0;
  }
  return 1;
}

#include <stdio.h>
long int convert(char *val)
{
  int number = 0;
  int power = 0;

  int curr_number = 0;

  for(int i = 2; i < str_len(val); i++)
  {
    number += (16 * power) * atoi(&val[i]);
    power++;
  }

  printf("%d", number);
}