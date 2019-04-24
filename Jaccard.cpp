#include <fstream>
#include <iostream>
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

    ofstream output_file(get_enron_path().append("/Jaccard_Measures.txt"));

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
            output_file << "#" << i + 1 << " - #" << j + 1 << " "
                        << (float) interval / (float) (setA.size() + setB.size()) << "\n";

        }
    }
    output_file.close();
}

