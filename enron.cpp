#include "enron.h"
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <cstdio>
#include <unistd.h>
#include <cstring>


// My path to maildir - will try to make it relative later using readlink
const char *const enron_path = "/home/baptiste/dev/internship/maildir";

enron::enron() {
    words = new map<string, int>;
    mails = new vector<vector<int>>();
}


enron *enron::singleton;

// Enron is a singleton class. Its entity is accessed by this static function.
enron *enron::get() {
    if (!enron::singleton) {
        enron::singleton = new enron();
        string path(enron_path);
        enron::singleton->recursiveParse(path);
    }
    return enron::singleton;
}


// Associates each word in enron inboxes with a different number and returns them as a map
void enron::recursiveParse(string &path) {
    DIR *dir;
    struct dirent *dirent;

    string child_path;

    // 1 - Use path as a folder
    if ((dir = opendir(path.c_str())) == nullptr) {
        // 2 - If it doesn't work, use it as a file
        if (!read_file_at(path)) {
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
}

// Opens the file and calls the necessary methods to build
bool enron::read_file_at(string & file_path) {
    cout << file_path << "\n";
    ifstream input(file_path);

    if (input.is_open()) {
        add_words_from(input);

        input.close();
        return true;
    } else {
        return false;
    }

}

// Adds to enron::words the words that haven't been added yet, and associates them with a number
void enron::add_words_from(ifstream & input) {
    vector<int> words_to_int;
    string word;

    while (input >> word) {
        if ((*words).find(word) == (*words).end()) {
            (*words).emplace(word, (*words).size());
        }
        words_to_int.push_back((*words)[word]);
    }
    mails->push_back(words_to_int);
}

// Prints to the console each mapped word and its associated number
void enron::log() {
    /* Log all keys and their value
     *
     * for (auto&[key, value]: *words)
     *   cout << key << " - " << value << "\n";
     */

    cout << words->size() << " words in the dictionnary" << "\n";
    cout << mails->size() << " mails have been numerized"<< "\n";

    for (vector<int> v : (*mails)) {
        static int id = 1;
        cout << id++ << " : ";
        for (int i : v) {
            cout << i << " ";
        }
        cout << "\n";
    }
}



/*
// Associates each word in enron inboxes with a different number and returns them as a map
void enron::parse() {
    DIR *enron_dir;
    struct dirent *enron_ent; //enron_ent contains one folder for each user

    DIR *user_dir;
    struct dirent *user_ent; //user_ent contains several folders

    DIR *rep_dir;
    struct dirent *rep_ent; //rep_ent contains the user e-mails


    if ((enron_dir = opendir(enron_path)) == nullptr) {
        cout << "Error(" << errno << ") opening enron folder through " << enron_path << endl;
    }

    while ((enron_ent = readdir(enron_dir)) != nullptr) {

        string user_path = enron_path;
        user_path.append(enron_ent->d_name);

        if ((user_dir = opendir(user_path.c_str())) == nullptr) {
            cout << "Error(" << errno << ") opening user folder through " << user_path << endl;
        }

        while ((user_ent = readdir(user_dir)) != nullptr) {

            string rep_path = user_path;
            rep_path.append("/");
            rep_path.append(user_ent->d_name);

            if ((rep_dir = opendir(rep_path.c_str())) == nullptr) {
                if (!add_words_from(rep_path)) { // some mails are directly saved in the user folder
                    cout << "Error(" << errno << ") opening mail folder through " << rep_path << endl;
                }
            }

            while (rep_dir != nullptr && (rep_ent = readdir(rep_dir)) != nullptr) {

                string file_path = rep_path;
                file_path.append("/");
                file_path.append(rep_ent->d_name);

                add_words_from(file_path);
            }
            closedir(rep_dir);
        }
        closedir(user_dir);
    }
    closedir(enron_dir);
}*/
