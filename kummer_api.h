/*
 * 	 Author: Mert Yassı
 * 	 Title : A 4 way SIMD Implementation of SIDH Compatible
 * 	 			Isogeny Evaluations on Kummer Surfaces
 *   Date  : 14.05.2019
 *
 */
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <immintrin.h>

#ifndef KUMMER_API_H_
#define KUMMER_API_H_

#define ADD4x _mm256_add_epi64
#define SUB4x _mm256_sub_epi64
#define AND4x _mm256_and_si256
#define MUL4x _mm256_mul_epu32
#define SHL4x _mm256_slli_epi64
#define SHR4x _mm256_srli_epi64
#define BLD4x _mm256_blend_epi32
#define SHF4x _mm256_shuffle_epi32
#define PER4x _mm256_permute4x64_epi64

typedef unsigned long long int u64;
typedef struct {
	unsigned long long int v[32];
} kpt64;

typedef struct {
	unsigned long long int v[63];
} kpt64d;

typedef __m256i vec;

int64_t cpucycles(void);
void kpt4x_to_kpt64(kpt64 *m, vec *r64);
void fprint_kpt4x751(FILE *f, vec *pt);
void print_kpt4x751(vec *pt);
void print_kpt4x751d(vec *pt);
void combaMUL32x32(vec *R, vec *P, vec *Q);
void combaMUL63x32(vec *R, vec *P, vec *Q);
void kummer_HDM(vec *res, vec *P);
void kummer_RDC(vec *R, vec *P);
void kummer_SQU(vec *R, vec *P);
void kummer_MUL(vec *R, vec *P, vec *Q);
void kummer_INV(vec *R, vec *P);
void kummer_DBL(vec *dP, vec *P, vec *K3, vec *K4);
void kummer_eDBLs(vec *eP, vec *P, vec *K3, vec *K4, int e);
void KummerConstantsFromSquaredThetas(vec *K3, vec *K4, vec *mus);
void IsogenousSquaredThetasFromTorsionKernel(vec *mus, vec *pis, vec *P2, vec *P4);
void IsogenyKummerPoint(vec *P, vec *pis);
void kummer_ISOG(vec *R);

#endif /* KUMMER_API_H_ */
