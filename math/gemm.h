#ifndef DARKVORTEX_GEMM_H
#define DARKVORTEX_GEMM_H

/* cpu gemm functions */

void gemm_cpu(bool TA, bool TB, int M, int N, int K, float ALPHA,
	float* A, int lda,
	float* B, int ldb,
	float BETA,
	float* C, int ldc);

inline void gemm(bool TA, bool TB, int M, int N, int K, float ALPHA,
	float* A, int lda,
	float* B, int ldb,
	float BETA,
	float* C, int ldc)
{
	gemm_cpu(TA, TB, M, N, K, ALPHA, A, lda, B, ldb, BETA, C, ldc);
}

#ifdef GPU

void gemm_gpu(bool TA, bool TB, int M, int N, int K, float ALPHA
	float* A, int lda,
	float* B, int ldb,
	float BETA,
	float* C, int ldc);

#endif


#endif
