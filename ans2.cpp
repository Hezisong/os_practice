#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <cstring>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
int N = 10;
pthread_mutex_t myLock;
pthread_cond_t myCondB;
pthread_cond_t myCondW;
int B_READY=0;
int W_READY=1;

void* BLACK(void* argv){
    int picked = 0;
    char indent = *(char*)argv;
    while (N > 0){
		while(B_READY==0);
		printf("%cpick %d\n", indent, N);
        N--;
		--B_READY;
		++W_READY;
       
    }
    printf("%cexit\n", indent);
	return 0;
}

void* WHITE(void* argv){
    int picked = 0;
    char indent = *(char*)argv;
    while (N > 1){
		while(W_READY==0);
        printf("%cpick %d\n", indent, N);
		--N;
		--W_READY;
		++B_READY;
    }
    printf("%cexit\n", indent);
	return 0;
}

int main(int argc, char** argv) {
	srand((unsigned)time(NULL));

    pthread_cond_init(&myCondB, NULL);
    pthread_cond_init(&myCondW, NULL);
    pthread_mutex_init(&myLock, NULL);
    
	pthread_t pW, pB;


	int st_time = 0;

    printf("WHITE\t");
    printf("BLACK\t");
	printf("\n");

    
	char indentW = ' ';
    pthread_create(&pW, NULL, WHITE, &indentW);
    char indentB = '\t';
    pthread_create(&pB, NULL, BLACK, &indentB);
    pthread_join(pW, NULL);
    pthread_join(pB, NULL);	
	return 0;
}
