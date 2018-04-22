#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Vector{
	int x3;
	int x2;
	int x1;
	int x0;
};

int a0, a1, a2, a3;
int b0, b1, b2, b3;
int w0, w1, w2, w3;

struct Vector wek1;
struct Vector wek2;
struct Vector wyn;
struct Vector wynik;

double addSIMD(){

	clock_t start = clock();

	asm(
		"movups	%1, %%xmm0 \n"
		"movups	%2, %%xmm1 \n"
		"addps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		: "=g" (wynik)
		: "g"(wek1), "g"(wek2)
		: "%xmm0", "%xmm1"
	);
	
	clock_t stop = clock();
	return (double)(stop - start) / CLOCKS_PER_SEC;
}

double subSIMD(){
	
	clock_t start = clock();
	
	asm(
		"movups	%1, %%xmm0 \n"
		"movups	%2, %%xmm1 \n"
		"subps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		: "=g" (wynik)
		: "g"(wek1), "g"(wek2)
		: "%xmm0", "%xmm1"
	);
	
	clock_t stop = clock();
	return (double)(stop - start) / CLOCKS_PER_SEC;
}

double mulSIMD(){
	
	clock_t start = clock();
	
	asm(
		"movups	%1, %%xmm0 \n"
		"movups	%2, %%xmm1 \n"
		"mulps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		: "=g" (wynik)
		: "g"(wek1), "g"(wek2)
		: "%xmm0", "%xmm1"
	);
	
	clock_t stop = clock();
	return (double)(stop - start) / CLOCKS_PER_SEC;
}

double divSIMD(){
	
	clock_t start = clock();
	
	asm(
		"movups	%1, %%xmm0 \n"
		"movups	%2, %%xmm1 \n"
		"divps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		: "=g" (wynik)
		: "g"(wek1), "g"(wek2)
		: "%xmm0", "%xmm1"
	);
	
	clock_t stop = clock();
	return (double)(stop - start) / CLOCKS_PER_SEC;
}

double addSISD(){
	a0 = wek1.x0;
	a1 = wek1.x1;
	a2 = wek1.x2;
	a3 = wek1.x3;

	b0 = wek2.x0;
	b1 = wek2.x1;
	b2 = wek2.x2;
	b3 = wek2.x3;

	//cos zwraca zle wyniki dla X2
	/*asm(
		"mov %4, %%eax \n"
		"mov %5, %%ebx \n"
		"add %%ebx, %%eax \n"
		"mov %%eax, %0 \n"
		"mov %6, %%eax \n"
		"mov %7, %%ebx \n"
		"add %%ebx, %%eax \n"
		"mov %%eax, %0 \n"
		"mov %8, %%eax \n"
		"mov %9, %%ebx \n"
		"add %%ebx, %%eax \n"
		"mov %%eax, %0 \n"
		"mov %10, %%eax \n"
		"mov %11, %%ebx \n"
		"add %%ebx, %%eax \n"
		"mov %%eax, %3 \n"
		: "=g" (wynik.x3), "=g" (wynik.x2), "=g" (wynik.x1), "=g" (wynik.x0)
		: "g"(v1.x3), "g"(v2.x3), "g"(v1.x2), "g"(v2.x2), "g"(v1.x1), "g"(v2.x1), "g"(v1.x0), "g"(v2.x0)
		: "%eax", "%ebx"
	);*/
	//Dla =g bedzie to kolejna %0, %1, %2, %3
	//Dla g bedzie to 4 -> 11
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

	clock_t stop = clock();
	
	wynik.x0 = w0;
	wynik.x1 = w1;
	wynik.x2 = w2;
	wynik.x3 = w3;

	return (double)(stop - start) / CLOCKS_PER_SEC;
}

