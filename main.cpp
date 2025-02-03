#include <cstring>
#include <iostream>
#include <fstream>
#include "json.h"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[]) {
    if (argc == 3) {
        // -- Show-infos command
        if (strcmp(argv[2], "show-infos") == 0) {
            json file = json::parse(ifstream(argv[1]));

            // Name
            cout << "Name : ";
            try {
                auto modules = file.at("Modules");
                for (auto & module : modules) {
                    if (module.at("Type") == "Runtime") {
                        string name = module.at("Name");
                        cout << name << endl;
                    }
                }
            } catch (...) {
                cout << "Not found" << endl;
            }

            // Version
            cout << "Version : ";
            try {
                string version = to_string(file.at("EngineAssociation"));
                version = version.substr(1, version.length()-2);
                cout << ((version[0] == '{') ? "From source" : version) << endl;
            } catch (...) {
                cout << "Not found" << endl;
            }

            // Plugins
            cout << "Plugins : ";
            try {
                auto plugins = file.at("Plugins");
                for (auto & plugin : plugins) cout << endl << "\t" << plugin.at("Name");
                cout << endl;
            } catch (...) {
                cout << "Not found" << endl;
            }

            return 0;
        }

        // -- Build project
        if (strcmp(argv[2], "build") == 0) {
            string command = R"(.\Engine\Build\BatchFiles\Build)";
            #if defined(_WIN64)
                command+= ".bat";
            #elif defined(__linux__) || defined(__APPLE__)
                command+= ".sh";
            #else
                cout << "OS not recognized" << endl;
                return -1;
            #endif

            json file = json::parse(ifstream(argv[1]));

            // Get name
            string name;
            try {
                auto modules = file.at("Modules");
                for (auto & module : modules) if (module.at("Type") == "Runtime") name = module.at("Name");
            } catch (...) {
                name = "Unknown";
            }
            if (name.empty()) { name = "Unknown"; }

            // Configure command
            command+= " " + name;
            #if defined(_WIN64)
                command+= " Win64 Development";
            #elif defined(__linux__)
                command+= " Linux Development";
            #elif defined(__APPLE__)
                command+= " Mac Development";
            #endif
            command+= ' ' + argv[1];
            command+= " -waitmutex";

            system(command.c_str());

            return 0;
        }
    } else if (argc == 4) {
        // -- Package command
        if (strcmp(argv[2], "package") == 0) {
            return 0;
        }
    } else {
        cerr << "Bad usage" << endl;
        return -1;
    }

    return 0;
}