#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static int var_in_data_segment = 16;

int main(int argc, char** argv)
{
    pid_t processid = 4310;
    //pid_t pid2 = 100;
    int var_on_the_stack1 = 1; //4 bytes
    double var_on_the_stack2 = 2; //8 bytes
    long double var_on_the_stack3 = 3; //16 bytes?? 24??
    int var_on_the_stack4 = 4;
    int status = 0;

    printf("stack[%d, 0x%p]\n", var_on_the_stack1, &var_on_the_stack1);
    printf("stack[%lf, 0x%p]\n", var_on_the_stack2, &var_on_the_stack2);
    printf("stack[%Lf, 0x%p]\n", var_on_the_stack3, &var_on_the_stack3);
    printf("stack[%d, 0x%p]\n", var_on_the_stack4, &var_on_the_stack4);
    printf("data [%d, 0x%p]\n", var_in_data_segment, &var_in_data_segment);
    printf("[%d]Before Fork\n", processid); //shows value along with address for value
    processid = fork(); //creates new process that runs concurrently with the original process
    //shares memory address.
    printf("[%d]After Fork\n", processid);
    /*if (processid == 0)
    {
        var_on_the_stack1 = 44; 
    }*/
    switch(processid)
    {
        case 0:
            var_on_the_stack1 = 1010101; 
            sleep(6); //pauses for x seconds
            printf("Parent\n"); //parent receives zero 
            break; 
        case -1: 
            printf("No\n");
            break;
        default: 
            waitpid(processid, &status, 0); 
            printf("waitpid 0 done\n");
            /*waitpid(processid, &status, -1); waits for any child process to end
            printf("waitpid -1 done\n");*/
            var_on_the_stack2 = 2020202; 
            sleep(6); //pauses for x seconds
            printf("Childt\n"); //child receives parent's pid
            break;
    } //waitpid waits for specfic child process
    //waiting for processid
    //returns referenced status address

    printf("[%d]stack[%d, 0x%p]\n", processid, var_on_the_stack1, &var_on_the_stack1); //getget() gets the actual processid
    printf("[%d]stack[%lf, 0x%p]\n", processid, var_on_the_stack2, &var_on_the_stack2); //our processid variable helps us track which pid belongs to who.
    printf("[%d]stack[%Lf, 0x%p]\n", processid, var_on_the_stack3, &var_on_the_stack3);
    printf("[%d]stack[%d, 0x%p]\n", processid, var_on_the_stack4, &var_on_the_stack4); //shows order output is unpredictable and
    printf("[%d] data[%d, 0x%p]\n", getpid(), var_in_data_segment, &var_in_data_segment); //child receives parent pid when doing pid = fork();

    return 0;
}