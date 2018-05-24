#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Vector{
	//float data[4];
	float x0;
	float x1;
	float x2;
	float x3;
};

float det(struct Vector v[4]){
	struct Vector tmp;
	
	struct Vector v0 = v[0];
	struct Vector v1 = v[1];
	struct Vector v2 = v[2];
	struct Vector v3 = v[3];
	
	asm(
		//Czesc pierwsza X0
		"movups	%1, %%xmm0 \n"	//A
		"movups	%2, %%xmm1 \n"	//B
		"shufps $0b00100001, %%xmm0, %%xmm0 \n" //A' - pierwsze mnozenie
		"shufps $0b01001110, %%xmm1, %%xmm1 \n"
		"mulps %%xmm1, %%xmm0 \n"		//wynik w X0
		//"movups	%%xmm0, %0 \n"
		
		"movups	%1, %%xmm1 \n"	//A
		"movups	%2, %%xmm2 \n"	//B
		"shufps $0b01001110, %%xmm1, %%xmm1 \n" //B' - drugie mnozenie
		"shufps $0b00100001, %%xmm2, %%xmm2 \n"
		"mulps %%xmm2, %%xmm1 \n"		//wynik w X1
		//"movups	%%xmm1, %0 \n"			
		
		"subps %%xmm1, %%xmm0 \n"	//A' - B' wynik w X0
		//"movups	%%xmm0, %0 \n"
		
		
		
		
		//Czesc druga X1
		"movups	%3, %%xmm1 \n"	//C
		"movups	%4, %%xmm2 \n"	//D
		"shufps $0b10010100, %%xmm1, %%xmm1 \n" //C' - pierwsze mnozenie
		"shufps $0b11111011, %%xmm2, %%xmm2 \n"
		"mulps %%xmm2, %%xmm1 \n"		//wynik w X1
		//"movups	%%xmm1, %0 \n"
		
		"movups	%3, %%xmm2 \n"	//C
		"movups	%4, %%xmm3 \n"	//D
		"shufps $0b11111011, %%xmm2, %%xmm2 \n" //D' - drugie mnozenie
		"shufps $0b10010100, %%xmm3, %%xmm3 \n"
		"mulps %%xmm3, %%xmm2 \n"		//wynik w X2
		//"movups	%%xmm2, %0 \n"			
		
		"subps %%xmm2, %%xmm1 \n"	//C' - D' wynik w X1
		//"movups	%%xmm1, %0 \n"
		
		//Mozenie X0 i X1 -> wynik do X0
		"mulps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		
		
		
		//Czesc trzecia X2
		"movups	%1, %%xmm1 \n"	//A
		"movups	%2, %%xmm2 \n"	//B
		"shufps $0b10110000, %%xmm1, %%xmm1 \n" //A' - Dwa ostatnie bity nie sa potrzne (beda tam 0)
		"shufps $0b11010000, %%xmm2, %%xmm2 \n"
		"mulps %%xmm2, %%xmm1 \n"		//wynik w X1
		//"movups	%%xmm1, %0 \n"
		
		"movups	%1, %%xmm2 \n"	//A
		"movups	%2, %%xmm3 \n"	//B
		"shufps $0b11010000, %%xmm2, %%xmm2 \n" //B' - drugie mnozenie
		"shufps $0b10110000, %%xmm3, %%xmm3 \n"
		"mulps %%xmm3, %%xmm2 \n"		//wynik w X2
		//"movups	%%xmm2, %0 \n"
		
		"subps %%xmm2, %%xmm1 \n"	//A' - B' wynik w X1
		//"movups	%%xmm0, %0 \n"
		
		
		
		
		//Czesc czwarta X3
		"movups	%3, %%xmm2 \n"	//C
		"movups	%4, %%xmm3 \n"	//D
		"shufps $0b00000000, %%xmm2, %%xmm2 \n" //C' - pierwsze mnozenie
		"shufps $0b01100000, %%xmm3, %%xmm3 \n"
		"mulps %%xmm3, %%xmm2 \n"		//wynik w X2
		//"movups	%%xmm2, %0 \n"
		
		"movups	%3, %%xmm3 \n"	//C
		"movups	%4, %%xmm4 \n"	//D
		"shufps $0b01100000, %%xmm3, %%xmm3 \n" //D' - drugie mnozenie
		"shufps $0b00000000, %%xmm4, %%xmm4 \n"
		"mulps %%xmm4, %%xmm3 \n"		//wynik w X3
		//"movups	%%xmm3, %0 \n"			
		
		"subps %%xmm3, %%xmm2 \n"	//C' - D' wynik w X2
		"movups	%%xmm2, %0 \n"
		
		
		
		
		//Mozenie X1 i X2 -> wynik do X1
		"mulps %%xmm2, %%xmm1 \n"
		//"movups	%%xmm0, %0 \n"
		
		//Dodawanie X0 i X1 -> wynik do X0 -> ostateczny wynik. wystarczy zsumowac wektory
		"addps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		
		: "=g" (tmp)
		: "g"(v0), "g"(v1), "g"(v2), "g"(v3)
		: "%xmm0", "%xmm1", "%xmm2", "%xmm3"
	);
	
	//printf("W: %f, %f, %f, %f \n", tmp.x3, tmp.x2, tmp.x1, tmp.x0);
	
	printf("W: %f \n", tmp.x3 + tmp.x2 + tmp.x1 + tmp.x0);
	
	float res = 1.2;
	return res;
}

int main(void){
	float wyznacznik;
	struct Vector macierz[4];
	
	float data[4][4] = {{1,2,3,4},{10,22,20,15},{3,5,6,7},{11,13,14,17}};
	
	for(int i = 0; i < 4; i++){
		macierz[i].x0 = data[i][0];
		macierz[i].x1 = data[i][1];
		macierz[i].x2 = data[i][2];
		macierz[i].x3 = data[i][3];
	}
	
	wyznacznik = det(macierz);
	printf("Wyznacznik: %f", wyznacznik);
	
	return 0;

}

