#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include  "cublas_v2.h"

float* cublas_array(size_t size){

    float *ptr;
    cudaError_t err = cudaMallocManaged(&ptr, size*sizeof(float), cudaMemAttachGlobal);
    //printf("CUDA Error: %s\n", cudaGetErrorString(err));
    cudaDeviceSynchronize();
    return ptr;

}

void* to_gpu(void* src_ptr, size_t size){
    void *dst_ptr;
    cudaError_t malloc_err = cudaMalloc(&dst_ptr, size);
    //printf("CUDA malloc error: %s\n", cudaGetErrorString(malloc_err));
    cudaError_t memcpy_err = cudaMemcpy(dst_ptr, src_ptr, size, cudaMemcpyHostToDevice);
    //printf("CUDA memcpy HtoD error: %s\n", cudaGetErrorString(memcpy_err));
    return dst_ptr;

}

void to_cpu(void* dst_ptr, void* src_ptr, size_t size){

    cudaError_t memcpy_err = cudaMemcpy(dst_ptr, src_ptr, size, cudaMemcpyDeviceToHost);
    //printf("CUDA memcpy DtoH error: %s\n", cudaGetErrorString(memcpy_err));

}

void* cublas_create(void){

    cublasHandle_t *handle = (cublasHandle_t*)malloc(sizeof(cublasHandle_t));
    cublasStatus_t err = cublasCreate(handle);
    //printf("cublasCreate status: %s\n", cudaGetErrorString(err));
    return handle;

}

void cublas_destroy(cublasHandle_t *handle){

    cublasStatus_t err = cublasDestroy(*handle);
    //printf("cublasDestroy status: %s\n", cudaGetErrorString(err));

}

