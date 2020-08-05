void* cublas_create(void);
void cublas_destroy(c_void_ptr *handle);
float *cublas_array(size_t size);
void* to_gpu(c_void_ptr *src_ptr, size_t size);
void to_cpu(void* dst_ptr, void* src_ptr, size_t size);
//int cublas_axpy(c_void_ptr *handle, int N, float alpha, void *x, int incX, void *y, int incY);

int cublas_saxpy(c_void_ptr *handle, int N, float alpha, float *x, int incX, float *y, int incY);
int cublas_daxpy(c_void_ptr *handle, int N, double alpha, double *x, int incX, double *y, int incY);
int cublas_caxpy(c_void_ptr *handle, int N, complex alpha, complex *x, int incX, complex *y, int incY);

int cublas_isamax(c_void_ptr *handle, int n, float *x, int incX, int *results);
int cublas_idamax(c_void_ptr *handle, int n, double *x, int incX, int *results);

int cublas_isamin(c_void_ptr *handle, int n, float *x, int incX, int *results);
int cublas_idamin(c_void_ptr *handle, int n, double *x, int incX, int *results);

int cublas_sasum(cublasHandle_t *handle, int n, float *x, int incX, float *results);
int cublas_dasum(cublasHandle_t *handle, int n, double *x, int incX, double *results);

int cublas_scopy(cublasHandle_t *handle, int n, float *x, int incX, float *y, int incY);
int cublas_dcopy(cublasHandle_t *handle, int n, double *x, int incX, double *y, int incY);

int cublas_sdot(cublasHandle_t *handle, int n, float *x, int incX, float *y, int incY, float *result);
int cublas_ddot(cublasHandle_t *handle, int n, double *x, int incX, double *y, int incY, double *result);

int cublas_snrm2(cublasHandle_t *handle, int n, float *x, int incX, float *results);
int cublas_dnrm2(cublasHandle_t *handle, int n, double *x, int incX, double *results);

int cublas_sgemm(c_void_ptr *handle, int transa, int transb, int m, int n, int k, float alpha, float *A, int lda, float *B, int ldb, float beta, float *C, int ldc);
