#include <stdio.h>

struct Vector{
	float x0;
	float x1;
	float x2;
	float x3;
};

float det(struct Vector v[4]){
	struct Vector tmp;
	
	//0 - 00
	//1 - 01
	//2 = 10
	//3 = 11
	//IN= 3  2 	1  0
	//A = a0 a1 a2 a3
	//A'= a2 a2 a0 a3
	//X0= 01 01 11 00
	
	asm(
		//Czesc pierwsza X0
		"movups	%1, %%xmm0 \n"	//A
		"movups	%2, %%xmm1 \n"	//B
		"shufps $0xDE, %%xmm0, %%xmm0 \n" //A' - a0a2a0a1 - 11011110
		"shufps $0xB1, %%xmm1, %%xmm1 \n" //B' - b1b0b3b2 - 10110001
		"mulps %%xmm1, %%xmm0 \n"		//wynik w X0
		
		"movups	%1, %%xmm1 \n"	//A
		"movups	%2, %%xmm2 \n"	//B
		"shufps $0xB1, %%xmm1, %%xmm1 \n" //A' - a1a0a3a2
		"shufps $0xDE, %%xmm2, %%xmm2 \n" //B' - b0b2b0b1
		"mulps %%xmm2, %%xmm1 \n"		//wynik w X1		
		
		"subps %%xmm1, %%xmm0 \n"	//A' - B' wynik w X0		
		
		
		
		//Czesc druga X1
		"movups	%3, %%xmm1 \n"	//C
		"movups	%4, %%xmm2 \n"	//D
		"shufps $0x6B, %%xmm1, %%xmm1 \n" //C' - c2c1c1c0
		"shufps $0x04, %%xmm2, %%xmm2 \n" //D' - d3d3d2d3
		"mulps %%xmm2, %%xmm1 \n"		//wynik w X1
		
		"movups	%3, %%xmm2 \n"	//C
		"movups	%4, %%xmm3 \n"	//D
		"shufps $0x04, %%xmm2, %%xmm2 \n" //C' - c3c3c2c3
		"shufps $0x6B, %%xmm3, %%xmm3 \n" //D' - d2d1d1d0
		"mulps %%xmm3, %%xmm2 \n"		//wynik w X2		
		
		"subps %%xmm2, %%xmm1 \n"	//C' - D' wynik w X1
		
		//Mozenie X0 i X1 -> wynik do X0
		"mulps %%xmm1, %%xmm0 \n"
		
		
		
		//Czesc trzecia X2
		"movups	%1, %%xmm1 \n"	//A
		"movups	%2, %%xmm2 \n"	//B
		"shufps $0x4F, %%xmm1, %%xmm1 \n" //A' - a2a3a0a0 (2 ostatnie sie wyzeruja przy odejmowaniu A'-B')
		"shufps $0x2F, %%xmm2, %%xmm2 \n" //B' - b3b1b0b0
		"mulps %%xmm2, %%xmm1 \n"		//wynik w X1
		
		"movups	%1, %%xmm2 \n"	//A
		"movups	%2, %%xmm3 \n"	//B
		"shufps $0x2F, %%xmm2, %%xmm2 \n" //A' - a3a1a0a0
		"shufps $0x4F, %%xmm3, %%xmm3 \n" //B' - b2b3b0b0
		"mulps %%xmm3, %%xmm2 \n"		//wynik w X2
		
		"subps %%xmm2, %%xmm1 \n"	//A' - B' wynik w X1
		//"movups	%%xmm1, %0 \n"	//Widac ze dwie ostatnie pozycje to 0 - wiec nie bedzie mialo wplywu na pozniejsze dodawanie)
		
		
		
		
		//Czesc czwarta X3
		"movups	%3, %%xmm2 \n"	//C
		"movups	%4, %%xmm3 \n"	//D
		"shufps $0xFF, %%xmm2, %%xmm2 \n" //C' - c0c0c0c0
		"shufps $0x9F, %%xmm3, %%xmm3 \n" //D' - d1d2d0d0
		"mulps %%xmm3, %%xmm2 \n"		//wynik w X2
		
		"movups	%3, %%xmm3 \n"	//C
		"movups	%4, %%xmm4 \n"	//D
		"shufps $0x9F, %%xmm3, %%xmm3 \n" //C' - c1c2c0c0
		"shufps $0xFF, %%xmm4, %%xmm4 \n" //D' - d0d0d0d0
		"mulps %%xmm4, %%xmm3 \n"		//wynik w X3		
		
		"subps %%xmm3, %%xmm2 \n"	//C' - D' wynik w X2		
		
		
		
		//Mozenie X1 i X2 -> wynik do X1
		"mulps %%xmm2, %%xmm1 \n"
		
		//Dodawanie X0 i X1 -> wynik do X0 -> ostateczny wynik. wystarczy zsumowac wektory
		"addps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		
		: "=g" (tmp)
		: "g"(v[0]), "g"(v[1]), "g"(v[2]), "g"(v[3])
		: "%xmm0", "%xmm1", "%xmm2", "%xmm3", "%xmm4"
	);
	
	//printf("W: %f, %f, %f, %f \n", tmp.x3, tmp.x2, tmp.x1, tmp.x0);
	//printf("W: %f \n", tmp.x3 + tmp.x2 + tmp.x1 + tmp.x0);
	
	return tmp.x3 + tmp.x2 + tmp.x1 + tmp.x0;
}

int main(void){
	float wyznacznik;
	struct Vector macierz[4];
	
	float data[4][4] = {{1,2,3,4},{2,9,2,3},{3,5,20,7},{11,13,1,10}};
	
	for(int i = 0; i < 4; i++){
		macierz[i].x0 = data[i][0];
		macierz[i].x1 = data[i][1];
		macierz[i].x2 = data[i][2];
		macierz[i].x3 = data[i][3];
	}
	
	wyznacznik = det(macierz);
	printf("Wyznacznik: %f \n", wyznacznik);
	
	return 0;

}

