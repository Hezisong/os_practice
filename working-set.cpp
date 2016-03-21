#include <stdio.h>
#include <memory.h>
#define PHYSICAL_NUM 5
#define WINDOW 4

int access_time[PHYSICAL_NUM];
int exist[PHYSICAL_NUM];
int time = 1;

void flush()
{
	for(int i = 0; i < PHYSICAL_NUM; i++)
	{
		if(exist[i]){
			if(access_time[i] + 3 < time){
				exist[i] = 0;
			}
		}
	}
}

void print()
{
	printf("current condition:\n");
	for(int i = 0; i < PHYSICAL_NUM; i++)
	{
		printf("page: %d, exist: %d, access_time: %d\n", i, exist[i], access_time[i]);
	}
}

int main()
{
	memset(access_time, 0, sizeof(access_time));
	memset(exist, 0, sizeof(exist));
	
	printf("Initial Condition:\n");
	printf("Physical Num: 5\n");
	printf("Window Size: 4\n");
	
	exist[0] = 1; access_time[0] = 0;
	exist[1] = 1; access_time[1] = -1;
	exist[2] = 1; access_time[2] = -2;
	print();
	
	while(1){
		int num;
		printf("Current time: %d, Input access page num[0-4]:", time);
		scanf("%d", &num);
		if(num < 0 || num > 4){
			printf("Incorrect input!\n");
			continue;
		}
		if(exist[num]){
			printf("Hit!\n");
		} else {
			printf("Miss!\n");
		}
		exist[num] = 1; access_time[num] = time;
		flush();
		print();
		time++;
	}
	
	return 0;
}
