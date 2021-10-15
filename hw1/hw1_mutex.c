# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <pthread.h>



# define amount 100000000
static int arr[amount];


static int a = 50, ans;
// static int count = 0;
static int thread_num = 10;
static int i_create;
static int i_c[amount];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* counting(void* k){
    printf("[child %ld]call lock \n", pthread_self());
    pthread_mutex_lock( &mutex );
    printf("[child %ld]do counting %d\n", pthread_self(), *((int *)k));
    int len = (int)(sizeof(arr)/sizeof(arr[0]));
    int c_s = len/thread_num * *((int *)k);
    int count = 0;
    
    for (int j = c_s; j<( c_s+len/thread_num); j++){
        // printf("%d ", arr[j]);
        if (arr[j] == a){
            count++;
        }
    }

    ans += count;

    printf("[child %ld]ans complete \n", pthread_self());
    pthread_mutex_unlock( &mutex );
    printf("\n");
    printf("[child %ld]count: %d\n", pthread_self(), count);
    pthread_exit((void *)count);
}


int main(int argc, char *argv[]){
    // int datasize = atoi(argv[1]);
    // thread_num = atoi(argv[2]);
    struct timeval start, end;
    void *result = 0;
    pthread_t tid[thread_num];
    
    for (int i=0; i<amount; i++){
        arr[i] = i;
        i_c[i] = i;
    }

    // printf("arr= \n");
    int len = (int)(sizeof(arr)/sizeof(arr[0]));
    int c_s = 0;
    // for (int i =0; i< len; i++) printf("%d ", arr[i]);
    // printf("\n");
    gettimeofday(&start, NULL);

    for (i_create = 0; i_create < thread_num; i_create++){
        printf("[main]i=%d\n", i_create);
        pthread_create(&tid[i_create], NULL, counting, &i_c[i_create]);
        printf("[main]created: %ld %d\n", tid[i_create], i_c[i_create]);
        // pthread_create(&tid, NULL, counting, (void *)&i);

    }

    // printf("[main]wait\n");
    for (int i =0; i<thread_num; i++){
        printf("[main]join\n");
        pthread_join(tid[i], NULL);
        // pthread_join(tid[i], (void*)&result);
        // printf("[main]count: %d\n", result);
        // ans += ((int)result);
    }


    gettimeofday(&end, NULL);
    printf("[main]count of %d = %d\n", a, ans);    


    
    printf("process time: %ld microseconds\n", ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)));
    return 0;
}