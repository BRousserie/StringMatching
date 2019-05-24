#include <climits>
#include <string>
#include <unistd.h>
#include <iostream>
#include "App.h"

string get_enron_path() {
    char buff[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1);
    if (len != -1) {
        buff[len] = '\0';
        string path(buff);
        string undesired_part("/StringMatching/bin/Debug/StringMatching");
        path = path.substr(0, path.size() - undesired_part.size());
        return path.append("/maildir");
    } else {
        cout << "Error with program path";
        return nullptr;
    }
}

void update_min(pair<int, float>& min, const array<measure, NB_SCORES>& scores) {
    min.second = scores[0].score;
    min.first = 0;
    for(int i = 1; i < scores.size(); i++) {
        if (scores[i].score < min.second) {
            min.second = scores[i].score;
            min.first = i;
        }
    }
}

int intersection_of(const set<int> &setA, const set<int> &setB) {
    int intersection = 0;
    int nb_words_remaining = setA.size();

    for (int A : setA) {
        if (setB.find(A) != setB.end())
            intersection++;

        if ((float)( intersection + (--nb_words_remaining)) / setA.size() < THRESHOLD) {
            return -1;
        }
    }
    return intersection;
}

void measure::set(int id_A, int id_B, float new_score) {
    mail_id_A = id_A;
    mail_id_B = id_B;
    score = new_score;
}
