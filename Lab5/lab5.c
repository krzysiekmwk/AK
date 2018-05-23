#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Vector{
	int x0;
	int x1;
	int x2;
	int x3;
};



float det(struct Vector v[4]){
		//"shufps $0x48, %%xmm0, %%xmm0 \n"
		//"shufps $0xb1, %%xmm1, %%xmm1 \n"
	struct Vector tmp;
	struct Vector v1 = v[0];
	struct Vector v2 = v[1];
	//tmp.data[0] = 10;
	/*asm(
		"movups	(%1), %%xmm0 \n"
		"movups	(%2), %%xmm1 \n"
		"mulps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, (%0) \n"
		: "=g"(tmp.data)
		: "g"(v[0].data), "g"(v[1].data), "g"(v[2].data), "g"(v[3].data)
		: "%xmm0", "%xmm1"
	);*/
	
	asm(
		"movups	%1, %%xmm0 \n"
		"movups	%2, %%xmm1 \n"
		"shufps $0x49, %%xmm0, %%xmm0 \n"
		"shufps $0xb1, %%xmm1, %%xmm1 \n"
		"addps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, %0 \n"
		: "=g" (tmp)
		: "g"(v1), "g"(v2)
		: "%xmm0", "%xmm1"
	);
	
	printf("W: %d, %d, %d, %d \n", tmp.x0, tmp.x1, tmp.x2, tmp.x3);
	
	float res = 1.2;
	return res;
}

int main(void){
	float wyznacznik;
	struct Vector macierz[4];
	
	int data[4][4] = {{1,2,3,4},{10,20,30,40},{1,1,1,1},{1,1,1,1}};
	
	/*for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			macierz[i].data[j] = data[i][j];
		}
	}*/
	
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

