//
// Created by sergi on 12/19/2023.
//

#include <iostream>
#include "Output.h"
#include "JsonEntities/Transition.h"
#include "constants.h"
#include "PathGraph.h"

/**
 * Using an InputItems object, generate the summary and the highest score path.
 * @param input
 */
Output::Output(const InputItems &input) {
    getAllEntities(input.getPcs(), input.getUsers());

    computeSummary(input.getAlertThatGeneratedIncident(), input.getAlerts());
    mapAffectedEntities(input.getPcs(), input.getUsers());

    computePath(input.getEntitiesForHighestScorePath());

    sortOutputLists();
}

/**
 * Map affected entities to the m_pcs and m_users member functions of the class.
 * @param inputPcs
 * @param inputUsers
 */
void Output::mapAffectedEntities(const vector<PC> &inputPcs, const vector<User> &inputUsers) {
    for (auto &entityIt: m_affectedEntities) {
        if (find_if(inputPcs.begin(), inputPcs.end(),
                    [&entityIt](const PC &obj) { return obj.id == entityIt; }) != inputPcs.end()) {
            m_pcs.push_back(entityIt);
        } else if (find_if(inputUsers.begin(), inputUsers.end(),
                           [&entityIt](const User &obj) { return obj.id == entityIt; }) != inputUsers.end()) {
            m_users.push_back(entityIt);
        }
    }
}

/**
 * Populate the m_allEntities member of the class using the IDs from the PCs and Users in the input data.
 * @param inputPcs
 * @param inputUsers
 */
void Output::getAllEntities(const vector<PC> &inputPcs, const vector<User> &inputUsers) {
    for (auto &it: inputPcs) {
        m_allEntities.push_back(it.id);
    }
    for (auto &it: inputUsers) {
        m_allEntities.push_back(it.id);
    }
}

/**
 * Using the ID of the alert that generated the incident and specified alerts, generate info necessary for the summary.
 * @param alertThatGeneratedIncident
 * @param inputAlerts The alerts to be used for the summary. This list is filtered to only include alerts 2 hours away from the one that generated the incident or closer.
 */
void Output::computeSummary(long alertThatGeneratedIncident,
                            const vector<Alert> &inputAlerts) {
    auto incidentIt = find_if(inputAlerts.begin(), inputAlerts.end(),
                              [&alertThatGeneratedIncident](const Alert &obj) {
                                  return obj.id == alertThatGeneratedIncident;
                              });
    if (incidentIt != inputAlerts.end()) {
        const Alert &incidentAlert = incidentIt[0];
        m_alerts.push_back(incidentAlert.id);
        m_incidentTimestamp = incidentAlert.timestamp;
        copy_if(inputAlerts.begin(), inputAlerts.end(), back_inserter(m_alertsInRange), [this](const Alert &obj) {
            return (abs(obj.timestamp - m_incidentTimestamp) <= constants::incidentDeltaTime);
        });
        vector<long> summaryEntities = getEntitiesFromAlert(incidentAlert);
        vector<tuple<Alert, int>> summaryAlerts{};
        while (!summaryEntities.empty()) {
            summaryAlerts.clear();
            for (const auto &it: summaryEntities) {
                vector<tuple<Alert, int>> alertsFromEntity = getAlertsFromEntity(it);
                summaryAlerts.insert(summaryAlerts.end(), alertsFromEntity.begin(), alertsFromEntity.end());
            }
            summaryEntities.clear();
            for (const auto &it: summaryAlerts) {
                vector<long> entitiesFromAlert = getEntitiesFromAlert(get<0>(it), get<1>(it));
                summaryEntities.insert(summaryEntities.end(), entitiesFromAlert.begin(), entitiesFromAlert.end());
            }
        }
    } else {
        cout << constants::message_incident_not_found_error << '\n';
    }
}

/**
 * Using the PathGraph class, compute the highest score path between two given entities.
 * @param entitiesForHighestScorePath
 */
void Output::computePath(tuple<long, long> entitiesForHighestScorePath) {
    PathGraph p = PathGraph(m_transitions);
    m_path = p.computeLongestPath(get<0>(entitiesForHighestScorePath), get<1>(entitiesForHighestScorePath));
}

/**
 * Given an Alert object, populate a vector with all the entities it affected.
 * Additionally, populate the m_transitions member of the Output class with transitions that are not added yet, and
 * populate the m_affectedEntities member with entities that have not been added yet.
 * @param alert
 * @param previousEntity Optionally specify the previous entity ID, if the alert originated from another entity.
 * @return
 */
vector<long> Output::getEntitiesFromAlert(const Alert &alert, long previousEntity) {
    vector<long> result{};
    for (auto &it: alert.affected_entities) {
        if (find(m_affectedEntities.begin(), m_affectedEntities.end(), it) == m_affectedEntities.end()) {
            m_affectedEntities.push_back(it);
            result.push_back(it);
        }
        if (previousEntity != -1 && previousEntity != it) {
            Transition t = Transition(previousEntity, it, alert.name, alert.score);
            if (find_if(m_transitions.begin(), m_transitions.end(),
                        [&t](const Transition &obj) { return (obj == t); }) ==
                m_transitions.end()) {
                m_transitions.push_back(t);
            }
        }
    }
    return result;
}

/**
 * Given an entity ID, populate a vector with tuples of all the alerts that have affected it, along with the id.
 * Additionally, populate the m_alerts member of the Output class with alerts that have not been added yet.
 * @param entity_id
 * @return
 */
vector<tuple<Alert, int>> Output::getAlertsFromEntity(const long entity_id) {
    vector<tuple<Alert, int>> result{};
    for (auto &it: m_alertsInRange) {
        if (abs(it.timestamp - m_incidentTimestamp) <= constants::incidentDeltaTime) {
            if (find(it.affected_entities.begin(), it.affected_entities.end(), entity_id) !=
                it.affected_entities.end()) {
                if (find(m_alerts.begin(), m_alerts.end(), it.id) == m_alerts.end()) {
                    m_alerts.push_back(it.id);
                }
                result.emplace_back(it, entity_id);
            }
        }
    }
    return result;
}

/**
 * Sort lists in the output JSON for easier readability.
 */
void Output::sortOutputLists() {
    sort(m_pcs.begin(), m_pcs.end());
    sort(m_users.begin(), m_users.end());
    sort(m_alerts.begin(), m_alerts.end());
}

const vector<long> &Output::getPcs() const {
    return m_pcs;
}

const vector<long> &Output::getUsers() const {
    return m_users;
}

const vector<long> &Output::getAlerts() const {
    return m_alerts;
}

const vector<Transition> &Output::getTransitions() const {
    return m_transitions;
}

const vector<Transition> &Output::getPath() const {
    return m_path;
}
