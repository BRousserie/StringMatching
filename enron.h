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
    map<string, int>* parse();
    void log();

    static enron* get();

private:
    bool add_words_from(string & input_path);
};

#endif //INTERNSHIP_ENRON_H
