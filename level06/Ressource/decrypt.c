#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int ac, char **av) {
  int i;
  int v4;
  int v5;
  char *s = av[1];
  v5 = strnlen(s, 32);
  if ( v5 <= 5 )
    return 1;
  v4 = (s[3] ^ 0x1337) + 6221293;
  for ( i = 0; i < v5; ++i )
  {
    if ( s[i] <= 31 )
      return 1;
    v4 += (v4 ^ (unsigned int)s[i]) % 0x539;
  }
  printf("Hash =  %p | %u \n", &v4,v4);
  return 0;
}
