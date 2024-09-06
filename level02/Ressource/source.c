#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char **argv, const char **envp)
{
  int v5;
  int v8;
  int v9;
  char username[96];
  char fake_pass[96];
  char real_pass[48];
  FILE *real_passFile;

  v5 = 0;
  v8 = 0;
  v9 = 0;
  memset(username, 0, sizeof(username));
  memset(fake_pass, 0, sizeof(fake_pass));
  memset(real_pass, 0, 41);
  real_passFile = fopen("/home/users/level03/.real_pass", "r");
  if ( !real_passFile )
  {
    fwrite("ERROR: failed to open real_password file\n", 1, 36, stderr);
    exit(1);
  }
  v9 = fread(real_pass, 1, 41, real_passFile);
  real_pass[strcspn(real_pass, "\n")] = 0;
  if ( v9 != 41 )
  {
    fwrite("ERROR: failed to read real_password file\n", 1uLL, 0x24uLL, stderr);
    fwrite("ERROR: failed to read real_password file\n", 1uLL, 0x24uLL, stderr);
    exit(1);
  }
  fclose(real_passFile);

  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");

  printf("--[ Username: ");
  fgets(username, 100, stdin);
  username[strcspn(username, "\n")] = 0;

  printf("--[ Password: ");
  fgets(fake_pass, 100, stdin);
  fake_pass[strcspn(fake_pass, "\n")] = 0;
  puts("*****************************************");
  if ( strncmp(real_pass, fake_pass, 41) )
  {
    printf(username);
    puts(" does not have access!");
    exit(1);
  }
  printf("Greetings, %s!\n", username);
  system("/bin/sh");
  return 0;
}