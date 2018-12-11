#ifndef DARKVORTEX_BLAS_H
#define DARKVORTEX_BLAS_H

/* cpu blas functions */
void const_cpu(int N, float alpha, float* x, int inc_x);
void axpy_cpu(int N, float alpha, float* x, int inc_x, float* y, int inc_y);
void add_cpu(int N, float alpha, float* x, int inc_x);
void copy_cpu(int N, float* x, int inc_x, float* y, int inc_y);
void scale_cpu(int N, float alpha, float* x, int inc_x);


#ifdef GPU
/* gpu blas functions */

#endif

#endif
