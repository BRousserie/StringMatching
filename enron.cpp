#include "enron.h"
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <cstdio>
#include <unistd.h>
#include <cstring>


enron::enron() {
    mails = new array<set<int>, NB_MAILS>;

    setup_enron_data();
}


enron* enron::singleton;

// Enron is a singleton class. Its entity is accessed by this static function.
enron *enron::get() {
    if (!enron::singleton) enron::singleton = new enron();
    return enron::singleton;
}


// Associates each word in enron inboxes with a different number and returns them as a map
void enron::recursiveParse(const string &path) {
    static map<string, int>* dictionary = new map<string, int>;
    DIR *dir;
    struct dirent *dirent;

    string child_path;

    // 1 - Use path as a folder
    if ((dir = opendir(path.c_str())) == nullptr) {
        // 2 - If it doesn't work, use it as a file
        if (!read_file_at(path, dictionary)) {
            // 3 - If it doesn't work, there's an error
            cout << "Error(" << errno << ") opening " << path << endl;
        }
    } else {
        // Repeat these 3 steps on everything this folder contains
        while ((dirent = readdir(dir)) != nullptr) {
            // Avoid infinite recursion
            if (strcmp(dirent->d_name, "..") && strcmp(dirent->d_name, ".")) {

                child_path = path;
                child_path.append("/");
                child_path.append(dirent->d_name);

                recursiveParse(child_path);

            }
        }
    }
    closedir(dir);
    delete(dictionary);
}

// Opens the file and calls the necessary methods to build
bool enron::read_file_at(const string &file_path, map<string, int>* dictionary) {
    ifstream input(file_path);

    if (input.is_open()) {
        extract_data_from(input, dictionary);

        input.close();
        return true;
    } else {
        return false;
    }

}

// Adds to enron::words the words that haven't been added yet, and associates them with a number
void enron::extract_data_from(ifstream &input, map<string, int>* dictionary) {
    static int i = 0;
    set<int> words_to_int;
    string word;

    while (input >> word) {
        if ((*dictionary).find(word) == (*dictionary).end()) {
            (*dictionary).emplace(word, (*dictionary).size());
        }
        words_to_int.emplace((*dictionary)[word]);
    }
    mails->at(i++) = words_to_int;
}

// Outputs data in files on disk
void enron::save() {
    ofstream mails_stream(get_enron_path().append("/mails.txt"), ofstream::out);

    for (const set<int> &set : (*mails)) {
        for (int id : set) {
            mails_stream << id << " ";
        }
        mails_stream << "\n";
    }
}

void enron::setup_enron_data() {
    ifstream mails_file(get_enron_path().append("/mails.txt"), ifstream::in);

    if (mails_file.is_open()) {
        restore_mails(mails_file);

        mails_file.close();
    } else {
        cout << "Data not found at " << get_enron_path() << ", now parsing enron database...\n";
        recursiveParse(get_enron_path());
        save();
    }
}

void enron::restore_mails(ifstream &input_file) {
    string str_line;
    set<int> mail;

    static int i = 0;

    while (getline(input_file, str_line)) {
        size_t pos = str_line.find(' ');
        size_t initialPos = 0;
        mail.clear();

        // Decompose statement
        while (pos != std::string::npos) {
            mail.emplace(stoi(str_line.substr(initialPos, pos - initialPos)));
            initialPos = pos + 1;

            pos = str_line.find(' ', initialPos);
        }

        mails->at(i++) = mail;
    }
}

void enron::log() {
    cout << "Treating " << mails->size() << " mails\n";
}

array<set<int>, NB_MAILS>* enron::get_mails() {
    return mails;
}