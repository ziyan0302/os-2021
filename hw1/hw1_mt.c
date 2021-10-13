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
    pid_t pid;
    
    for (int i=0; i<amount; i++) arr[i] = i;
    // printf("arr= \n");
    int len = (int)(sizeof(arr)/sizeof(arr[0]));
    int c_s = 0;
    // for (int i =0; i< len; i++) printf("%d ", arr[i]);
    gettimeofday(&start, NULL);

    for (int i = 0; i < process_num; i++){
        pid = fork();

        if (pid == -1){
            perror("fork(): ");
            exit(-1);
        } else if (pid == 0){
            // printf("[child %d]child process %d\n", getpid(), getpid());
            c_s = len/process_num *i;
            // printf("[child %d]c_s: %d\n", getpid(), c_s);

            for (int j = c_s; j<( c_s+len/process_num); j++){
                // printf("[child %d]arr part: %d", getpid(), arr[j]);
                if (arr[j] == a){
                    count++;
            }
            // printf("\n");
                
            }
            // printf("[child %d]count= %d\n", getpid(), count);
            exit(count);
        }


    }


    for (int i =0; i<process_num; i++){
        pid = wait(&count);
        if (pid == -1){
            perror("wait error");
        } else{
            if (WIFSIGNALED(count) != 0){
                printf("[parent]child killed by %d\n", WTERMSIG(count));
            }
            else if (WIFEXITED(count) != 0){
                ans += WEXITSTATUS(count);
            }
        }
    }

    gettimeofday(&end, NULL);
    printf("count of %d = %d\n", a, ans);    


    
    printf("process time: %ld microseconds\n", ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)));
    return 0;
}