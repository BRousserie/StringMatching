#include <vector>
#include <map>
#include "enron.h"

using namespace std;

#ifndef INTERNSHIP_JACCARD_H
#define INTERNSHIP_JACCARD_H

class Jaccard {
private:
    static Jaccard* singleton;

public:
    static Jaccard* get();

private:
    Jaccard();
    void match();
};


#endif //INTERNSHIP_JACCARD_H
