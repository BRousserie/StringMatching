#include <fstream>
#include <iostream>
#include <iomanip>
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
    set<int> union_set;
    float score;
    pair<int, float> min(0, 0);
    array<measure, NB_SCORES> scores{};
    float percentage;
    int nb_measures_done = 1;

    cout << fixed << setprecision(4);

#pragma omp parallel for private(i, j, interval, union_set, score) shared(entity, min, scores, nb_measures_done, percentage) reduction(+: inserted_values) num_threads(NB_THREADS)
    for (i = 0; i < NB_MAILS; i++) {
        for (j = i + 1; j < NB_MAILS; j++) {

            const set<int> &setA = (*entity.get_mails())[i];
            const set<int> &setB = (*entity.get_mails())[j];

            if (setA.size() / THRESHOLD > setB.size() && setB.size() > setA.size() * THRESHOLD ) {
                interval = 0;

                for (int A : setA) {
                    for (int B : setB) {

                        if (A == B) interval++;

                    }
                }

                union_set = setA;
                union_set.insert(setB.begin(), setB.end());

                score = (float) interval / (float) union_set.size();

                if (inserted_values < NB_SCORES) {
                    scores[inserted_values++].set(i, j, score);
                } else {
                    if (score > min.second) {
#pragma omp critical
{
                        scores[min.first].set(i, j, score);
                        update_min(min, scores);
}
                    }
                }
            }

            if (omp_get_thread_num() == 0) {
                percentage = 100 *  ((float)nb_measures_done++ / NB_MEASURES_PER_THREAD);
                cout << percentage << "% completed : " << nb_measures_done << " measures done (1st thread)\n" ;
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

