#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define ECE_BUF_SIZE 4096
static char ece_buffer[ECE_BUF_SIZE];


int main()
{
    int fd = open("/dev/deekshna_mod", O_RDWR);
    if(fd < 0)
    {
        printf("open failed\n");
        return 1;
    }
    //int sum=0;
    int num=0; int cond = 1;
    do
    {
        printf("Enter an integer to be added:\n");
        scanf("%s",ece_buffer);
        write(fd,ece_buffer,strlen(ece_buffer));
        printf("The sum is %d \n", atoi(read(fd,ece_buffer,strlen(ece_buffer)));
        printf("Enter:\n1 :To conitnue adding numbers\n2 :To exit\n");
        scanf(" %d",&cond);
    } while (cond==1);
    close(fd);
    exit(0);
    return 0;
}
