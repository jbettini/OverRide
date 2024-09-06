#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

unsigned log_wrapper(FILE *log_file, const char *prefix, const char *msg) {
    char log_message[264];
    unsigned canary;

    canary = __readfsqword(0x28u);
    strcpy(log_message, prefix);
    snprintf(&log_message[strlen(log_message)], 254 - strlen(log_message), msg);
    log_message[strcspn(log_message, "\n")] = 0;
    fprintf(log_file, "LOG: %s\n", log_message);

    return __readfsqword(0x28u) ^ canary;
}

int main(int argc, const char **argv) {
    FILE *log_file, *input_file;
    int fd;
    char buf;
    char dest[104];
    
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    log_file = fopen("./backups/.log", "w");
    if (!log_file) {
        printf("ERROR: Failed to open log file\n");
        exit(1);
    }

    log_wrapper(log_file, "Starting back up: ", argv[1]);

    input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }

    strcpy(dest, "./backups/"); 
    strncat(dest, argv[1], 99 - strlen(dest)); 

    fd = open(dest, O_WRONLY | O_CREAT, 0640);
    if (fd < 0) {
        printf("ERROR: Failed to open %s\n", dest);
        exit(1);
    }

    while ((buf = fgetc(input_file)) != EOF) {
        write(fd, &buf, 1);
    }

    log_wrapper(log_file, "Finished back up ", argv[1]);

    fclose(input_file);
    close(fd);
    fclose(log_file);

    return 0;
}
