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
    
    step=1.0/(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    t1 = std::chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        int i,id,nthrds;
        double x;
        double sum;//Turns into local variable
        id=omp_get_thread_num();
        nthrds=omp_get_num_threads();
        if (id==0)
            nthreads=nthrds;
        for (i=id,sum=0.0;i<num_steps;i+=nthrds){
            x=(i+0.5)*step;
            sum+=4.0/(1.0+x*x);//No array sum[], thus no false sharing
        }
        #pragma omp critical
            pi+=(sum*step);
    }
    
    t2 = std::chrono::high_resolution_clock::now();  
        time_span = t2 - t1;
    printf("%lf,%fs",pi,time_span.count());
    return 0;
}