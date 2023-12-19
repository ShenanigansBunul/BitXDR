//
// Created by sergi on 12/18/2023.
//

#ifndef BITXDR_PC_H
#define BITXDR_PC_H

#include<string>
#include "../json.hpp"

using json = nlohmann::json;
using namespace std;

class PC {
    long id;
public:
    [[nodiscard]] long getId() const;

private:
    string computer_name;
    string ip;
    string mac;

public:
    explicit PC(const json &json);
};


#endif //BITXDR_PC_H
