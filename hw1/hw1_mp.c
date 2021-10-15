# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sys/wait.h>

# define amount 100000000
static int arr[amount];


static int a = 50, ans;
static int count = 0;
static int process_num = 12;
static u_int32_t period[10];

int main(int argc, char *argv[]){
    // process_num = atoi(argv[1]);
    // int datasize = atoi(argv[2]);
    struct timeval start, end;
    pid_t pid;
    FILE *F ;
    F = fopen("multiprocess_int.csv","a");
    if(F == NULL) printf("open file fail QQ\n");

    
    for (int i=0; i<amount; i++) arr[i] = i;
    // printf("arr= \n");
    int len = (int)(sizeof(arr)/sizeof(arr[0]));
    int c_s = 0;
    // for (int i =0; i< len; i++) printf("%d ", arr[i]);
    

    for (int t = 0; t<10; t++){
        gettimeofday(&start, NULL);
        ans = 0;
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
        period[t] = (end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec);
    }
    u_int64_t period_total;
    u_int64_t len_period = (u_int64_t)(sizeof(period)/sizeof(period[0]));
    int len_p = (int)(sizeof(period)/sizeof(period[0]));
    printf("len_p = %d\n", len_p);
    for (int i = 0; i<len_p; i++){
        // printf("%u\n", period[i]);
        period_total +=period[i];
    }
    u_int64_t aver_period = period_total/len_period;
    printf("len_period: %lu\n", len_period);
    printf("period_total: %lu\n", period_total);
    printf("aver period: %lu\n", aver_period);
    for (int i = 0; i<10; i++){
    // fprintf(F, "%u \n", period[i]);
    }
    fprintf(F, "%d, %d, %lu \n",amount, process_num, aver_period);
    fclose(F);
    return 0;
}