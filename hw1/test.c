#include<stdio.h>
#include<pthread.h>

# define amount 10000
static int arr[amount];
static int a = 2, ans;
static int thread_num = 1;

void* myprint(void *x)
{
    int k = *((int *)x);
    printf("\n Thread created.. value of k [%d]\n",k);
    //k =11;
    int len = (int)(sizeof(arr)/sizeof(arr[0]));
    int c_s = len/thread_num * *((int *)x);
    int count = 0;

    for (int j = c_s; j<( c_s+len/thread_num); j++){
        // printf("[child %d]arr part: %d", getpid(), arr[j]);
        if (arr[j] == a){
            count++;
        }
    }

    pthread_exit((void *)k);

}
int main()
{
 pthread_t th1;
 int x =5;
 int *y;
 pthread_create(&th1,NULL,myprint,(void*)&x);
 pthread_join(th1,(void*)&y);
 printf("\n Exit value is [%d]\n",y);
}  