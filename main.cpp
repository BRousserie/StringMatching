#include "omp.h"
#include "enron.h"
#include "Jaccard.h"
#include <iostream>
#include <unistd.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    cout << omp_get_max_threads() << " threads are available\n";

    enron::get()->log();

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    Jaccard::get();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<seconds>( t2 - t1 ).count();
    cout << duration << endl;
    return 0;
}

