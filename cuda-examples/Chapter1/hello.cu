#include "stdio.h"

__global__ void helloFromGPU(void) {
	printf("Hello World from thread %d\n", threadIdx.x);
}

int main()
{
    printf("Hello World from CPU\n");
    helloFromGPU<<<10, 10>>>();
    cudaDeviceReset();
    // cudaDeviceSynchronize();
    return 0;
}
