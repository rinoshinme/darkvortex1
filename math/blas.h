#ifndef DARKVORTEX_BLAS_H
#define DARKVORTEX_BLAS_H

/* cpu blas functions */
void const_cpu(int N, float alpha, float* x, int inc_x);
void axpy_cpu(int N, float alpha, float* x, int inc_x, float* y, int inc_y);
void add_cpu(int N, float alpha, float* x, int inc_x);
void copy_cpu(int N, float* x, int inc_x, float* y, int inc_y);
void scale_cpu(int N, float alpha, float* x, int inc_x);

/* softmax operations */
void softmax_cpu(float* input, int batch_size, int sample_size, float temperature, float* output);
float xentropy_cpu(float* x, float* y, int batch_size, int sample_size);
void softmax_gradient();

#ifdef GPU
/* gpu blas functions */

#endif

#endif
