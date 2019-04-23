#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

#ifndef INTERNSHIP_ENRON_H
#define INTERNSHIP_ENRON_H
class enron {
private:
    map<string, int>* words;
    vector<set<int>>* mails;
    static enron* singleton;

public:
    void save();
    void log();

    map<string, int>* get_words();
    vector<set<int>>* get_mails();
    static enron* get();

private:
    enron();
    bool setup_enron_data();

    void restore_map(ifstream & input_file);
    void restore_mails(ifstream & input_file);

    bool read_file_at(const string & file_path);
    void extract_data_from(ifstream &input);

    void recursiveParse(const string &path);
    //
    // void parse();
};

#endif //INTERNSHIP_ENRON_H
