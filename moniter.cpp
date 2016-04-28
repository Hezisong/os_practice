#include <iostream>
#include <pthread.h>
#include <windows.h>

using namespace std;

int TOTAL = 10;
pthread_t black_thread, white_thread;
int black_ready = 0;
int white_ready = 1;

void* pickBlack(void* arg)
{
    while(TOTAL > 0){
        while(black_ready == 0);
        cout << "Black: pick " << TOTAL << endl;
        TOTAL--;
        black_ready--;
        white_ready++;
    }
    cout << "Black: exit" << endl;
}

void* pickWhite(void* arg)
{
    while(TOTAL > 0){
        while(white_ready == 0);
        cout << "White: pick " << TOTAL << endl;
        TOTAL--;
        white_ready--;
        black_ready++;
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