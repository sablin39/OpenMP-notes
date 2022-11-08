#include<omp.h>
#include<stdio.h>
#include<chrono>
#pragma G++ optimize(2)
static long num_steps=100000;
double step;
#define NUM_THREADS 4
std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;
std::chrono::duration<double> time_span;
int main(){
    int i,nthreads;
    double pi;
    double sum;
    step=1.0/(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    t1 = std::chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        double x;
        #pragma omp for reduction(+:sum)
        for (i=0;i<num_steps;i++){
            x=(i+0.5)*step;
            sum+=4.0/(1.0+x*x);
        }
    }
    pi=step*sum;
    t2 = std::chrono::high_resolution_clock::now();  
        time_span = t2 - t1;
    printf("%lf,%fs",pi,time_span.count());
    return 0;
}