#include <map>
#include <string>

using namespace std;

#ifndef INTERNSHIP_ENRON_H
#define INTERNSHIP_ENRON_H
class enron {
private:
    map<string, int>* data;
    static enron* singleton;

public:
    enron();
    void log();

    static enron* get();

private:
    void recursiveParse(string & path);
    void parse();
    bool add_words_from(string & input_path);
};

#endif //INTERNSHIP_ENRON_H
