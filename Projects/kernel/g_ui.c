#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define ECE_BUF_SIZE 4096

static char ece_buffer[ECE_BUF_SIZE];


int main(){
    int fd = open("/dev/g_mod", O_RDWR);
    if(fd < 0) {
        printf("Cannot open device file...\n");
        return 0;
    }

    printf("Enter string in lowercase: ");
    scanf("%s", ece_buffer);
    printf("Writing into Kernel...\n");
    write(fd, ece_buffer, strlen(ece_buffer));
    printf("Reading from Kernel...\n");
    read(fd, ece_buffer, strlen(ece_buffer));
    printf("Returned string in uppercase:  = %s\n\n", ece_buffer);
    close(fd);
    exit(0);
    return 0;
}