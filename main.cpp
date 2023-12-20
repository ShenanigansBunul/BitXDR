#include <iostream>
#include <fstream>
#include "constants.h"
#include "json.hpp"
#include "InputItems.h"
#include "Output.h"
#include <string>
#include <chrono>

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

void writeToFile(const string &filePath, const string &content) {
    ofstream outputFile(filePath, ofstream::out | ofstream::trunc);
    if (outputFile.is_open()) {
        outputFile << content;
        outputFile.close();
    } else {
        cout << constants::message_output_file_not_open;
    }
}

template <typename Func>
double measureExecutionTime(Func&& func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(end - start);
    return duration.count();
}

int main(int argc, char **argv) {
    double elapsedTime = measureExecutionTime([argc, argv] {
        if (argc != 3) {
            cout << constants::message_instructions << '\n';
        } else {
            string inputFilePath = string(argv[1]);
            string outputFilePath = string(argv[2]);
            ifstream inputFile(inputFilePath);
            if (inputFile) {
                if (inputFile.is_open()) {
                    string line;
                    string inputString;
                    while (getline(inputFile, line)) {
                        inputString += line;
                    }
                    try {
                        json inputJson{json::parse(inputString)};
                        InputItems inputObj = InputItems(inputJson[0]);
                        Output o = Output(inputObj);
                        ordered_json q(o);
                        writeToFile(outputFilePath, q.dump(4, ' '));
                    }
                    catch (const json::parse_error &e) {
                        cout << constants::message_input_parse_error << '\n' << e.what();
                    }
                } else {
                    cout << constants::message_input_file_not_open;
                }
            } else {
                cout << constants::message_input_file_nonexistent;
            }
        }
    });
    if(constants::print_measured_time) {
        cout << "Elapsed Time: " << elapsedTime << "s" << std::endl;
    }
    return 0;
}
