#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

int N;
int sum = 0;
pthread_mutex_t lock;

typedef struct range{
    int start;
    int end;
}range;

void *worker(void*arg){
    range* r = (range*)arg;
    for(int i = r->start;i<=r->end;i++){
        if(N%i==0){
            pthread_mutex_lock(&lock);
            sum+=i;
            int j = N/i;
            if(j!=N&&j!=i){
                sum+=j;
            }
            pthread_mutex_unlock(&lock);
        }
    }
    return NULL;
}

int main(int argc, char*argv[]){
    if(argc!=3){
        printf("Usage: %s N P\n",argv[0]);
        return 1;
    }
    N = atoi(argv[1]);
    if(N<=1){
        printf("%d is NOT a Perfect Number\n",N);
        return 0;
    }
    int P = atoi(argv[2]);
    if(P<=0){
        printf("Invalid Number of Threads\n");
        return 1;
    }
    int limit = (int)sqrt(N);
    if(P>limit){
        P = limit;
    }
    int chunk = limit/P;
    pthread_t threads[P];
    range ranges[P];
    pthread_mutex_init(&lock,NULL);
    int start = 1;
    for(int i = 0;i<P;i++){
        ranges[i].start = start;
        if(i==P-1){
            ranges[i].end = limit;
        }
        else{
            ranges[i].end = start+chunk-1;
        }
        start = ranges[i].end+1;
        pthread_create(&threads[i],NULL,worker,&ranges[i]);
    }

    for(int i = 0;i<P;i++){
        pthread_join(threads[i],NULL);
    }

    if(sum==N){
        printf("%d is a Perfect Number\n",N);
    }
    else{
        printf("%d is NOT a Perfect Number\n",N);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}