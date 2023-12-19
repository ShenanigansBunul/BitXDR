//
// Created by sergi on 12/18/2023.
//

#include "Alert.h"
#include "../InputItems.h"

Alert::Alert(const json &json) {
    id = json["id"];
    timestamp = json["timestamp"];
    name = json["name"];
    score = json["score"];
    for (const auto &i: json["affected_entities"]) {
        affected_entities.push_back(i);
    }
}

long Alert::getId() const {
    return id;
}

long long Alert::getTimestamp() const {
    return timestamp;
}

const string &Alert::getName() const {
    return name;
}

int Alert::getScore() const {
    return score;
}

const vector<long> &Alert::getAffectedEntities() const {
    return affected_entities;
}
