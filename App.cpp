#include <climits>
#include <string>
#include <unistd.h>
#include <iostream>
#include "App.h"

string get_enron_path() {
    char buff[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1);
    if (len != -1) {
        buff[len] = '\0';
        string path(buff);
        string undesired_part("/StringMatching/bin/Debug/StringMatching");
        path = path.substr(0, path.size() - undesired_part.size());
        return path.append("/maildir");
    } else {
        cout << "Error with program path";
        return nullptr;
    }
}