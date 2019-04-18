#include <map>
#include <string>
#include <vector>

using namespace std;

#ifndef INTERNSHIP_ENRON_H
#define INTERNSHIP_ENRON_H
class enron {
private:
    map<string, int>* words;
    vector<vector<int>>* mails;
    static enron* singleton;

public:
    enron();
    void log();


    static enron* get();

private:
    bool read_file_at(string & file_path);
    void add_words_from(ifstream &input);

    void recursiveParse(string &path);
    //
    // void parse();
};

#endif //INTERNSHIP_ENRON_H
