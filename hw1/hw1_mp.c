# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sys/wait.h>

int arr[25];
// int gettimeofday (struct timeval *tp, struct timezone *tz);


int main(void){
    struct timeval start, end;
    pid_t pid;
    gettimeofday(&start, NULL);
    printf("seconds: %ld, microseconds: %ld\n", start.tv_sec, start.tv_usec);
    int arr[] = {9,9,5,8,3,2,10,7,8,9,9,5,8,3,2,10,7,8,9,9,5,8,3,2,10};
    int a = 9;
    int count = 0;
    int exit_status;

    // for (int i = 0; i<=24; i++){
    //     if (arr[i] == a){
    //         count++;
    //     }
    // }

    pid = fork();

    if (pid == -1){
        perror("fork()");
        exit(-1);
    } else if (pid == 0){
        printf("child process %d\n", getpid());
            for (int i = 0; i<=24; i++){
            if (arr[i] == a){
                count++;
            }
            
        }
        exit_status = count;
        printf("exit_status: %d\n", exit_status);
        return exit_status;
    } else if (pid > 0){
        printf("parent process %d\n", getpid());
        printf("child pid = %d\n", pid);
        wait(&exit_status);
        printf("child(%d)'s exit status: %d\n", pid, exit_status);
    }

    printf("count of %d = %d\n", a, count);
    


    gettimeofday(&end, NULL);
    printf("process time: %ld microseconds\n", ((end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec)));
    return 0;
}