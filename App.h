#ifndef INTERNSHIP_APP_H
#define INTERNSHIP_APP_H

#include <array>
#include <set>

using namespace std;

#define NB_THREADS 24
#define NB_MAILS 8656
#define NB_SCORES 1000
#define THRESHOLD 0.8
#define NB_MEASURES_PER_THREAD ((NB_MAILS/NB_THREADS) * (NB_MAILS - 1 - NB_MAILS/(2*NB_THREADS)))

struct measure {
    int mail_id_A, mail_id_B;
    float score;

    void set(int id_A, int id_B, float new_score);
};

string get_enron_path();
void update_min(pair<int, float>& min, const array<measure, NB_SCORES>& scores);
int intersection_of(const set<int> &setA, const set<int> &setB);

#endif //INTERNSHIP_APP_H
