#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Vector{
	int x0;
	int x1;
	int x2;
	int x3;
};

void showVectror(struct Vector v);

struct Vector v1;
struct Vector v2;
struct Vector wynik;

int a0, a1, a2, a3;
int b0, b1, b2, b3;
int w0, w1, w2, w3;

double addSIMD(){
	v1.x0 = rand()%1000 + 1;
	v1.x1 = 2;
	v1.x2 = 3;
	v1.x3 = 4;

	v2.x0 = 3;
	v2.x1 = 4;
	v2.x2 = 5;
	v2.x3 = 5;

	wynik.x0 = 0;
	wynik.x1 = 0;
	wynik.x2 = 0;
	wynik.x3 = 0;

	printf("%d, %d, %d, %d \n", wynik.x0, wynik.x1,  wynik.x2, wynik.x3);

	clock_t start = clock();

	asm(
		"movups	%1, %%xmm0 \n"
		"movups	%2, %%xmm1 \n"
		"addps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		: "=g" (wynik)
		: "g"(v1), "g"(v2)
		: "%xmm0", "%xmm1"
	);

	clock_t stop = clock();

	printf("%d, %d, %d, %d \n", wynik.x0, wynik.x1,  wynik.x2, wynik.x3);
	return (double)(stop - start) / CLOCKS_PER_SEC;
}

double addSISD(){
	v1.x0 = rand()%1000 + 1;
	v1.x1 = 2;
	v1.x2 = 3;
	v1.x3 = 4;

	v2.x0 = 3;
	v2.x1 = 4;
	v2.x2 = 5;
	v2.x3 = 5;

	wynik.x0 = 0;
	wynik.x1 = 0;
	wynik.x2 = 0;
	wynik.x3 = 0;

	a0 = v1.x0;
	a1 = v1.x1;
	a2 = v1.x2;
	a3 = v1.x3;

	b0 = v2.x0;
	b1 = v2.x1;
	b2 = v2.x2;
	b3 = v2.x3;

	clock_t start = clock();

	asm(
		"mov a0, %%eax \n"
		"mov b0, %%ebx \n"
		"add %%ebx, %%eax \n"
		"mov %%eax, w0 \n"
		"mov a1, %%eax \n"
		"mov b1, %%ebx \n"
		"add %%ebx, %%eax \n"
		"mov %%eax, w1 \n"
		"mov a2, %%eax \n"
		"mov b2, %%ebx \n"
		"add %%ebx, %%eax \n"
		"mov %%eax, w2 \n"
		"mov a3, %%eax \n"
		"mov b3, %%ebx \n"
		"add %%ebx, %%eax \n"
		"mov %%eax, w3 \n"
		:
		: 
		: "%eax", "%ebx"
	);

	wynik.x0 = w0;
	wynik.x1 = w1;
	wynik.x2 = w2;
	wynik.x3 = w3;

	clock_t stop = clock();
	printf("%d, %d, %d, %d \n", wynik.x0, wynik.x1,  wynik.x2, wynik.x3);

	return (double)(stop - start) / CLOCKS_PER_SEC;
}

int main(void){
	srand(time(NULL));

	//printf("size int: %d", (int)sizeof(int));
	//printf("size vec: %d", (int)sizeof(v1));
	
	FILE *f = fopen("wynik.txt", "w");

	double totalTime = 0;
	
	//for(int i = 0; i < 2048; i++){
		totalTime += addSIMD();
	//}

	printf("%f \n", totalTime);

	addSISD();
	

	//fprintf(f, "%d", wynik.x0);

	
	return 0;

}

