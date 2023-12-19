//
// Created by sergi on 12/19/2023.
//

#include <iostream>
#include "Output.h"
#include "JsonEntities/Transition.h"
#include "constants.h"

Output::Output(const InputItems &input) {
    get_all_entities(input.getPcs(), input.getUsers());

    compute_summary(input.getAlertThatGeneratedIncident(), input.getAlerts());
    map_affected_entities(input.getPcs(), input.getUsers());

    compute_path(input.getEntitiesForHighestScorePath(), input.getAlerts());
    //todo: write output to file
}

void Output::map_affected_entities(const vector<PC> &input_pcs, const vector<User> &input_users) {
    for (auto &entityIt: affectedEntities) {
        if (find_if(input_pcs.begin(), input_pcs.end(),
                    [&entityIt](const PC &obj) { return obj.getId() == entityIt; }) != input_pcs.end()) {
            pcs.push_back(entityIt);
        } else if (find_if(input_users.begin(), input_users.end(),
                           [&entityIt](const User &obj) { return obj.getId() == entityIt; }) != input_users.end()) {
            users.push_back(entityIt);
        }
    }
}

void Output::get_all_entities(const vector<PC> &input_pcs, const vector<User> &input_users) {
    for (auto &it: input_pcs) {
        allEntities.push_back(it.getId());
    }
    for (auto &it: input_users) {
        allEntities.push_back(it.getId());
    }
}

void Output::compute_summary(const long alertThatGeneratedIncident,
                             const vector<Alert> &input_alerts) {
    auto incidentIt = find_if(input_alerts.begin(), input_alerts.end(),
                              [&alertThatGeneratedIncident](const Alert &obj) {
                                  return obj.getId() == alertThatGeneratedIncident;
                              });
    if (incidentIt != input_alerts.end()) {
        const Alert &incidentAlert = incidentIt[0];
        alerts.push_back(incidentAlert.getId());
        incidentTimestamp = incidentAlert.getTimestamp();
        copy_if(input_alerts.begin(), input_alerts.end(), back_inserter(alertsInRange), [this](const Alert &obj) {
            return (abs(obj.getTimestamp() - incidentTimestamp) <= incident_delta_time);
        });
        //get_entities_from_alert(incidentAlert);
        vector<long> summary_entities = get_entities_from_alert(incidentAlert);
        vector<tuple<Alert, int>> summary_alerts{};
        while (!summary_entities.empty()) {
            summary_alerts.clear();
            for (const auto &it: summary_entities) {
                vector<tuple<Alert, int>> alertsFromEntity = get_alerts_from_entity(it);
                summary_alerts.insert(summary_alerts.end(), alertsFromEntity.begin(), alertsFromEntity.end());
            }
            summary_entities.clear();
            for (const auto &it: summary_alerts) {
                vector<long> entitiesFromAlert = get_entities_from_alert(get<0>(it), get<1>(it));
                summary_entities.insert(summary_entities.end(), entitiesFromAlert.begin(), entitiesFromAlert.end());
            }
        }
    } else {
        cout << "not found alert that generated incident!!";
    }
}

//todo: implement (topological sort)
void Output::compute_path(const tuple<long, long> entitiesForHighestScorePath,
                          const vector<Alert> &input_alerts) {

}

vector<long> Output::get_entities_from_alert(const Alert &alert, const long previous_entity) {
    vector<long> result{};
    for (auto &it: alert.getAffectedEntities()) {
        if (find(affectedEntities.begin(), affectedEntities.end(), it) == affectedEntities.end()) {
            cout << it << endl;
            affectedEntities.push_back(it);
            result.push_back(it);
        }
        if (previous_entity != -1 && previous_entity != it) {
            Transition t = Transition(previous_entity, it, alert.getName(), alert.getScore());
            if (find_if(transitions.begin(), transitions.end(), [&t](const Transition &obj) { return (obj == t); }) ==
                transitions.end()) {
                transitions.push_back(t);
            }
        }
    }
    return result;
}

vector<tuple<Alert, int>> Output::get_alerts_from_entity(const long entity_id) {
    vector<tuple<Alert, int>> result{};
    for (auto &it: alertsInRange) {
        if (abs(it.getTimestamp() - incidentTimestamp) <= incident_delta_time) {
            if (find(it.getAffectedEntities().begin(), it.getAffectedEntities().end(), entity_id) !=
                it.getAffectedEntities().end()) {
                if (find(alerts.begin(), alerts.end(), it.getId()) == alerts.end()) {
                    alerts.push_back(it.getId());

                    result.emplace_back(it, entity_id);
                }
            }
        }
    }
    return result;
}

const vector<long> &Output::getPcs() const {
    return pcs;
}

const vector<long> &Output::getUsers() const {
    return users;
}

const vector<long> &Output::getAlerts() const {
    return alerts;
}

const vector<Transition> &Output::getTransitions() const {
    return transitions;
}

const vector<Transition> &Output::getPath() const {
    return path;
}
