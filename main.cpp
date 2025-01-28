#include <cstring>
#include <iostream>
#include <fstream>
#include "json.h"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[]) {
    if (argc == 3) {
        // Show-infos command
        if (strcmp(argv[2], "show-infos") == 0) {
            clog << "[LOG] show-infos commands called" << endl;

            json file = json::parse(ifstream(argv[1]));

            return 0;
        }

        // Build project
        if (strcmp(argv[2], "build") == 0) {
            return 0;
        }
    } else if (argc == 4) {
        // Package command
        if (strcmp(argv[2], "package") == 0) {
            return 0;
        }
    } else {
        cerr << "Bad usage" << endl;
        return -1;
    }

    return 0;
}