int cublas_saxpy(cublasHandle_t *handle, int n, float alpha, float *x, int incX, float *y, int incY){

    cublasSaxpy(*handle, n, &alpha, x, incX, y, incY);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_daxpy(cublasHandle_t *handle, int n, double alpha, double *x, int incX, double *y, int incY){

    cublasDaxpy(*handle, n, &alpha, x, incX, y, incY);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_caxpy(cublasHandle_t *handle, int n, complex float alpha, complex float *x, int incX, complex float *y, int incY){

    cublasCaxpy(*handle, n, (cuFloatComplex*) &alpha, (cuFloatComplex*) x,  incX, (cuFloatComplex*) y, incY);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_zaxpy(cublasHandle_t *handle, int n, complex double alpha, complex double *x, int incX, complex double *y, int incY){

    cublasZaxpy(*handle, n, (cuDoubleComplex*) &alpha, (cuDoubleComplex*) x, incX, (cuDoubleComplex*) y, incY);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_isamax(cublasHandle_t *handle, int n, float *x, int incX, int *results){

    cublasIsamax(*handle, n, x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_idamax(cublasHandle_t *handle, int n, double *x, int incX, int *results){

    cublasIdamax(*handle, n, x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_icamax(cublasHandle_t *handle, int n, complex float *x, int incX, int *results){

    cublasIcamax(*handle, n, (cuFloatComplex*) x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_izamax(cublasHandle_t *handle, int n, complex double *x, int incX, int *results){

    cublasIzamax(*handle, n, (cuDoubleComplex*) x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_isamin(cublasHandle_t *handle, int n, float *x, int incX, int *results){

    cublasIsamin(*handle, n, x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_idamin(cublasHandle_t *handle, int n, double *x, int incX, int *results){

    cublasIdamin(*handle, n, x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_icamin(cublasHandle_t *handle, int n, complex float *x, int incX, int *results){

    cublasIcamin(*handle, n, (cuFloatComplex*) x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_izamin(cublasHandle_t *handle, int n, complex double *x, int incX, int *results){

    cublasIzamin(*handle, n, (cuDoubleComplex*) x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_sasum(cublasHandle_t *handle, int n, float *x, int incX, float *results){

    cublasSasum(*handle, n, x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_dasum(cublasHandle_t *handle, int n, double *x, int incX, double *results){

    cublasDasum(*handle, n, x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_scasum(cublasHandle_t *handle, int n, complex float *x, int incX, float *results){

    cublasScasum(*handle, n, (cuFloatComplex*) x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_dzasum(cublasHandle_t *handle, int n, complex double *x, int incX, double *results){

    cublasDzasum(*handle, n, (cuDoubleComplex*) x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_scopy(cublasHandle_t *handle, int n, float *x, int incX, float *y, int incY){

    cublasScopy(*handle, n, x, incX, y, incY);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_dcopy(cublasHandle_t *handle, int n, double *x, int incX, double *y, int incY){

    cublasDcopy(*handle, n, x, incX, y, incY);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_ccopy(cublasHandle_t *handle, int n, complex float *x, int incX, complex float *y, int incY){

    cublasCcopy(*handle, n, (cuFloatComplex*) x, incX, (cuFloatComplex*) y, incY);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_zcopy(cublasHandle_t *handle, int n, complex double *x, int incX, complex double *y, int incY){

    cublasZcopy(*handle, n, (cuDoubleComplex*) x, incX, (cuDoubleComplex*) y, incY);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_sdot(cublasHandle_t *handle, int n, float *x, int incX, float *y, int incY, float *result){

    cublasSdot(*handle, n, x, incX, y, incY, result);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_ddot(cublasHandle_t *handle, int n, double *x, int incX, double *y, int incY, double *result){

    cublasDdot(*handle, n, x, incX, y, incY, result);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_cdotu(cublasHandle_t *handle, int n, complex float *x, int incX, complex float *y, int incY, complex float *result){

    cublasCdotu(*handle, n, (cuFloatComplex*) x, incX, (cuFloatComplex*) y, incY, (cuFloatComplex*) result);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_zdotu(cublasHandle_t *handle, int n, complex double *x, int incX, complex double *y, int incY, complex double *result){

    cublasZdotu(*handle, n, (cuDoubleComplex*) x, incX, (cuDoubleComplex*) y, incY, (cuDoubleComplex*) result);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_snrm2(cublasHandle_t *handle, int n, float *x, int incX, float *results){

    cublasSnrm2(*handle, n, x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_dnrm2(cublasHandle_t *handle, int n, double *x, int incX, double *results){

    cublasDnrm2(*handle, n, x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_scnrm2(cublasHandle_t *handle, int n, complex float *x, int incX, float *results){

    cublasScnrm2(*handle, n, (cuFloatComplex*) x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_dznrm2(cublasHandle_t *handle, int n, complex double *x, int incX, double *results){

    cublasDznrm2(*handle, n, (cuDoubleComplex*) x, incX, results);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_srot(cublasHandle_t *handle, int n, float *x, int incX, float *y, int incY, float c, float s){
    cublasSrot(*handle, n, x, incX, y, incY, &c, &s);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_drot(cublasHandle_t *handle, int n, double *x, int incX, double *y, int incY, double c, double s){
    cublasDrot(*handle, n, x, incX, y, incY, &c, &s);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_crot(cublasHandle_t *handle, int n, complex float *x, int incX, complex float *y, int incY, float c, complex float s){
    cublasCrot(*handle, n, (cuFloatComplex*) x, incX, (cuFloatComplex*) y, incY, &c, (cuFloatComplex*) &s);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_csrot(cublasHandle_t *handle, int n, complex float *x, int incX, complex float *y, int incY, float c, float s){
    cublasCsrot(*handle, n, (cuFloatComplex*) x, incX, (cuFloatComplex*) y, incY, &c, &s);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_zrot(cublasHandle_t *handle, int n, complex double *x, int incX, complex double *y, int incY, double c, complex double s){
    cublasZrot(*handle, n, (cuDoubleComplex*) x, incX, (cuDoubleComplex*) y, incY, &c, (cuDoubleComplex*) &s);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_zdrot(cublasHandle_t *handle, int n, complex double *x, int incX, complex double *y, int incY, double c, double s){
    cublasZdrot(*handle, n, (cuDoubleComplex*) x, incX, (cuDoubleComplex*) y, incY, &c, &s);
    cudaDeviceSynchronize();
    return 0;
}


int cublas_srotg(cublasHandle_t *handle, float a, float b, float c, float s){
    cublasSrotg(*handle, &a, &b, &c, &s);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_drotg(cublasHandle_t *handle, double a, double b, double c, double s){
    cublasDrotg(*handle, &a, &b, &c, &s);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_srotm(cublasHandle_t *handle, int n, float *x, int incX, float *y, int incY, float *param){
    cublasSrotm(*handle, n, x, incX, y, incY, param);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_drotm(cublasHandle_t *handle, int n, double *x, int incX, double *y, int incY, double *param){
    cublasDrotm(*handle, n, x, incX, y, incY, param);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_srotmg(cublasHandle_t *handle, float d1, float d2, float x1, float y1, float *param){

    cublasSrotmg(*handle, &d1, &d2, &x1, &y1, param);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_drotmg(cublasHandle_t *handle, double d1, double d2, double x1, double y1, double *param){
    cublasDrotmg(*handle, &d1, &d2, &x1, &y1, param);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_sscal(cublasHandle_t *handle, int n, float alpha, float *x, int incX){
    cublasSscal(*handle, n, &alpha, x, incX);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_dscal(cublasHandle_t *handle, int n, double alpha, double *x, int incX){
    cublasDscal(*handle, n, &alpha, x, incX);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_cscal(cublasHandle_t *handle, int n, complex float alpha, complex float *x, int incX){
    cublasCscal(*handle, n, (cuFloatComplex*) &alpha, (cuFloatComplex*) x, incX);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_zscal(cublasHandle_t *handle, int n, complex double alpha, complex double *x, int incX){
    cublasZscal(*handle, n, (cuDoubleComplex*) &alpha, (cuDoubleComplex*) x, incX);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_sswap(cublasHandle_t *handle, int n, float *x, int incX, float *y, int incY){
    cublasSswap(*handle, n, x, incX, y, incY);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_dswap(cublasHandle_t *handle, int n, double *x, int incX, double *y, int incY){
    cublasDswap(*handle, n, x, incX, y, incY);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_cswap(cublasHandle_t *handle, int n, complex float *x, int incX, complex float *y, int incY){
    cublasCswap(*handle, n, (cuFloatComplex*) x, incX, (cuFloatComplex*) y, incY);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_zswap(cublasHandle_t *handle, int n, complex double *x, int incX, complex double *y, int incY){
    cublasZswap(*handle, n, (cuDoubleComplex*) x, incX, (cuDoubleComplex*) y, incY);
    cudaDeviceSynchronize();
    return 0;
}

int cublas_sgemm(cublasHandle_t *handle, int transa, int transb, int m, int n, int k, float alpha, float *A, int lda, float *B, int ldb, float beta, float *C, int ldc){

    cublasSgemm(*handle, transa, transb, m, n, k, &alpha, A, lda, B, ldb, &beta, C, ldc);
    cudaDeviceSynchronize();
    return 0;

}
