//
// Created by sergi on 12/18/2023.
//

#include "PC.h"

PC::PC(const json &json) {
    id = json["id"];
    computer_name = json["computer_name"];
    ip = json["ip"];
    mac = json["mac"];
}

long PC::getId() const {
    return id;
}
