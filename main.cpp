#include "omp.h"
#include "enron.h"
#include "Jaccard.h"
#include <iostream>
#include <unistd.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {

    cout << NB_MEASURES_PER_THREAD << endl;
    cout << omp_get_max_threads() << " threads are available\n";
#pragma omp parallel
    {
        string hello_thread("Hello from " + to_string(omp_get_thread_num()) + "\n");
        cout << hello_thread << std::flush;
    };
    enron::get()->log();

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    Jaccard::get();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
    cout << duration << endl;
    return 0;
}

