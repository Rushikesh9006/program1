#include <iostream>
#include <omp.h>

int main() {
   
    int num_procs = omp_get_num_procs();
    std::cout << "Number of processors available: " << num_procs << std::endl;

   
    int max_threads = omp_get_max_threads();
    std::cout << "Maximum threads available: " << max_threads << std::endl;

    omp_set_num_threads(max_threads);

 
    #pragma omp parallel
    {
        
        #pragma omp single
        {
            int num_threads = omp_get_num_threads();
            std::cout << "Number of threads in parallel: " << num_threads << std::endl;
        }

        #pragma omp critical
        {
            std::cout << "Thread " << omp_get_thread_num() << " is running" << std::endl;
        }
    }

    return 0;
}
