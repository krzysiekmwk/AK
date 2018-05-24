#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Vector{
	float data[4];
};



float det(struct Vector v[4]){
	struct Vector tmp;
	
	asm(
		"movups	(%0), %%xmm0 \n"
		"movups	(%1), %%xmm1 \n"
		"shufps $0x48, %%xmm0, %%xmm0 \n"
		"shufps $0xb1, %%xmm1, %%xmm1 \n"
		"mulps %%xmm1, %%xmm0 \n"
		"movups	%%xmm0, (%2) \n"
		
		:: "r"(v[0].data), "r"(v[1].data), "r"(tmp.data)
		: "%xmm0", "%xmm1"
	);
	
	printf("W: %f, %f, %f, %f \n", tmp.data[0], tmp.data[1], tmp.data[2], tmp.data[3]);
	
	float res = 1.2;
	return res;
}

int main(void){
	float wyznacznik;
	struct Vector macierz[4];
	
	float data[4][4] = {{1,2,3,4},{10,20,30,40},{1,1,1,1},{1,1,1,1}};
	
	for(int i = 0; i < 4; i++){
		macierz[i].data[0] = data[i][0];
		macierz[i].data[1] = data[i][1];
		macierz[i].data[2] = data[i][2];
		macierz[i].data[3] = data[i][3];
	}
	
	wyznacznik = det(macierz);
	printf("Wyznacznik: %f", wyznacznik);
	
	return 0;

}

