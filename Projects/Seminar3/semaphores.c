#include <sys/types.h>

#include <stdlib.h>

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
  
// gcc semaphores.c -lpthread -o tst009

sem_t mutex;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static int ret;

void* thread(void* arg)
{
    //wait
    sem_wait(&mutex); //lock semaphore
    printf("\nSleep\n");
  

    sleep(4);
      
    //signal
    printf("\nWakey Wakey\n");
    sem_post(&mutex); //unlock semaphore
    ret = pthread_cond_signal(&cond);
}
  
void* thread2(void* arg)
{
    printf("start waiting \n");

    ret = pthread_cond_wait(&cond, &mtx);

    printf("done waiting \n");
}

int main()
{
    sem_init(&mutex, 0, 1); //intialize semaphore with sharing capablities and intializes with 1
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread2,NULL);
    pthread_create(&t2,NULL,thread,NULL);
    pthread_join(t2,NULL);
    printf("t2 joined\n");
    pthread_join(t1,NULL);
    printf("t1 joined\n");
    //pthread_join(t2,NULL);
    //printf("t2 joined\n");
    sem_destroy(&mutex);
    return 0;
}