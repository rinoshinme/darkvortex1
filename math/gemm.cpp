#include "gemm.h"

// register for efficient access
/*
 * A: MxK
 * B: KxN
 * C: MxN (C = A x B)
 */ 
void gemm_nn(int M, int N, int K, float ALPHA,
	float* A, int lda,
	float* B, int ldb,
	float* C, int ldc)
{
	for (int i = 0; i < M; ++i)
	{
		for (int k = 0; k < K; ++k)
		{
			register float A_part = ALPHA * A[i * lda + k];
			for (int j = 0; j < N; ++j)
				C[i * ldc + j] += A_part * B[k * ldb + j];
		}
	}
}

/*
 * A: MxK
 * B: NxK
 * C: MxN (C = A x Bt)
 */ 
void gemm_nt(int M, int N, int K, float ALPHA,
	float* A, int lda,
	float* B, int ldb,
	float* C, int ldc)
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			register float sum = 0.0f;
			for (int k = 0; k < K; ++k)
				sum += ALPHA * A[i * lda + k] * B[j * ldb + k];
			C[i * ldc + j] += sum;
		}
	}
}

/*
 * A: KxM
 * B: KxN
 * C: MxN (C = At x B)
 */
void gemm_tn(int M, int N, int K, float ALPHA,
	float* A, int lda,
	float* B, int ldb,
	float* C, int ldc)
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			register float sum = 0.0f;
			for (int k = 0; k < K; ++k)
				sum += ALPHA * A[k * lda + i] * B[k * ldb + j];
			C[i * ldc + j] += sum;
		}
	}
}

/* 
 * A: KxM
 * B: NxK
 * C: MxN (C = At x Bt)
 */
void gemm_tt(int M, int N, int K, float ALPHA,
	float* A, int lda,
	float* B, int ldb,
	float* C, int ldc)
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			register float sum = 0.0f;
			for (int k = 0; k < K; ++k)
				sum += ALPHA * A[k * lda + i] * B[j * ldb + k];
			C[i * lda + j] += sum;
		}
	}
}

/*
 * C = C * BETA + ALPHA * A * B
 */
void gemm_cpu(bool TA, bool TB, int M, int N, int K, float ALPHA,
	float* A, int lda,
	float* B, int ldb,
	float BETA,
	float* C, int ldc)
{
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
			C[i * ldc + j] *= BETA;

	if (!TA && !TB)
		gemm_nn(M, N, K, ALPHA, A, lda, B, ldb, C, ldc);
	else if (!TA && TB)
		gemm_nt(M, N, K, ALPHA, A, lda, B, ldb, C, ldc);
	else if (TA && !TB)
		gemm_tn(M, N, K, ALPHA, A, lda, B, ldb, C, ldc);
	else
		gemm_tt(M, N, K, ALPHA, A, lda, B, ldb, C, ldc);
}
