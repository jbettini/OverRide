#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void secret_backdoor() {
  char cmd[128];

  fgets(cmd, 128, stdin);
  system(cmd);
}

void    set_msg(int buf) {
  char s[1024];

  memset(s, 0, sizeof(s));
  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets(s, 1024, stdin);
  strncpy((char *)buf, s, *(int *)(buf + 180));
}

void set_username(int buf) {
  char username[140];

  puts(">: Enter your username");
  printf(">>: ");
  fgets(username, 128, stdin);
  for (int i = 0; i <= 40 && username[i]; ++i )
     *(char *)(buf + i + 140) = username[i];
  printf(">: Welcome, %s", ((const char *)(buf + 140)));  
}

void handle_msg() {
  char buf[140];

  set_username((int)buf);
  set_msg((int)buf);
  puts(">: Msg sent!");
}

int main(int argc, const char **argv, const char **envp) {

  puts("--------------------------------------------\n"
    "|   ~Welcome to l33t-m$n ~    v1337        |\n"
    "--------------------------------------------");
  handle_msg();
  return 0;
}