//
// Created by sergi on 12/18/2023.
//

#include "InputItems.h"
#include "json.hpp"
#include<iostream>
#include "constants.h"

using json = nlohmann::json;

void from_json(const json &j, PC &pc) {
    j.at("id").get_to(pc.id);
    j.at("computer_name").get_to(pc.computer_name);
    j.at("ip").get_to(pc.ip);
    j.at("mac").get_to(pc.mac);
}

void from_json(const json &j, User &user) {
    j.at("id").get_to(user.id);
    j.at("email").get_to(user.email);
    j.at("nickname").get_to(user.nickname);
}

void from_json(const json &j, Alert &alert) {
    j.at("id").get_to(alert.id);
    j.at("timestamp").get_to(alert.timestamp);
    j.at("name").get_to(alert.name);
    j.at("score").get_to(alert.score);
    j.at("affected_entities").get_to(alert.affected_entities);
}

InputItems::InputItems(const json &json) {
    initializeFromJsonArray(json, "pcs", pcs, constants::message_input_pc_warning);
    initializeFromJsonArray(json, "users", users, constants::message_input_user_warning);
    initializeFromJsonArray(json, "alerts", alerts, constants::message_input_alert_warning);
    try {
        alert_that_generated_incident = json.at("alert_that_generated_incident");
    }
    catch (exception &e) {
        cout << constants::message_missing_incident_warning << '\n';
    }
    try {
        entities_for_highest_score_path = tuple<long, long>(json["entities_for_highest_score_path"][0],
                                                            json["entities_for_highest_score_path"][1]);
    }
    catch (exception &e) {
        cout << constants::message_missing_highest_score_path_entities << '\n';
    }
}

template<typename T>
void InputItems::initializeFromJsonArray(const json &j, const string &key, vector<T> &container,
                                         const string &errorMessage) {
    for (const auto &item: j.at(key)) {
        try {
            container.emplace_back(item);
        } catch (const exception &e) {
            cout << errorMessage << '\n' << e.what() << '\n';
        }
    }
}

const vector<PC> &InputItems::getPcs() const {
    return pcs;
}

const vector<User> &InputItems::getUsers() const {
    return users;
}

const vector<Alert> &InputItems::getAlerts() const {
    return alerts;
}

long InputItems::getAlertThatGeneratedIncident() const {
    return alert_that_generated_incident;
}

const tuple<long, long> &InputItems::getEntitiesForHighestScorePath() const {
    return entities_for_highest_score_path;
}

