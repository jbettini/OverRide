#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



int main(int ac, char **av) {
    char *param_1 = av[1];
    int local_18;
    uint32_t local_14;
    size_t sVar1;
    sVar1 = strcspn(param_1,"\n");
    param_1[sVar1] = '\0';
    sVar1 = strnlen(param_1,0x20);
    if ((int)sVar1 < 6) {
          printf("local invalid\n");
          return 1;
    }
    local_14 = ((int)param_1[3] ^ 0x1337U) + 0x5eeded;
     for (local_18 = 0; local_18 < (int)sVar1; local_18 = local_18 + 1) {
        if (param_1[local_18] < ' ') {
          printf("local invalid\n");
          return 1;
        }
        local_14 = local_14 + ((int)param_1[local_18] ^ local_14) % 1337;
      }
      printf("local 14 =  %p | %u \n", &local_14,local_14);
      return 1;
}
