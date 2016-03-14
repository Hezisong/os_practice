#include<stdio.h>

void translate(int vm, int pm)
{
	int pdeIndex = (vm >> 22) & 0x3ff;
	int pteIndex = (vm >> 12) & 0x3ff;
	int offset = vm & 0xfff;
	int pteFn = (pm - offset) >> 12;
	int pte = 3 + (pteFn << 12);
	int pdeFn = pdeIndex - 0x300 + 1;
	int pde = (pdeFn << 12) + 3;
	printf("va 0x%x, pa 0x%08x, pde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x\n", vm, pm, pdeIndex, pde, pteIndex, pte);
}

int main()
{
	translate(0xcd82c07c,  0x0c20907c);
	translate(0xc2265b1f,  0x0d8f1b1f);
	translate(0xcc386bbc,  0x0414cbbc);
	translate(0xc7ed4d57,  0x07311d57);
	translate(0xca6cecc0,  0x0c9e9cc0);
	translate(0xc18072e8,  0x007412e8);
	translate(0xcd5f4b3a,  0x06ec9b3a);
	translate(0xcc324c99,  0x0008ac99);
	translate(0xc7204e52,  0x0b8b6e52);
	translate(0xc3a90293,  0x0f1fd293);
	translate(0xce6c3f32,  0x007d4f32);
	
	return 0;
}
