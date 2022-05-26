#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// gcc cond_api.c -lpthread -o tst006

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int ready = 0;
static int done = 0;


static void* thread_produce(void *args)
{
    int ret; 
    for(;done < 100;)
    {
        ret = pthread_mutex_lock(&mtx);
        if(ret != 0) return NULL;
        ++ready;
        printf("+ Lock \n");
        ret = pthread_mutex_unlock(&mtx);
        if(ret != 0) return NULL;
        pthread_cond_signal(&cond);
        if(ret != 0) return NULL;
        usleep(1000 * 100);
    }
    return NULL;
}


static void* thread_consume(void *args)
{
    int ret;
    for(;done < 6;)
    {
        ret = pthread_mutex_lock(&mtx);
        if(ret != 0) return NULL;
        while(ready==0)
        {
            ret = pthread_cond_wait(&cond, &mtx);
            if(ret != 0) return NULL;
        }
        while(ready > 0)
        {
            pthread_cond_signal(&cond);
            --ready;
            ++done;
            printf("-\n");
        }
        ret = pthread_mutex_unlock(&mtx);
        if(ret != 0) return NULL;
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t t1, t2, t3, t4, t5;
    int loops, loops2, ret;
    loops = (argc > 1) ? atoi(argv[1]) : 1000000;
    loops2 = (argc > 1) ? atoi(argv[1]) : 1000000; 
    printf("\n");

    ret = pthread_create(&t1, NULL, thread_consume, &loops);
    ret = pthread_create(&t5, NULL, thread_produce, &loops);

    pthread_join(t1, NULL);
    printf("t1 consume done\n");
    done = 200;
    pthread_join(t5, NULL);
    printf("t5 produce done\n");
    done = 0;

    ret = pthread_create(&t4, NULL, thread_consume, &loops2);
    ret = pthread_create(&t2, NULL, thread_produce, &loops2);
    ret = pthread_create(&t3, NULL, thread_produce, &loops2);
    //ret = pthread_create(&t4, NULL, thread_consume, &loops);
    printf("creation done\n");
    
    
    done = 0;
    pthread_join(t4, NULL);
    printf("t4 consume done\n");
    //printf("consume2 done\n");

    done = 200;
    
    //pthread_join(t5, NULL);
    printf("t2 produce done\n");
    pthread_join(t2, NULL);
    printf("t3 produce done\n");
    pthread_join(t3, NULL);
    //pthread_join(t5, NULL);
    //pthread_join(t4, NULL);
    
    return 0;
}