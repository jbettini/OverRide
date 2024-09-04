#include <stdbool.h>

bool verify_user_name(char *username)
{
  puts("verifying username....\n");
  return memcmp(username, "dat_wil", 7) != 0;
}

bool verify_user_pass(const void *pass)
{
  return memcmp(pass, "admin", 5) != 0;
}

int main(int argc, const char **argv, const char **envp)
{
  char pass[64];
  char username[257];
  bool v5;

  memset(pass, 0, sizeof(pass));
  memset(username, 0, sizeof(username));
  v5 = 0;
  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username: ");
  fgets(username, 256, stdin);
  v5 = verify_user_name(username);
  if ( v5 ) {
    puts("nope, incorrect username...\n");
  } else {
    puts("Enter Password: ");
    fgets(pass, 100, stdin);
    v5 = verify_user_pass(pass);
    puts("nope, incorrect password...\n");
  }
  return 1;
}