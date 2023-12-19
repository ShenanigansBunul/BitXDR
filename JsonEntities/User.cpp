//
// Created by sergi on 12/18/2023.
//

#include "User.h"

User::User(const json &json) {
    id = json["id"];
    email = json["email"];
    nickname = json["nickname"];
}

long User::getId() const {
    return id;
}