double subSISD(){
	a0 = wek1.x0;
	a1 = wek1.x1;
	a2 = wek1.x2;
	a3 = wek1.x3;

	b0 = wek2.x0;
	b1 = wek2.x1;
	b2 = wek2.x2;
	b3 = wek2.x3;
	
	clock_t start = clock();
	
	asm(
		"mov a0, %%eax \n"
		"mov b0, %%ebx \n"
		"sub %%ebx, %%eax \n"
		"mov %%eax, w0 \n"
		"mov a1, %%eax \n"
		"mov b1, %%ebx \n"
		"sub %%ebx, %%eax \n"
		"mov %%eax, w1 \n"
		"mov a2, %%eax \n"
		"mov b2, %%ebx \n"
		"sub %%ebx, %%eax \n"
		"mov %%eax, w2 \n"
		"mov a3, %%eax \n"
		"mov b3, %%ebx \n"
		"sub %%ebx, %%eax \n"
		"mov %%eax, w3 \n"
		:
		: 
		: "%eax", "%ebx"
	);
	
	clock_t stop = clock();

	wynik.x0 = w0;
	wynik.x1 = w1;
	wynik.x2 = w2;
	wynik.x3 = w3;

	return (double)(stop - start) / CLOCKS_PER_SEC;
}

double mulSISD(){
	a0 = wek1.x0;
	a1 = wek1.x1;
	a2 = wek1.x2;
	a3 = wek1.x3;

	b0 = wek2.x0;
	b1 = wek2.x1;
	b2 = wek2.x2;
	b3 = wek2.x3;
	
	clock_t start = clock();
	
	asm(
		"mov a0, %%eax \n"
		"mov b0, %%ebx \n"
		"imul %%ebx, %%eax \n"
		"mov %%eax, w0 \n"
		"mov a1, %%eax \n"
		"mov b1, %%ebx \n"
		"imul %%ebx, %%eax \n"
		"mov %%eax, w1 \n"
		"mov a2, %%eax \n"
		"mov b2, %%ebx \n"
		"imul %%ebx, %%eax \n"
		"mov %%eax, w2 \n"
		"mov a3, %%eax \n"
		"mov b3, %%ebx \n"
		"imul %%ebx, %%eax \n"
		"mov %%eax, w3 \n"
		:
		: 
		: "%eax", "%ebx"
	);
	
	clock_t stop = clock();

	wynik.x0 = w0;
	wynik.x1 = w1;
	wynik.x2 = w2;
	wynik.x3 = w3;

	return (double)(stop - start) / CLOCKS_PER_SEC;
}

double divSISD(){
	a0 = wek1.x0;
	a1 = wek1.x1;
	a2 = wek1.x2;
	a3 = wek1.x3;

	b0 = wek2.x0;
	b1 = wek2.x1;
	b2 = wek2.x2;
	b3 = wek2.x3;
	
	clock_t start = clock();

	asm(
		"mov a0, %%eax \n"
		"movl b0, %%ebx \n"
		"xor %%edx, %%edx \n"
		"idiv %%ebx, %%eax \n"
		"mov %%eax, w0 \n"
		"mov a1, %%eax \n"
		"mov b1, %%ebx \n"
		"xor %%edx, %%edx \n"
		"idiv %%ebx, %%eax \n"
		"mov %%eax, w1 \n"
		"mov a2, %%eax \n"
		"mov b2, %%ebx \n"
		"xor %%edx, %%edx \n"
		"idiv %%ebx, %%eax \n"
		"mov %%eax, w2 \n"
		"mov a3, %%eax \n"
		"mov b3, %%ebx \n"
		"xor %%edx, %%edx \n"
		"idiv %%ebx, %%eax \n"
		"mov %%eax, w3 \n"
		:
		: 
		: "%eax", "%ebx"
	);
	
	clock_t stop = clock();

	wynik.x0 = w0;
	wynik.x1 = w1;
	wynik.x2 = w2;
	wynik.x3 = w3;

	return (double)(stop - start) / CLOCKS_PER_SEC;
}

