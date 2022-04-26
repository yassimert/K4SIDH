/*
 * 	 Author: Mert Yassı
 * 	 Title : A 4 way SIMD Implementation of SIDH Compatible
 * 	 			Isogeny Evaluations on Kummer Surfaces
 *   Date  : 14.05.2019
 *
 */
#include "kummer_api.h"

#define PRINT
#define VALIDATION
#define SPEED

int main() {
	vec RES[32];
#ifdef PRINT
	kummer_ISOG(RES);											// run Kummer isogeny evaluations sequence
	printf("\n\nThe last Kummer point is:\n");
	print_kpt4x751(RES);										// print the last Kummer point to screen
#endif
#ifdef VALIDATION
	FILE *f, *s, *t;
	char ch;
	s = fopen("Kummer.mag", "r");						// read Magma script version of the isogeny loop
	t = fopen("Test.mag", "w");						// make changes in new file
	while((ch = fgetc(s)) != EOF) fputc(ch, t);					// copy script to new file
	fclose(s); fclose(t);
	f = fopen("Test.mag", "a");						// open new file to append results
	printf("\n\nRunning K4SIDH Validation Test.......\n\n\n");
	kummer_ISOG(RES);											// run Kummer isogeny evaluations sequence
	fprint_kpt4x751(f,RES);										// print results to opened file
	fprintf(f, "P1 eq P[1];\n");								// check if 1st channel of the result is true
	fprintf(f, "P2 eq P[2];\n");								// check if 2nd channel of the result is true
	fprintf(f, "P3 eq P[3];\n");								// check if 3rd channel of the result is true
	fprintf(f, "P4 eq P[4];\n");								// check if 4th channel of the result is true
	fprintf(f, "exit;\n");										// append exit statement for closing Magma after checking is done
	fclose(f);
	int ret = system("python3 encoder.py Test.mag");	// run new Magma script and make the comparison
	if(ret != 0) return -1;
#endif
#ifdef SPEED
	unsigned long long cycles, cycles1, cycles2, n;
	clock_t src, trg;
	double time;
	cycles = 0;
	int LOOP = 10;
	printf("\n\nRunning K4SIDH Speed Test.......\n\n\n");
    src = clock();												// get starting time
	for (n = 0; n < LOOP; n++){									// start running isogeny sequence LOOP times
		cycles1 = cpucycles();									// measure speed of the application
		kummer_ISOG(RES);										// run Kummer isogeny evaluations sequence
		cycles2 = cpucycles();									// measure speed of the application
		cycles = cycles+(cycles2-cycles1);						// measure speed of the application
	}
    trg = clock();												// get finish time
    time = ((double) (trg - src)) / CLOCKS_PER_SEC;				// calculate running time
	printf("K4SIDH runs in:\n%10lld cycles, %f seconds.\n", cycles/LOOP, time/LOOP);
	printf("\n");
#endif
	return 0;
}
