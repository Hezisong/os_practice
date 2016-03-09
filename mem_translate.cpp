#include<stdio.h>

int memory[4096];
int pdbr = 0x220;

void load_memory()
{
	FILE *fp = fopen("data.txt", "r");
	int data;
	for(int i = 0; i < 128; i++)
	{
		fscanf(fp, "page %x: ", &data);
		for(int j = 0; j < 32; j++)
		{
			fscanf(fp, "%x", &data);
			memory[i*32 + j] = data;	
		}
		fscanf(fp, "\n");	
	}
}

void translate(int vm)
{
	printf("Virtual Address %x\n", vm);
	int pdeIndex = (vm & 0x6c00) >> 10;
	int pde = memory[(pdbr/32)*32 + pdeIndex];
	int pdeValid = pde >> 7;
	int pdeFn = pde & 0x7f;
	printf("  --> pde index:0x%x pde contents:(valid %x, pfn 0x%x)\n", pdeIndex, pdeValid, pdeFn);
	if(pdeValid == 0){
		printf("    --> Fault (page directory entry not valid)\n");
		return;
	}
	
	int pteIndex = (vm & 0x3e0) >> 5;
	int pte = memory[pdeFn*32 + pteIndex];
	int pteValid = pte >> 7;
	int pteFn = pte & 0x7f;
	printf("    pte index:0x%x pte contents:(valid %x, pfn 0x%x)\n", pteIndex, pteValid, pteFn);
	if(pteValid == 0){
		printf("      --> Fault (page directory entry not valid)\n");
		return;
	}
	
	int phy_address = (pteFn<<5) + (vm&0x1f);
	int value = memory[phy_address];
	printf("      Translates to Physical Address 0x%x --> Value:%x", phy_address, value);
}

int main()
{
	load_memory();
	
	while(1){
		printf("please input Virtual Address: ");
		int vm;
		scanf("%x", &vm);
		translate(vm);
	}
	
	return 0;
}
