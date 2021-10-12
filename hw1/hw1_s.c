# include <stdio.h>
# include <sys/time.h>

int arr[25];
// int gettimeofday (struct timeval *tp, struct timezone *tz);


int main(void){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    int arr[] = {9,9,5,8,3,2,10,7,8,9,9,5,8,3,2,10,7,8,9,9,5,8,3,2,10};
    int a = 9;
    int count = 0;
    // printf("a = %d\n", a);
    // for (int i = 0; i<=24; i++){
    //     printf("arr[%d] = %d\n", i, arr[i]);
    // }

    for (int i = 0; i<=24; i++){
        if (arr[i] == a){
            count++;
        }
    }

    printf("count of %d = %d\n", a, count);
    


    gettimeofday(&end, NULL);
    printf("process time: %ld microseconds\n", ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)));
    return 0;
}