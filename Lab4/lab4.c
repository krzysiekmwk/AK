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

struct Vector addSIMD(struct Vector v1, struct Vector v2){
	struct Vector wynik;

	asm(
		"movups	%1, %%xmm0 \n"
		"movups	%2, %%xmm1 \n"
		"addps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		: "=g" (wynik)
		: "g"(v1), "g"(v2)
		: "%xmm0", "%xmm1"
	);
	
	return wynik;
}

struct Vector subSIMD(struct Vector v1, struct Vector v2){
	struct Vector wynik;

	asm(
		"movups	%1, %%xmm0 \n"
		"movups	%2, %%xmm1 \n"
		"subps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		: "=g" (wynik)
		: "g"(v1), "g"(v2)
		: "%xmm0", "%xmm1"
	);
	
	return wynik;
}

struct Vector mulSIMD(struct Vector v1, struct Vector v2){
	struct Vector wynik;

	asm(
		"movups	%1, %%xmm0 \n"
		"movups	%2, %%xmm1 \n"
		"mulps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		: "=g" (wynik)
		: "g"(v1), "g"(v2)
		: "%xmm0", "%xmm1"
	);
	
	return wynik;
}

struct Vector divSIMD(struct Vector v1, struct Vector v2){
	struct Vector wynik;

	asm(
		"movups	%1, %%xmm0 \n"
		"movups	%2, %%xmm1 \n"
		"divps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		: "=g" (wynik)
		: "g"(v1), "g"(v2)
		: "%xmm0", "%xmm1"
	);
	
	return wynik;
}

struct Vector addSISD(struct Vector v1, struct Vector v2){
	struct Vector wynik;
	
	a0 = v1.x0;
	a1 = v1.x1;
	a2 = v1.x2;
	a3 = v1.x3;

	b0 = v2.x0;
	b1 = v2.x1;
	b2 = v2.x2;
	b3 = v2.x3;

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

	return wynik;
}

struct Vector subSISD(struct Vector v1, struct Vector v2){
	struct Vector wynik;
	
	a0 = v1.x0;
	a1 = v1.x1;
	a2 = v1.x2;
	a3 = v1.x3;

	b0 = v2.x0;
	b1 = v2.x1;
	b2 = v2.x2;
	b3 = v2.x3;
	
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

	wynik.x0 = w0;
	wynik.x1 = w1;
	wynik.x2 = w2;
	wynik.x3 = w3;

	return wynik;
}

struct Vector mulSISD(struct Vector v1, struct Vector v2){
	struct Vector wynik;
	
	a0 = v1.x0;
	a1 = v1.x1;
	a2 = v1.x2;
	a3 = v1.x3;

	b0 = v2.x0;
	b1 = v2.x1;
	b2 = v2.x2;
	b3 = v2.x3;
	
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

	wynik.x0 = w0;
	wynik.x1 = w1;
	wynik.x2 = w2;
	wynik.x3 = w3;

	return wynik;
}

struct Vector divSISD(struct Vector v1, struct Vector v2){
	struct Vector wynik;
	
	a0 = v1.x0;
	a1 = v1.x1;
	a2 = v1.x2;
	a3 = v1.x3;

	b0 = v2.x0;
	b1 = v2.x1;
	b2 = v2.x2;
	b3 = v2.x3;
	
	//Generuje 'blad w obliczeniach zmiennoprzcinkowych (zrzut pamieci)'
	asm(
		"mov a0, %%eax \n"
		"mov b0, %%ebx \n"
		"idiv %%ebx, %%eax \n"
		"mov %%eax, w0 \n"
		"mov a1, %%eax \n"
		"mov b1, %%ebx \n"
		"idiv %%ebx, %%eax \n"
		"mov %%eax, w1 \n"
		"mov a2, %%eax \n"
		"mov b2, %%ebx \n"
		"idiv %%ebx, %%eax \n"
		"mov %%eax, w2 \n"
		"mov a3, %%eax \n"
		"mov b3, %%ebx \n"
		"idiv %%ebx, %%eax \n"
		"mov %%eax, w3 \n"
		:
		: 
		: "%eax", "%ebx"
	);

	wynik.x0 = w0;
	wynik.x1 = w1;
	wynik.x2 = w2;
	wynik.x3 = w3;

	return wynik;
}

