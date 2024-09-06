#include <stdio.h>
#include <string.h>
#include <unistd.h>

int get_unum() {
    int num;

    num = 0;
    fflush(stdout);
    scanf("%d", &num);
    clear_stdin();
    return num;
}

int store_number(int a1) {
    unsigned int unum;
    unsigned int index;

    printf(" Number: ");
    unum = get_unum();
    printf(" Index: ");
    index = get_unum();

    if (index % 3 == 0 || (unum >> 24) == 183) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    } else {
        *(unsigned int *)(a1 + 4 * index) = unum;
        return 0;
    }
}

int read_number(int a1) {
    unsigned int index;

    printf(" Index: ");
    index = get_unum();
    printf(" Number at data[%u] is %u\n", index, *(unsigned int *)(a1 + 4 * index));
    return 0;
}

int main(int argc, const char **argv, const char **envp) {
    char storage[400];
    int number;
    char command[4];
    int v9, v10, v11, v12;
    unsigned int canary;

    canary = __readgsdword(0x14u);
    number = 0;
    *(int *)command = 0;
    v9 = v10 = v11 = v12 = 0;
    memset(storage, 0, sizeof(storage));

    while (*argv) {
        memset((void *)*argv, 0, strlen(*argv));
        ++argv;
    }

    while (*envp) {
        memset((void *)*envp, 0, strlen(*envp));
        ++envp;
    }

    puts(
        "----------------------------------------------------\n"
        "  Welcome to wil's crappy number storage service!   \n"
        "----------------------------------------------------\n"
        " Commands:                                          \n"
        "    store - store a number into the data storage    \n"
        "    read  - read a number from the data storage     \n"
        "    quit  - exit the program                        \n"
        "----------------------------------------------------\n"
        "   wil has reserved some storage :>                 \n"
        "----------------------------------------------------\n"
    );

    while (1) {
        printf("Input command: ");
        number = 1;
        fgets(command, 20, stdin);
        command[strlen(command) - 1] = 0;

        if (!memcmp(command, "store", 5)) {
            number = store_number((int)storage);
        } else if (!memcmp(command, "read", 4)) {
            number = read_number((int)storage);
        } else if (!memcmp(command, "quit", 4)) {
            return 0;
        }

        if (number) {
            printf(" Failed to do %s command\n", command);
        } else {
            printf(" Completed %s command successfully\n", command);
        }

        *(int *)command = 0;
        v9 = v10 = v11 = v12 = 0;
    }
}
