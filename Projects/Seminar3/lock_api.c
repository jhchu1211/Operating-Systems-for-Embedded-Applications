#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// gcc lock_api.c -lpthread -o tst005
// ./tst005 10000

static int glob = 0;
static int tNum = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void* thread_function(void *args)
{
    int loops = *((int *) args);
    int ix, ret;
    for(ix = 0; ix < loops; ++ix)
    {
        ret = pthread_mutex_lock(&mtx);
        printf("%d", ret);
        printf("lock\t");
        if(ret != 0) 
        {
            printf("free after lock");
            return NULL;
        }
        ++glob;
        if(glob%2 == 0)
        {
            ret = pthread_mutex_trylock(&mtx);
            printf("%d", ret);
            printf("try lock 1\t");
        }
        ret = pthread_mutex_unlock(&mtx);
        printf("%d", ret);
        printf("unlock\t");
        if(ret != 0) 
        {
            printf("free after unlock \n");
            return NULL;
        }
        /*if(glob%2 == 0)
        {
            printf("try lock 2\n");
            ret = pthread_mutex_trylock(&mtx);
            if(ret != 0) 
            {
                printf("free after try lock \n");
                return NULL;
            }
        }*/
    }
    tNum++;
    printf("pthread_create %d done \n", tNum );
    return NULL;
}

int main(int argc, char*argv[])
{
    pthread_t t1, t2, t3;
    int loops, ret;
    loops = (argc > 1) ? atoi(argv[1]) : 1000000;

    ret = pthread_create(&t1, NULL, thread_function, &loops);
    ret = pthread_create(&t2, NULL, thread_function, &loops);
    ret = pthread_create(&t3, NULL, thread_function, &loops);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL); //wait for thread terminate and clean up resources

    printf("total = %d\n", glob);

    return 0;
}