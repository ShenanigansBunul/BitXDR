//
// Created by sergi on 12/19/2023.
//

#ifndef BITXDR_OUTPUT_H
#define BITXDR_OUTPUT_H

#include<vector>
#include "JsonEntities/PC.h"
#include "JsonEntities/User.h"
#include "JsonEntities/Alert.h"
#include "JsonEntities/Transition.h"
#include "json.hpp"
#include "InputItems.h"

using ordered_json = nlohmann::ordered_json;
using namespace std;

class Output {
private:
    long long m_incidentTimestamp{};

    vector<long> m_allEntities;
    vector<long> m_affectedEntities;
    vector<Alert> m_alertsInRange;

    vector<long> m_pcs;
    vector<long> m_users;
    vector<long> m_alerts;
    vector<Transition> m_transitions;
    vector<Transition> m_path;

    void getAllEntities(const vector<PC> &inputPcs, const vector<User> &inputUsers);

    void computeSummary(long alertThatGeneratedIncident,
                        const vector<Alert> &inputAlerts);

    void computePath(tuple<long, long> entitiesForHighestScorePath);

    vector<long> getEntitiesFromAlert(const Alert &alert, long previousEntity = -1);

    vector<tuple<Alert, int>> getAlertsFromEntity(long entity_id);

    void mapAffectedEntities(const vector<PC> &inputPcs,
                             const vector<User> &inputUsers);

    void sortOutputLists();

public:
    explicit Output(const InputItems &input);

    [[nodiscard]] const vector<long> &getPcs() const;

    [[nodiscard]] const vector<long> &getUsers() const;

    [[nodiscard]] const vector<long> &getAlerts() const;

    [[nodiscard]] const vector<Transition> &getTransitions() const;

    [[nodiscard]] const vector<Transition> &getPath() const;
};


#endif //BITXDR_OUTPUT_H
