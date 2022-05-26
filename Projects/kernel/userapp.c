#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int args, char *argv[])
{
    char buf0[64] = "First Test...";
    char buf1[64];

    //buf0[0] = "First things first";

    int fd = open("/dev/test_mod01", O_RDWR);
    if(fd < 0)
    {
        printf("open failed");
        return 1;
    }
    if(write(fd, &buf0, 64) < 0)
    {
        printf("\n can't write buf0\n");
        return 1;
    }
    if(read(fd,&buf1,64) < 0)
    {
        printf("\n can't read to buf1\n");
        return 1;
    }
    //read(fd, "BLahblahblah",64);
    //write(fd, "writeblah", 64);
    return 0;
}