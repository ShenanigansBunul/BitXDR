//
// Created by sergi on 12/18/2023.
//

#ifndef BITXDR_ALERT_H
#define BITXDR_ALERT_H
#include<string>
#include<vector>
#include "../json.hpp"
using json = nlohmann::json;
using namespace std;

class Alert {
    long id;
    long long timestamp;
    string name;
    int score;
    vector<long> affected_entities;
public:
    [[nodiscard]] long getId() const;

    [[nodiscard]] long long getTimestamp() const;

    [[nodiscard]] const string &getName() const;

    [[nodiscard]] int getScore() const;

    [[nodiscard]] const vector<long> &getAffectedEntities() const;

public:
    explicit Alert(const json &json);
};


#endif //BITXDR_ALERT_H
