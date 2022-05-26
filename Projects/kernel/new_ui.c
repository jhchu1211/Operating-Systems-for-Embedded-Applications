#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define ECE_BUF_SIZE 4096

//const char* bank[] = { "chair" , "juice" , "glass", "grape" , "mouse"};

static char ece_buffer[ECE_BUF_SIZE];
static char right[ECE_BUF_SIZE] = "ooooo";

int main()
{
    //int p = rand() % 5;
    int fd = open("/dev/test_mod01", O_RDWR);
    int countMax = 4;
    int count = 0;
    int tr = 0;
    int offset = 0;
    int b = 0;
    do
    {
        b = 0;
        printf("\nEnter 5 letter string: \n");
        scanf("%s", ece_buffer);
        write(fd,ece_buffer,strlen(ece_buffer));
        read(fd,ece_buffer,strlen(ece_buffer));
        printf("%s", ece_buffer);
        for(int i = 0;i < 5; i++)
        {
            if(ece_buffer[i] == 'o')
            {
                b++;
            }
        }
        if(b == 5)
        {
            printf("\nchecked\n");
            break;
        }
        count++;
        //offset = offset + strlen(ece_buffer);
    } while (tr == 0 && count <= countMax);
    close(fd);
    exit(0);
    return 0;
}