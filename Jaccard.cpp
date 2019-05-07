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
    enron& entity = (*enron::get());
    int i, j, interval;
    set<int> union_set;
    string output;
    ofstream output_file(get_enron_path().append("/Jaccard_Measures.txt"));

#pragma omp parallel for private(i, j, interval, output, union_set) shared(output_file, entity)
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
            output = ("#" + to_string(i + 1) + " - #" + to_string(j + 1) + " "
                        + to_string((float) interval / (float) union_set.size()) + "\n");
            output_file << output;

        }
    }
    output_file.close();
}

