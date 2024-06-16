
-----------------------------------------------------

undefined4 auth(char *param_1,uint param_2) {
  size_t sVar1;
  undefined4 uVar2;
  long lVar3;
  int local_18;
  uint local_14;
  
  sVar1 = strcspn(param_1,"\n");
  param_1[sVar1] = '\0';
  sVar1 = strnlen(param_1,0x20);
  if ((int)sVar1 < 6) {
    uVar2 = 1;
  }
  else {
    lVar3 = ptrace(PTRACE_TRACEME);
    if (lVar3 == -1) {
      puts("\x1b[32m.---------------------------.");
      puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
      puts("\x1b[32m\'---------------------------\'");
      uVar2 = 1;
    }
    else {
      local_14 = ((int)param_1[3] ^ 0x1337U) + 0x5eeded;
      for (local_18 = 0; local_18 < (int)sVar1; local_18 = local_18 + 1) {
        if (param_1[local_18] < ' ') {
          return 1;
        }
        local_14 = local_14 + ((int)param_1[local_18] ^ local_14) % 0x539;
      }
      if (param_2 == local_14) {
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}

-----------------------------------------------------

void clear_stdin(void) {
  int iVar1;
  
  do {
    iVar1 = getchar();
    if ((char)iVar1 == '\n') {
      return;
    }
  } while ((char)iVar1 != -1);
  return;
}

-----------------------------------------------------

void enable_timeout_cons(void) {
  signal(0xe,prog_timeout);
  alarm(0x3c);
  return;
}

-----------------------------------------------------

undefined4 get_unum(void) {
  undefined4 local_10 [3];
  
  local_10[0] = 0;
  fflush(stdout);
  __isoc99_scanf(&DAT_08048a60,local_10);
  clear_stdin();
  return local_10[0];
}

-----------------------------------------------------

void prog_timeout(void) {
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x80);
  (*pcVar1)();
  return;
}

-----------------------------------------------------
bool main(undefined4 param_1,undefined4 param_2) {
  int iVar1;
  int in_GS_OFFSET;
  uint uStack_38;
  char local_34 [32];
  int local_14;
  
  local_14 = *(int *)(in_GS_OFFSET + 0x14);
  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(local_34,0x20,stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  __isoc99_scanf();
  iVar1 = auth(local_34,uStack_38);
  if (iVar1 == 0) {
    puts("Authenticated!");
    system("/bin/sh");
  }
  if (local_14 != *(int *)(in_GS_OFFSET + 0x14)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar1 != 0;
}