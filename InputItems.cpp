//
// Created by sergi on 12/18/2023.
//

#include "InputItems.h"
#include "json.hpp"
using json = nlohmann::json;

InputItems::InputItems(const json& json) {
    for(const auto & i : json["pcs"]){
        pcs.emplace_back(i);
    }
    for(const auto & i : json["users"]){
        users.emplace_back(i);
    }
    for(const auto & i : json["alerts"]){
        alerts.emplace_back(i);
    }
    alert_that_generated_incident = json["alert_that_generated_incident"];
    entities_for_highest_score_path = tuple<long, long>(json["entities_for_highest_score_path"][0], json["entities_for_highest_score_path"][1]);
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

const tuple<long, long> & InputItems::getEntitiesForHighestScorePath() const {
    return entities_for_highest_score_path;
}

