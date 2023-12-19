#include <iostream>
#include <fstream>
#include "constants.h"
#include "json.hpp"
#include "InputItems.h"
#include "Output.h"
#include <string>

using namespace std;
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

void to_json(ordered_json &j, const Transition &transition) {
    j = {{"first_entity",  transition.getFirstEntity()},
         {"second_entity", transition.getSecondEntity()},
         {"alert_name",    transition.getAlertName()},
         {"alert_score",   transition.getAlertScore()}};
}

void to_json(ordered_json &j, const Output &output) {
    j = {
            {"summary",
                       {{"pcs", ordered_json(output.getPcs())},
                               {"users", ordered_json(output.getUsers())},
                               {"alerts", ordered_json(output.getAlerts())},
                               {"transitions", ordered_json(output.getTransitions())}
                       }
            },
            {"path", ordered_json(output.getPath())}
    };
}

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "usage: xdr.exe input.json output.json";
    } else {
        string inputFilePath = string(argv[1]);
        ifstream inputFile(inputFilePath);
        if (!inputFile) {
            cout << "input file does not exist";
        } else {
            if (inputFile.is_open()) {
                string line;
                string inputString;
                while (getline(inputFile, line)) {
                    inputString += line;
                }
                json inputJson{json::parse(inputString)};
                InputItems inputObj = InputItems(inputJson[0]);
                cout << "created input object\n";
                Output o = Output(inputObj);
                ordered_json q(o);
                cout << q.dump(4, ' ');
                //todo: write to file
                //todo: handle errors
                //todo: test local paths as well as global paths
            }
        }
    }
    return 0;
}
