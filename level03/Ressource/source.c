
int decrypt(EVP_PKEY_CTX *arg, uchar *out,size_t *outlen,uchar *in,size_t inlen)
{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  int in_GS_OFFSET;
  bool bVar6;
  bool bVar7;
  uint local_2c;
  undefined4 local_21;
  undefined4 local_1d;
  undefined4 local_19;
  undefined4 local_15;
  undefined local_11;
  int local_10;
  
  local_10 = *(int *)(in_GS_OFFSET + 0x14);
  local_21 = 0x757c7d51;
  local_1d = 0x67667360;
  local_19 = 0x7b66737e;
  local_15 = 0x33617c7d;
  local_11 = 0;
  uVar2 = 0xffffffff;
  puVar4 = &local_21;

  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *(char *)puVar4;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  } while (cVar1 != '\0');


  local_2c = 0;
  while( true ) {
    bVar6 = local_2c < ~uVar2 - 1;
    bVar7 = local_2c == ~uVar2 - 1;
    if (!bVar6) break;
    *(byte *)((int)&local_21 + local_2c) = (byte)arg ^ *(byte *)((int)&local_21 + local_2c);
    local_2c = local_2c + 1;
  }


  iVar3 = 0x11;
  puVar4 = &local_21;
  pbVar5 = (byte *)"Congratulations!";

  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *(byte *)puVar4 < *pbVar5;
    bVar7 = *(byte *)puVar4 == *pbVar5;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    pbVar5 = pbVar5 + 1;
  } while (bVar7);



  if ((!bVar6 && !bVar7) == bVar6) {
    iVar3 = system("/bin/sh");
  }
  else {
    iVar3 = puts("\nInvalid Password");
  }


  if (local_10 == *(int *)(in_GS_OFFSET + 0x14)) {
    return iVar3;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}

void test(int param_1,int param_2)
{
  EVP_PKEY_CTX *pEVar1;
  uchar *u1;
  size_t *st1;
  uchar *uc1;
  size_t st2;
  
  pEVar1 = (EVP_PKEY_CTX *)(param_2 - param_1);
  switch(pEVar1) {
  default:
    pEVar1 = (EVP_PKEY_CTX *)rand();
    decrypt(pEVar1, u1, st1, uc1, st2);
    break;
  case (EVP_PKEY_CTX *)0x1:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x2:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x3:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x4:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x5:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x6:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x7:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x8:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x9:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x10:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x11:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x12:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x13:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x14:
    decrypt(pEVar1,u1,st1,uc1,st2);
    break;
  case (EVP_PKEY_CTX *)0x15:
    decrypt(pEVar1,u1,st1,uc1,st2);
  }
  return;
}

undefined4 main(void) {
  uint __seed;
  int iStack_14;
  
  __seed = time((time_t *)0x0);
  srand(__seed);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf();
  test(iStack_14,0x1337d00d);
  return 0;
}
