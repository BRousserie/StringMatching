#include "enron.h"
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>


enron::enron() {
    data = new map<string, int>;
}


enron* enron::singleton;
// Enron is a singleton class. Its entity is accessed by this static function.
enron* enron::get() {
    if (!enron::singleton) {
        enron::singleton = new enron();
        enron::singleton->parse();
    }
    return enron::singleton;
}


// My path to maildir - will try to make it relative later using readlink
const char* const enron_path = "/home/baptiste/dev/internship/maildir/";

// Associates each word in enron inboxes with a different number and returns them as a map
map<string, int>* enron::parse() {
    DIR * enron_dir;
    struct dirent *enron_ent; //enron_ent contains one folder for each user

    DIR * user_dir;
    struct dirent *user_ent; //user_ent contains several folders

    DIR * rep_dir;
    struct dirent *rep_ent; //rep_ent contains the user e-mails


    if ((enron_dir = opendir(enron_path)) == NULL) {
        cout << "Error(" << errno << ") opening enron folder through " << enron_path << endl;
        return nullptr;
    }

    while ((enron_ent = readdir(enron_dir)) != NULL) {

        string user_path = enron_path;
        user_path.append(enron_ent->d_name);

        if ((user_dir = opendir(user_path.c_str())) == NULL) {
            cout << "Error(" << errno << ") opening user folder through " << user_path << endl;
            return nullptr;
        }

        while ((user_ent = readdir(user_dir)) != NULL) {

            string rep_path = user_path;
            rep_path.append("/");
            rep_path.append(user_ent->d_name);

            if((rep_dir = opendir(rep_path.c_str())) == NULL) {
                if (!add_words_from(rep_path)) {
                    cout << "Error(" << errno << ") opening mail folder through " << rep_path << endl;
                    return nullptr;
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

bool enron::add_words_from(string & input_path) {
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
    for (auto& [key, value]: *data)
        cout << key << " - " << value << "\n";
}