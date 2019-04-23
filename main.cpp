#include "enron.h"
#include "Jaccard.h"

using namespace std;

int main() {
    enron::get()->log();
    Jaccard::get();
    return 0;
}

