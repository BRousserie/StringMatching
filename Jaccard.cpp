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
    int i, j, interval, inserted_values = 0;
    float score;
    set<int> union_set;
    pair<int, float> min(0, 0);
    array<measure, NB_SCORES> scores{};

#pragma omp parallel for private(i, j, interval, union_set, score) shared(entity, min, scores, inserted_values)
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

            score = (float) interval / (float) union_set.size();

            if (inserted_values < 1000) {
                scores[inserted_values++].set(i, j, score);
            } else {
                if (score < min.second) {

#pragma omp critical
{
                    scores[inserted_values++].set(i, j, score);

                    update_min(min, scores);
}

                }
            }
        }
    }
    log(scores);
}

void Jaccard::log(array<measure, NB_SCORES> & scores) {
    string output;
    ofstream output_file(get_enron_path().append("/Jaccard_Measures.txt"));

    for(measure m : scores) {
        output = ("#" + to_string(m.mail_id_A + 1) + " - #" + to_string(m.mail_id_B + 1) + " "
                  + to_string(m.score) + "\n");
        output_file << output;
    }

    output_file.close();
}

