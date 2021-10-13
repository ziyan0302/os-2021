# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sys/wait.h>

// int gettimeofday (struct timeval *tp, struct timezone *tz);
// static int arr[] = {9,9,5,8,3,2,10,7,8,9,9,5,8,3,2,10,7,8,9,9,5,8,3,2,10};
# define amount 10000000
static int arr[amount];


static int a = 2, ans;
static int count = 0;
static int process_num = 2;



int main(void){
    struct timeval start, end;
    // int count;
    pthread_t tid;
    
    for (int i=0; i<amount; i++) arr[i] = i;
    // printf("arr= \n");
    int len = (int)(sizeof(arr)/sizeof(arr[0]));
    int c_s = 0;
    // for (int i =0; i< len; i++) printf("%d ", arr[i]);
    gettimeofday(&start, NULL);

    for (int i = 0; i < process_num; i++){
        pthread_create(&tid, NULL, counting, &i);

    }


    for (int i =0; i<process_num; i++){
        tid = wait(&count);
        
    }

    gettimeofday(&end, NULL);
    printf("count of %d = %d\n", a, ans);    


    
    printf("process time: %ld microseconds\n", ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)));
    return 0;
}

void* counting(void* i){
    printf("do counting");
    int len = (int)(sizeof(arr)/sizeof(arr[0]));
    int c_s = len/process_num * (int* )i;
    // printf("[child %d]c_s: %d\n", getpid(), c_s);

    for (int j = c_s; j<( c_s+len/process_num); j++){
        // printf("[child %d]arr part: %d", getpid(), arr[j]);
        if (arr[j] == a){
            count++;
    pthread_exit();
}