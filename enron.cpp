#include "enron.h"
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <stdio.h>

const char * enron_path = "/proc/self/exe";
enron* enron::singleton;

enron::enron() {
    data = parse();
}

enron* enron::get() {
    if (!enron::singleton) enron::singleton = new enron();
    return enron::singleton;
}

map<string, int>* enron::parse() {
    map<string, int>* enron;
    DIR * enrondir;
    struct dirent *enronuser;

    if((enrondir = opendir(enron_path)) == NULL) {
        cout << "Error(" << errno << ") opening " << enron_path << endl;
        return nullptr;
    }

    DIR * userinbox;
    struct dirent *inboxfile;
    fstream mail;
    string word;
    while ((enronuser = readdir(enrondir)) != NULL) {
        string path = enronuser->d_name;
        path.append("/inbox/");

        if((userinbox = opendir(path.c_str())) == NULL) {
            cout << "Error(" << errno << ") opening " << enron_path << endl;
            return nullptr;
        }

        while ((inboxfile = readdir(userinbox)) != NULL) {

            mail.open(inboxfile->d_name);

            while (mail >> word) {
                if ((*enron)[word] == 0)
                    (*enron)[word] = enron->size();
            }

            mail.close();
        }
    }
    closedir(userinbox);
    closedir(enrondir);

    return enron;
}

void enron::log() {
    for (auto& [key, value]: *data)
        cout << key << " - " << value;
}