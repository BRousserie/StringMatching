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
    data = new map<string, int>;
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
    if ((dir = opendir(path.c_str())) == NULL) {
        // 2 - If it doesn't work, use it as a file
        if (!add_words_from(path)) {
            // 3 - If it doesn't work, there's an error
            cout << "Error(" << errno << ") opening " << path << endl;
        }
    } else {
        // Repeat these 3 steps on everything this folder contains
        while ((dirent = readdir(dir)) != NULL) {
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

// Adds to data the words that haven't been added yet, and associates them with a number
bool enron::add_words_from(string &input_path) {
    cout << input_path << "\n";
    ifstream input(input_path);

    if (input.is_open()) {
        string word;
        while (input >> word) {
            if ((*data).find(word) == (*data).end()) {
                (*data).emplace(word, (*data).size());
            }
        }
        input.close();
        return true;
    } else {
        return false;
    }
}

// Prints to the console each mapped word and its associated number
void enron::log() {
    for (auto&[key, value]: *data)
        cout << key << " - " << value << "\n";
}




// Associates each word in enron inboxes with a different number and returns them as a map
void enron::parse() {
    DIR *enron_dir;
    struct dirent *enron_ent; //enron_ent contains one folder for each user

    DIR *user_dir;
    struct dirent *user_ent; //user_ent contains several folders

    DIR *rep_dir;
    struct dirent *rep_ent; //rep_ent contains the user e-mails


    if ((enron_dir = opendir(enron_path)) == NULL) {
        cout << "Error(" << errno << ") opening enron folder through " << enron_path << endl;
    }

    while ((enron_ent = readdir(enron_dir)) != NULL) {

        string user_path = enron_path;
        user_path.append(enron_ent->d_name);

        if ((user_dir = opendir(user_path.c_str())) == NULL) {
            cout << "Error(" << errno << ") opening user folder through " << user_path << endl;
        }

        while ((user_ent = readdir(user_dir)) != NULL) {

            string rep_path = user_path;
            rep_path.append("/");
            rep_path.append(user_ent->d_name);

            if ((rep_dir = opendir(rep_path.c_str())) == NULL) {
                if (!add_words_from(rep_path)) {
                    cout << "Error(" << errno << ") opening mail folder through " << rep_path << endl;
                }
            }

            while (rep_dir != NULL && (rep_ent = readdir(rep_dir)) != NULL) {

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
}