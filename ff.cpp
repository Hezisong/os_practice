/*
	first fit algorithm of physics memory manager
	Zisong He
*/
#include<stdio.h>
#include<string.h>

#define MEMORY_SIZE 8000                             //memory size
 
struct block {                                       //memory block node
	int start;
	size_t size;
	block *prev, *next;
	block(int Start, size_t Size, block *Prev, block *Next){
		start = Start;
		size = Size;
		prev = Prev;
		next = Next;
	}
}*header,*tailer;                                     // list for free memory block

static size_t nr_free;                                // number of free memory block

struct pmm_manager {                                  // physics memory manager of first fit algorithm
    const char *name;                                 // pmm_manager's name
    void (*init)(void);                               // initialize internal description&management data structure
                                                      // (free block list, number of free block) of XXX_pmm_manager 
    struct block *(*alloc_pages)(size_t n);           // allocate >=n , depend on the allocation algorithm 
    void (*free_pages)(int base, size_t n);           // free >=n with "base" addr of Page descriptor structures(memlayout.h)
    size_t (*nr_free_pages)(void);                    // return the number of free pages 
    void (*check)(void);                              // check the correctness of XXX_pmm_manager 
};

static void ff_init(void)                             //initialize header, tailer and nr_free 
{
	header = new block(0, 0, NULL, NULL);
	tailer = new block(0, MEMORY_SIZE, NULL, NULL);
	header->next = tailer;
	tailer->prev = header;
	nr_free = 1;	
}

static struct block* ff_alloc_pages(size_t n)         //allocate n pages
{
	if(n < 1)	return NULL;
	block *tmp = header;
	while(tmp != NULL){
		if(tmp->size < n)	tmp = tmp->next;
		else {
			block *node = new block(tmp->start, n, NULL, NULL);
			tmp->start += n;
			tmp->size -= n;
			if(tmp->size == 0){
				tmp->prev->next = tmp->next;
				if(tmp->next != NULL)	tmp->next->prev = tmp->prev;
				delete tmp;
				nr_free--;
			}
			return node;
		}		
	}
	return NULL;
}

static void ff_free_pages(int base, size_t size)
{
	block *node = new block(base, size, NULL, NULL);
	//find right position
	block *current = header;
	while(true){
		if(current->next != NULL){
			if(base < current->next->start)
				break;
			else
				current = current->next;
		} else
			break;
	}
//	printf("base:(%d,%d)\n", base, base+size);
//	printf("current:(%d,%d)\n", current->start, current->size+current->start);
	
	//set merge flag
	int flag = 0;
	if(current->size > 0 && (current->size + current->start) == node->start){//merge current and node 
		flag = 1;
	}
	if(current->next != NULL && current->next->start == (node->start + node->size)){//merge current->next and node
		flag += 2;		
	}
//	printf("flag: %d\n", flag);
	//merge node
	switch(flag){
		case 0:{//insert node
			node->prev = current;
			node->next = current->next;
			if(current->next != NULL)	current->next->prev = node;
			current->next = node;
			nr_free++;
			break;
		}
		case 1:{
			current->size += node->size;
			break;	
		}
		case 2:{
			current->next->size += node->size;
			current->next->start = node->start;
			break;
		}
		case 3:{
			current->size += (node->size + current->next->size);
			if(current->next->next != NULL)	current->next->next->prev = current;
			block *t = current->next;
			current->next = t->next;
			delete t;
			nr_free--;	
			break;
		}
		default:
			break;
	}
}

static size_t ff_nr_free_pages(void){
	return nr_free;
}

static void ff_check(void){
	block *tmp = header->next;
	printf("[");
	while(tmp != NULL){
		printf("(%d, %d) ", tmp->start, tmp->size+tmp->start);
		tmp = tmp->next;
	}
	printf("]\n");
}

const struct pmm_manager ff_pmm_manager = {
    .name = "ff_pmm_manager",
    .init = ff_init,
    .alloc_pages = ff_alloc_pages,
    .free_pages = ff_free_pages,
    .nr_free_pages = ff_nr_free_pages,
    .check = ff_check,
};

int main()
{
	//init
	ff_pmm_manager.init();
	printf("nr_free: %d\n", ff_pmm_manager.nr_free_pages());
	ff_pmm_manager.check();
	
	//alloc 100
	ff_pmm_manager.alloc_pages(100);
	printf("nr_free: %d\n", ff_pmm_manager.nr_free_pages());
	ff_pmm_manager.check();
	
	//free [0,10]
	ff_pmm_manager.free_pages(0,10);
	printf("nr_free: %d\n", ff_pmm_manager.nr_free_pages());
	ff_pmm_manager.check();
	
	//alloc 100
	ff_pmm_manager.alloc_pages(100);
	printf("nr_free: %d\n", ff_pmm_manager.nr_free_pages());
	ff_pmm_manager.check();
	
	//free [100,200]
	ff_pmm_manager.free_pages(100,100);
	printf("nr_free: %d\n", ff_pmm_manager.nr_free_pages());
	ff_pmm_manager.check();
	
	//free[10,100]
	ff_pmm_manager.free_pages(10,90);
	printf("nr_free: %d\n", ff_pmm_manager.nr_free_pages());
	ff_pmm_manager.check();
	
	return 0;
}
