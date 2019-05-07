#include "omp.h"
#include <iostream>
#include "enron.h"
#include "Jaccard.h"
#include <unistd.h>

using namespace std;

int main() {
    cout << omp_get_max_threads() << " threads are available\n";
#pragma omp parallel
    {
        string hello_thread("Hello from " + to_string(omp_get_thread_num()) + "\n");
        cout << hello_thread << std::flush;
    };
    enron::get()->log();
    Jaccard::get();
    return 0;
}