int main(void){
	srand(time(NULL));
	
	FILE *f = fopen("wynik.txt", "w");

	double totalTime = 0;
	
	struct Vector wek1;
	struct Vector wek2;
	struct Vector wyn;
	/*
	//printf("%d, %d, %d, %d \n", wyn.x3, wyn.x2, wyn.x1, wyn.x0);
	
	wek1.x3 = 2;
	wek1.x2 = 2;
	wek1.x1 = 2;
	wek1.x0 = 2;

	wek2.x3 = 2;
	wek2.x2 = 2;
	wek2.x1 = 2;
	wek2.x0 = 2;
	
	clock_t start = clock();
	
	wyn = divSISD(wek1, wek2);
	
	clock_t stop = clock();
	totalTime += (double)(stop - start) / CLOCKS_PER_SEC;
	
	//printf("%f", totalTime);
	
	printf("%d, %d, %d, %d \n", wyn.x3, wyn.x2, wyn.x1, wyn.x0);*/
	
	
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 10; i++){
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
				
				clock_t start = clock();
		
				wyn = addSIMD(wek1, wek2);
				
				clock_t stop = clock();
				totalTime += (double)(stop - start) / CLOCKS_PER_SEC;
		
			}
		}
	
		totalTime /= 10.0;

		printf("add SIMD: Sredni czas dodawania dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "add SIMD: Sredni czas dodawania dla %d liczb: %f \n", k*2048, totalTime);
	}
	
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 10; i++){
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
				
				clock_t start = clock();
		
				wyn = subSIMD(wek1, wek2);
				
				clock_t stop = clock();
				totalTime += (double)(stop - start) / CLOCKS_PER_SEC;
		
			}
		}
	
		totalTime /= 10.0;

		printf("sub SIMD: Sredni czas odejmowania dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "sub SIMD: Sredni czas odejmowania dla %d liczb: %f \n", k*2048, totalTime);
	}
	
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 10; i++){
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
				
				clock_t start = clock();
		
				wyn = mulSIMD(wek1, wek2);
				
				clock_t stop = clock();
				totalTime += (double)(stop - start) / CLOCKS_PER_SEC;
		
			}
		}
	
		totalTime /= 10.0;

		printf("mul SIMD: Sredni czas mnozenia dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "mul SIMD: Sredni czas mnozenia dla %d liczb: %f \n", k*2048, totalTime);
	}
	
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 10; i++){
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
				
				clock_t start = clock();
		
				wyn = divSIMD(wek1, wek2);
				
				clock_t stop = clock();
				totalTime += (double)(stop - start) / CLOCKS_PER_SEC;
		
			}
		}
	
		totalTime /= 10.0;

		printf("div SIMD: Sredni czas dzielenia dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "div SIMD: Sredni czas dzielenia dla %d liczb: %f \n", k*2048, totalTime);
	}
	
	
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 10; i++){
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
				
				clock_t start = clock();
		
				wyn = addSISD(wek1, wek2);
				
				clock_t stop = clock();
				totalTime += (double)(stop - start) / CLOCKS_PER_SEC;
		
			}
		}
	
		totalTime /= 10.0;

		printf("add SISD: Sredni czas dodawania dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "add SISD: Sredni czas dodawania dla %d liczb: %f \n", k*2048, totalTime);
	}
	
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 10; i++){
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
				
				clock_t start = clock();
		
				wyn = subSISD(wek1, wek2);
				
				clock_t stop = clock();
				totalTime += (double)(stop - start) / CLOCKS_PER_SEC;
		
			}
		}
	
		totalTime /= 10.0;

		printf("sub SISD: Sredni czas odejmowania dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "sub SISD: Sredni czas odejmowania dla %d liczb: %f \n", k*2048, totalTime);
	}
	
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 10; i++){
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
				
				clock_t start = clock();
		
				wyn = mulSISD(wek1, wek2);
				
				clock_t stop = clock();
				totalTime += (double)(stop - start) / CLOCKS_PER_SEC;
		
			}
		}
	
		totalTime /= 10.0;

		printf("mul SISD: Sredni czas mnozenia dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "mul SISD: Sredni czas mnozenia dla %d liczb: %f \n", k*2048, totalTime);
	}
	
	/*
	for(int k = 1; k <= 4; k *= 2){
		for(int i = 0; i < 10; i++){
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
				
				clock_t start = clock();
		
				wyn = divSISD(wek1, wek2);
				
				clock_t stop = clock();
				totalTime += (double)(stop - start) / CLOCKS_PER_SEC;
		
			}
		}
	
		totalTime /= 10.0;

		printf("div SISD: Sredni czas dzielenia dla %d liczb: %f \n", k*2048, totalTime);
		
		fprintf(f, "div SISD: Sredni czas dzielenia dla %d liczb: %f \n", k*2048, totalTime);
	} */
	
	
	return 0;

}

