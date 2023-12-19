//
// Created by sergi on 12/18/2023.
//

#ifndef BITXDR_USER_H
#define BITXDR_USER_H

#include<string>
#include "../json.hpp"

using json = nlohmann::json;
using namespace std;

class User {
    long id;
public:
    [[nodiscard]] long getId() const;

private:
    string email;
    string nickname;

public:
    explicit User(const json &json);
};


#endif //BITXDR_USER_H
