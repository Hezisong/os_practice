#include <iostream>

using namespace std;

struct job{
	int id;
	int source;
	int start_time;
	int length;
	int level;
	job *next;
	job *prev;
}*header,*current; 

int tick = 0;

void schedule()
{
	job *tmp = header;
	while((tmp = tmp->next) != NULL){
		if(tmp != current && tmp->start_time <= tick){
			if(current == NULL)
				current = tmp;
			else if(tmp->level > current->level){
				if(tmp->source > 0 && tmp->source == current->source){
					current->level = tmp->level;
				} else {
					current = tmp;
				}
			}
		}
		
	}
}

int main()
{
	current = NULL;
	header = new job();
	header->id = 0; header->source = -1; header->start_time = 0; header->level = 0; header->length = 0; 
	job *j1 = new job();
	j1->id = 1; j1->source = 1; j1->start_time = 0; j1->level = 1; j1->length = 5;
	job *j2 = new job();
	j2->id = 2; j2->source = 0; j2->start_time = 3; j2->level = 2; j2->length = 6;
	job *j3 = new job();
	j3->id = 3; j3->source = 1; j3->start_time = 2; j3->level = 3; j3->length = 4;
	header->next = j1; j1->next = j2; j2->next = j3; j3->next = NULL;
	header->prev = NULL; j1->prev = header; j2->prev = j1; j3->prev = j2;
	
	while(header->next != NULL){
		schedule();
		if(current != NULL){
			current->length--;
			cout << "time: " << tick << " id: " << current->id << " level: " << current->level;
			if(current->length == 0){
				if(current->next != NULL){
					current->next->prev = current->prev;
				}
				current->prev->next = current->next;
				delete [] current;
				current = NULL;
				cout << " ------job Done!";
			}
			cout << endl;
		} else {
			cout << "no job is running" << endl;
		}
		tick++;	
	}
	
		
	return 0;
} 
