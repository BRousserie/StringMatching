#ifndef INTERNSHIP_ENRON_H
#define INTERNSHIP_ENRON_H

#include <map>
#include <string>
#include <array>
#include <set>
#include "App.h"

using namespace std;

class enron {
private:
    array<set<int>, NB_MAILS>* mails;
    map<string, int>* dictionary;
    static enron* singleton;

public:
    void save();
    void log();

    static enron* get();
    array<set<int>, NB_MAILS>* get_mails();

private:
    enron();
    void setup_enron_data();
    void restore_mails(ifstream & input_file);

    void recursiveParse(const string &path);
    bool read_file_at(const string & file_path, map<string, int>* dictionary);
    void extract_data_from(ifstream &input, map<string, int>* dictionary);
};

#endif //INTERNSHIP_ENRON_H
