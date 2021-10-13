# include <stdio.h>
# include <sys/time.h>

# define amount 10000000
static int arr[amount];

// int gettimeofday (struct timeval *tp, struct timezone *tz);


int main(void){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i=0; i<amount; i++) arr[i] = i;
    // printf("arr= \n");
    int len = (int)(sizeof(arr)/sizeof(arr[0]));
    int a = 9;
    int count = 0;
    // printf("a = %d\n", a);
    // for (int i = 0; i<=24; i++){
    //     printf("arr[%d] = %d\n", i, arr[i]);
    // }

    for (int i = 0; i<=len; i++){
        if (arr[i] == a){
            count++;
        }
    }

    printf("count of %d = %d\n", a, count);
    


    gettimeofday(&end, NULL);
    printf("process time: %ld microseconds\n", ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)));
    return 0;
}