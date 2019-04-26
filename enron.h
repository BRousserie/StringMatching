#include <map>
#include <string>
#include <array>
#include <set>
#include "App.h"

using namespace std;

#ifndef INTERNSHIP_ENRON_H
#define INTERNSHIP_ENRON_H
class enron {
private:
    //map<string, int>* words;   we currently don't use map for something else than encoding mails
    // Thus, it would be useless to restore it
    array<set<int>, NB_MAILS>* mails;
    static enron* singleton;

public:
    void save();
    void log();

    //map<string, int>* get_words();
    array<set<int>, NB_MAILS>* get_mails();
    static enron* get();

private:
    enron();
    bool setup_enron_data();

    //void restore_map(ifstream & input_file);
    void restore_mails(ifstream & input_file);

    bool read_file_at(const string & file_path, map<string, int>* dictionary);
    void extract_data_from(ifstream &input, map<string, int>* dictionary);

    void recursiveParse(const string &path);
    //
    // void parse();
};

#endif //INTERNSHIP_ENRON_H
