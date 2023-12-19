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
        string input_file_path = string(argv[1]);
        ifstream input_file(input_file_path);
        if (!input_file) {
            cout << "input file does not exist";
        } else {
            if (input_file.is_open()) {
                string line;
                string input_string;
                while (getline(input_file, line)) {
                    input_string += line;
                }
                json input_json{json::parse(input_string)};
                InputItems input_obj = InputItems(input_json[0]);
                cout << "created input object\n";
                Output o = Output(input_obj);
                ordered_json q(o);
                cout << q.dump(4, ' ');
            }
        }
    }
    return 0;
}