int main(void){
	srand(time(NULL));
	
	FILE *f = fopen("wynikAsm.txt", "w");

	double totalTime = 0;
	
	//printf("%d, %d, %d, %d \n", wyn.x3, wyn.x2, wyn.x1, wyn.x0);
	/*
	wek1.x3 = 1;
	wek1.x2 = 1;
	wek1.x1 = 1;
	wek1.x0 = 1;

	wek2.x3 = 2;
	wek2.x2 = 1;
	wek2.x1 = 1;
	wek2.x0 = 1;
	
	clock_t start = clock();
	
	wyn = divSISD(wek1, wek2);
	
	clock_t stop = clock();
	totalTime += (double)(stop - start) / CLOCKS_PER_SEC;
	
	//printf("%f", totalTime);
	
	printf("%d, %d, %d, %d \n", wyn.x3, wyn.x2, wyn.x1, wyn.x0);*/
	
	totalTime = 0;
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 2048*k; j++){
				wek1.x3 = rand()%100000 + 1; // Wygenerowanie dodatnich liczb calkowitych za wyjatkiem zera
				wek1.x2 = rand()%100000 + 1;
				wek1.x1 = rand()%100000 + 1;
				wek1.x0 = rand()%100000 + 1;

				wek2.x3 = rand()%100000 + 1;
				wek2.x2 = rand()%100000 + 1;
				wek2.x1 = rand()%100000 + 1;
				wek2.x0 = rand()%100000 + 1;
				//printf("%d, %d, %d, %d \n", wek1.x3, wek1.x2, wek1.x1, wek1.x0);
				//printf("%d, %d, %d, %d \n", wek2.x3, wek2.x2, wek2.x1, wek2.x0);
		
				totalTime += addSIMD();
			}
		}
	
		totalTime /= 100.0;

		printf("add SIMD: Sredni czas dodawania dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "add SIMD: Sredni czas dodawania dla %d liczb: %f \n", k*2048, totalTime);
		totalTime = 0;
	}
	
	totalTime = 0;
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 2048*k; j++){
				wek1.x3 = rand()%100000 + 1; // Wygenerowanie dodatnich liczb calkowitych za wyjatkiem zera
				wek1.x2 = rand()%100000 + 1;
				wek1.x1 = rand()%100000 + 1;
				wek1.x0 = rand()%100000 + 1;

				wek2.x3 = rand()%100000 + 1;
				wek2.x2 = rand()%100000 + 1;
				wek2.x1 = rand()%100000 + 1;
				wek2.x0 = rand()%100000 + 1;
				//printf("%d, %d, %d, %d \n", wek1.x3, wek1.x2, wek1.x1, wek1.x0);
				//printf("%d, %d, %d, %d \n", wek2.x3, wek2.x2, wek2.x1, wek2.x0);

				totalTime += subSIMD();
				
			}
		}
	
		totalTime /= 100.0;

		printf("sub SIMD: Sredni czas odejmowania dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "sub SIMD: Sredni czas odejmowania dla %d liczb: %f \n", k*2048, totalTime);
		totalTime = 0;
	}
	
	totalTime = 0;
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 2048*k; j++){
				wek1.x3 = rand()%100000 + 1; // Wygenerowanie dodatnich liczb calkowitych za wyjatkiem zera
				wek1.x2 = rand()%100000 + 1;
				wek1.x1 = rand()%100000 + 1;
				wek1.x0 = rand()%100000 + 1;

				wek2.x3 = rand()%100000 + 1;
				wek2.x2 = rand()%100000 + 1;
				wek2.x1 = rand()%100000 + 1;
				wek2.x0 = rand()%100000 + 1;
				//printf("%d, %d, %d, %d \n", wek1.x3, wek1.x2, wek1.x1, wek1.x0);
				//printf("%d, %d, %d, %d \n", wek2.x3, wek2.x2, wek2.x1, wek2.x0);
		
				totalTime += mulSIMD();

			}
		}
	
		totalTime /= 100.0;

		printf("mul SIMD: Sredni czas mnozenia dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "mul SIMD: Sredni czas mnozenia dla %d liczb: %f \n", k*2048, totalTime);
		totalTime = 0;
	}
	
	totalTime = 0;
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 2048*k; j++){
				wek1.x3 = rand()%100000 + 1; // Wygenerowanie dodatnich liczb calkowitych za wyjatkiem zera
				wek1.x2 = rand()%100000 + 1;
				wek1.x1 = rand()%100000 + 1;
				wek1.x0 = rand()%100000 + 1;

				wek2.x3 = rand()%100000 + 1;
				wek2.x2 = rand()%100000 + 1;
				wek2.x1 = rand()%100000 + 1;
				wek2.x0 = rand()%100000 + 1;
				//printf("%d, %d, %d, %d \n", wek1.x3, wek1.x2, wek1.x1, wek1.x0);
				//printf("%d, %d, %d, %d \n", wek2.x3, wek2.x2, wek2.x1, wek2.x0);
				
				totalTime += divSIMD();
		
			}
		}
	
		totalTime /= 100.0;

		printf("div SIMD: Sredni czas dzielenia dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "div SIMD: Sredni czas dzielenia dla %d liczb: %f \n", k*2048, totalTime);
		totalTime = 0;
	}
	
	totalTime = 0;
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 2048*k; j++){
				wek1.x3 = rand()%100000 + 1; // Wygenerowanie dodatnich liczb calkowitych za wyjatkiem zera
				wek1.x2 = rand()%100000 + 1;
				wek1.x1 = rand()%100000 + 1;
				wek1.x0 = rand()%100000 + 1;

				wek2.x3 = rand()%100000 + 1;
				wek2.x2 = rand()%100000 + 1;
				wek2.x1 = rand()%100000 + 1;
				wek2.x0 = rand()%100000 + 1;
				//printf("%d, %d, %d, %d \n", wek1.x3, wek1.x2, wek1.x1, wek1.x0);
				//printf("%d, %d, %d, %d \n", wek2.x3, wek2.x2, wek2.x1, wek2.x0);
				
				totalTime += addSISD();
		
			}
		}
	
		totalTime /= 100.0;

		printf("add SISD: Sredni czas dodawania dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "add SISD: Sredni czas dodawania dla %d liczb: %f \n", k*2048, totalTime);
		totalTime = 0;
	}
	
	totalTime = 0;
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 2048*k; j++){
				wek1.x3 = rand()%100000 + 1; // Wygenerowanie dodatnich liczb calkowitych za wyjatkiem zera
				wek1.x2 = rand()%100000 + 1;
				wek1.x1 = rand()%100000 + 1;
				wek1.x0 = rand()%100000 + 1;

				wek2.x3 = rand()%100000 + 1;
				wek2.x2 = rand()%100000 + 1;
				wek2.x1 = rand()%100000 + 1;
				wek2.x0 = rand()%100000 + 1;
				//printf("%d, %d, %d, %d \n", wek1.x3, wek1.x2, wek1.x1, wek1.x0);
				//printf("%d, %d, %d, %d \n", wek2.x3, wek2.x2, wek2.x1, wek2.x0);
				
				totalTime += subSISD();
		
			}
		}
	
		totalTime /= 100.0;

		printf("sub SISD: Sredni czas odejmowania dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "sub SISD: Sredni czas odejmowania dla %d liczb: %f \n", k*2048, totalTime);
		totalTime = 0;
	}
	
	totalTime = 0;
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 2048*k; j++){
				wek1.x3 = rand()%100000 + 1; // Wygenerowanie dodatnich liczb calkowitych za wyjatkiem zera
				wek1.x2 = rand()%100000 + 1;
				wek1.x1 = rand()%100000 + 1;
				wek1.x0 = rand()%100000 + 1;

				wek2.x3 = rand()%100000 + 1;
				wek2.x2 = rand()%100000 + 1;
				wek2.x1 = rand()%100000 + 1;
				wek2.x0 = rand()%100000 + 1;
				//printf("%d, %d, %d, %d \n", wek1.x3, wek1.x2, wek1.x1, wek1.x0);
				//printf("%d, %d, %d, %d \n", wek2.x3, wek2.x2, wek2.x1, wek2.x0);
		
				totalTime += mulSISD();
			}
		}
		
		totalTime /= 100.0;

		printf("mul SISD: Sredni czas mnozenia dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "mul SISD: Sredni czas mnozenia dla %d liczb: %f \n", k*2048, totalTime);
		totalTime = 0;
	}
	
	totalTime = 0;
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 2048*k; j++){
				wek1.x3 = rand()%100000 + 1; // Wygenerowanie dodatnich liczb calkowitych za wyjatkiem zera
				wek1.x2 = rand()%100000 + 1;
				wek1.x1 = rand()%100000 + 1;
				wek1.x0 = rand()%100000 + 1;

				wek2.x3 = rand()%100000 + 1;
				wek2.x2 = rand()%100000 + 1;
				wek2.x1 = rand()%100000 + 1;
				wek2.x0 = rand()%100000 + 1;
				//printf("%d, %d, %d, %d \n", wek1.x3, wek1.x2, wek1.x1, wek1.x0);
				//printf("%d, %d, %d, %d \n", wek2.x3, wek2.x2, wek2.x1, wek2.x0);
				
				totalTime += divSISD();
			}
		}
		
		totalTime /= 100.0;
		
		printf("div SISD: Sredni czas dzielenia dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "div SISD: Sredni czas dzielenia dla %d liczb: %f \n", k*2048, totalTime);
		totalTime = 0;
	} 
	
	
	return 0;

}

