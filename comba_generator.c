/*
 * 	 Author: Mert Yassı
 * 	 Title : A 4 way SIMD Implementation of SIDH Compatible
 * 	 			Isogeny Evaluations on Kummer Surfaces
 *   Date  : 14.05.2019
 *
 */
/* GENERIC COMBA BASED MULTIPLICATION/SQUARING GENERATOR */
#include <stdio.h>
#include <stdlib.h>

void mulMxN_generator(int DIGITSM, int DIGITSN) {
	int i, k, l, ct = 0, r = 0, arr[2][2], tmp;
	if(DIGITSM < DIGITSN){
		tmp = DIGITSN; DIGITSN = DIGITSM; DIGITSM = tmp;
	}
	int DIFF = DIGITSM-DIGITSN;
	printf("\n%d x %d COMBA based 4-way multiplication:\n\n",DIGITSM,DIGITSN);
	printf("R[0] = MUL4x(P[0],Q[0]);\n\n");
	for(i = 1; i < DIGITSN; i++){
		for(k = 0; k <= i; k++){
			printf("P%dQ%d = MUL4x(P[%d],Q[%d]);\n",i-k,k,i-k,k);
			if(k == 1){
				arr[0][0] = i-k+1; 	arr[0][1] = k-1;
				arr[1][0] = i-k; 	arr[1][1] = k;
			}
		}
		if(i == 1){
			printf("R[1] = ADD4x(P%dQ%d,P%dQ%d);\n",arr[0][0],arr[0][1],arr[1][0],arr[1][1]);
		}else{
			printf("tmp%d = ADD4x(P%dQ%d,P%dQ%d);\n",ct,arr[0][0],arr[0][1],arr[1][0],arr[1][1]); ct++;
		}
		for(k = 2; k <= i; k++){
			if(k == i){
				printf("R[%d] = ADD4x(tmp%d,P%dQ%d);\n",r+2,ct-1,i-k,k); r++;
			}else{
				printf("tmp%d = ADD4x(tmp%d,P%dQ%d);\n",ct,ct-1,i-k,k);
			}
			ct++;
		}
		ct = 0; printf("\n"); 
	}
	for(i = DIGITSN; i < DIGITSM; i++){
		for(k = 0; k <= DIGITSN-1; k++){
			printf("P%dQ%d = MUL4x(P[%d],Q[%d]);\n",i-k,k,i-k,k);
			if(k == 1){
				arr[0][0] = i-k+1; 	arr[0][1] = k-1;
				arr[1][0] = i-k; 	arr[1][1] = k;
			}
		}
		if(i == 1){
			printf("R[1] = ADD4x(P%dQ%d,P%dQ%d);\n",arr[0][0],arr[0][1],arr[1][0],arr[1][1]);
		}else{
			printf("tmp%d = ADD4x(P%dQ%d,P%dQ%d);\n",ct,arr[0][0],arr[0][1],arr[1][0],arr[1][1]); ct++;
		}
		for(k = 2; k <= DIGITSN-1; k++){
			if(k == DIGITSN-1){
				printf("R[%d] = ADD4x(tmp%d,P%dQ%d);\n",r+2,ct-1,i-k,k); r++;
			}else{
				printf("tmp%d = ADD4x(tmp%d,P%dQ%d);\n",ct,ct-1,i-k,k);
			}
			ct++;
		}
		ct = 0; printf("\n");
	}
	for(i = 1; i < DIGITSN-1; i++){
		for(k = DIGITSM-1, l = i; k >= DIFF+i; k--, l++){
			printf("P%dQ%d = MUL4x(P[%d],Q[%d]);\n",k,l,k,l);
			if(k == DIGITSM-2){
				arr[0][0] = k+1; 	arr[0][1] = l-1;
				arr[1][0] = k; 		arr[1][1] = l;
			}
		}
		if(i == DIGITSN-2){
			printf("R[%d] = ADD4x(P%dQ%d,P%dQ%d);\n",r+2,arr[0][0],arr[0][1],arr[1][0],arr[1][1]); r++;
		}else{
			printf("tmp%d = ADD4x(P%dQ%d,P%dQ%d);\n",ct,arr[0][0],arr[0][1],arr[1][0],arr[1][1]); ct++;
		}
		for(k = DIGITSM-3, l = i; k >= DIFF+i; k--, l++){
			if(k == DIFF+i){
				printf("R[%d] = ADD4x(tmp%d,P%dQ%d);\n",r+2,ct-1,k,l+2); r++;
			}else{
				printf("tmp%d = ADD4x(tmp%d,P%dQ%d);\n",ct,ct-1,k,l+2);
			}
			ct++;
		}
		ct = 0; printf("\n");
	}
	printf("R[%d] = MUL4x(P[%d],Q[%d]);\n",r+2,DIGITSM-1,DIGITSN-1);
}

