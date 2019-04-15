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
};

#endif //INTERNSHIP_ENRON_H
