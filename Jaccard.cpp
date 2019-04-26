#include <fstream>
#include <iostream>
#include <omp.h>
#include "Jaccard.h"
#include "enron.h"
#include "App.h"


Jaccard::Jaccard() {
    match();
}

Jaccard *Jaccard::singleton;

Jaccard *Jaccard::get() {
    if (!Jaccard::singleton) Jaccard::singleton = new Jaccard();
    return Jaccard::singleton;
}

void Jaccard::match() {
    enron entity = (*enron::get());
    int interval;
    int i, j;
    set<int> union_set;

    ofstream output_file(get_enron_path().append("/Jaccard_Measures.txt"));

#pragma omp parallel for num_threads(8)
    for (i = 0; i < NB_MAILS; i++) {
        for (j = i + 1; j < NB_MAILS; j++) {

            const set<int> &setA = (*entity.get_mails())[i];
            const set<int> &setB = (*entity.get_mails())[j];

            interval = 0;

            for (int A : setA) {
                for (int B : setB) {

                    if (A == B) interval++;

                }
            }

            union_set = setA;
            union_set.insert(setB.begin(), setB.end());
            output_file << "#" << i + 1 << " - #" << j + 1 << " "
                        << (float) interval / (float) union_set.size() << "\n";

        }
    }
    output_file.close();
}