void squ_generator(int DIGITS) {
	int i, k, l, ct = 0, r = 0, flag = 0, arr[2][2];
	printf("\n%d x %d COMBA based 4-way squaring:\n\n",DIGITS,DIGITS);

	for(k = 0; k < DIGITS-1; k++) {
		printf("P%d_2 = ADD4x(P[%d],P[%d]);\n",k,k,k);
	}
	printf("\n");
	printf("R[0] = MUL4x(P[0],P[0]);\n\n");
	printf("R[1] = MUL4x(P[1],P0_2);\n\n");
	for(i = 2; i < DIGITS; i++) {
		for(k = 0; k <= i/2; k++) {
			if(i-k == k){
				printf("P%dP%d = MUL4x(P[%d],P[%d]);\n",i-k,k,i-k,k);
			}else{
				printf("P%dP%d = MUL4x(P[%d],P%d_2);\n",i-k,k,i-k,k);
			}
			if(k == 1){
				arr[0][0] = i-k+1; 	arr[0][1] = k-1;
				arr[1][0] = i-k; 	arr[1][1] = k;
			}
		}
		if(i == 2){
			printf("R[2] = ADD4x(P%dP%d,P%dP%d);\n",arr[0][0],arr[0][1],arr[1][0],arr[1][1]);
		}else if(i == 3){
			printf("R[3] = ADD4x(P%dP%d,P%dP%d);\n",arr[0][0],arr[0][1],arr[1][0],arr[1][1]);
		}else{
			printf("tmp%d = ADD4x(P%dP%d,P%dP%d);\n",ct,arr[0][0],arr[0][1],arr[1][0],arr[1][1]); ct++;
		}for(k = 2; k <= i/2; k++) {
			if(k == i/2){
				printf("R[%d] = ADD4x(tmp%d,P%dP%d);\n",r+4,ct-1,i-k,k); r++;
			}else{
				printf("tmp%d = ADD4x(tmp%d,P%dP%d);\n",ct,ct-1,i-k,k);
			}
			ct++;
		}
		ct = 0; printf("\n");
	}
	for(i = 1; i < DIGITS-2; i++) {
		for(k = DIGITS-1, l = i; k >= i; k--, l++){
			if(k == DIGITS-2){
				arr[0][0] = k+1; 	arr[0][1] = l-1;
				arr[1][0] = k; 		arr[1][1] = l;
			}
			if(k == l){
				printf("P%dP%d = MUL4x(P[%d],P[%d]);\n",k,l,k,l);
				break;
			}
			else if(k == l+1){
				printf("P%dP%d = MUL4x(P[%d],P%d_2);\n",k,l,k,l);
				break;
			}
			else{
				printf("P%dP%d = MUL4x(P[%d],P%d_2);\n",k,l,k,l);

			}
		}
		if((i == DIGITS-3) | (i == DIGITS-4)){
			printf("R[%d] = ADD4x(P%dP%d,P%dP%d);\n",r+4,arr[0][0],arr[0][1],arr[1][0],arr[1][1]); r++;
			flag = 1;
		}else{
			printf("tmp%d = ADD4x(P%dP%d,P%dP%d);\n",ct,arr[0][0],arr[0][1],arr[1][0],arr[1][1]); ct++;
		}
		for(k = DIGITS-3, l = i; k >= i; k--, l++){
			if(flag == 1){
				break;
			}else if((k == l+2) | (k == l+3)){
				printf("R[%d] = ADD4x(tmp%d,P%dP%d);\n",r+4,ct-1,k,l+2); r++;
				break;
			}else{
				printf("tmp%d = ADD4x(tmp%d,P%dP%d);\n",ct,ct-1,k,l+2);
			}
			ct++;
		}
		flag = 0; ct = 0; printf("\n");
	}
	printf("R[%d] = MUL4x(P[%d],P%d_2);\n\n",r+4,DIGITS-1,DIGITS-2); r++;
	printf("R[%d] = MUL4x(P[%d],P[%d]);\n",r+4,DIGITS-1,DIGITS-1);
}

int main() {
	mulMxN_generator(63,32);
	squ_generator(32);

	return 0;
}



