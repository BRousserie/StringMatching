#ifndef INTERNSHIP_JACCARD_H
#define INTERNSHIP_JACCARD_H

#include "enron.h"

using namespace std;

class Jaccard {
private:
    static Jaccard* singleton;

public:
    static Jaccard* get();
    void log(array<measure, NB_SCORES>& scores);

private:
    Jaccard();
    void match();

};


#endif //INTERNSHIP_JACCARD_H
