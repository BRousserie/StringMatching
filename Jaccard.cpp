#include <fstream>
#include <iostream>
#include "Jaccard.h"
#include "enron.h"
#include "App.h"


Jaccard::Jaccard() {
    match();
}

Jaccard* Jaccard::singleton;

Jaccard* Jaccard::get() {
    if (!Jaccard::singleton) Jaccard::singleton = new Jaccard();
    return Jaccard::singleton;
}

void Jaccard::match() {
    enron entity = (*enron::get());
    int interval;

    ofstream output_file(get_enron_path().append("/Jaccard_Measures.txt"));
    for(int i = 0; i < NB_MAILS; i++) cout << "\t" << i;


    for(int i = 0; i < NB_MAILS; i++) {

        output_file << i;
        for(int j = 0; j < NB_MAILS; j++) {

            if (i != j) {
                cout << i << " - " << j << "\n";

                const set<int> &setA = (*entity.get_mails())[i];
                const set<int> &setB = (*entity.get_mails())[j];

                interval = 0;

                for (int A : setA) {
                    for (int B : setB) {

                        if (A == B) interval++;

                    }
                }
                output_file << "#" << i+1 << " - #" << j+1 << " "
                    << (float)interval / (float)(setA.size() + setB.size()) << "\n";
            }
        }
    }
    output_file.close();
}

