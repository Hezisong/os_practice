#include <iostream>
#include <pthread.h>
#include <windows.h>

using namespace std;

int TOTAL = 10;
pthread_cond_t ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t black_thread, white_thread;

void* pickBlack(void *arg)
{
    while(TOTAL > 0){
    	pthread_mutex_lock(&lock);
        if(!(TOTAL&1)){
            pthread_cond_wait(&ready, &lock);
        }
        cout << "Black: pick " << TOTAL << endl;
        TOTAL--;
        pthread_cond_signal(&ready);
    	pthread_mutex_unlock(&lock);
	}
    cout << "Black: exit" << endl;
}

void* pickWhite(void* arg)
{
    while(TOTAL > 0){
    	pthread_mutex_lock(&lock);
        if((TOTAL&1)){
            pthread_cond_wait(&ready, &lock);
        }
        cout << "White: pick " << TOTAL << endl;
        TOTAL--;
        pthread_cond_signal(&ready);
    	pthread_mutex_unlock(&lock);
    }
    cout << "White: exit" << endl;
}

int main()
{
    if(pthread_create(&black_thread, NULL, pickBlack, NULL) != 0){
        cout << "pthread black create error!" << endl;
        return 0;
    }
    if(pthread_create(&white_thread, NULL, pickWhite, NULL) != 0){
        cout << "pthread white create error!" << endl;
        return 0;
    }
    pthread_join(black_thread, NULL);
    pthread_join(white_thread, NULL);
    
    return 0;
}
