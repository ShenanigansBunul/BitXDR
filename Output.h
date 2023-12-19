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
public:
    [[nodiscard]] const vector<long> &getPcs() const;

    [[nodiscard]] const vector<long> &getUsers() const;

    [[nodiscard]] const vector<long> &getAlerts() const;

    [[nodiscard]] const vector<Transition> &getTransitions() const;

    [[nodiscard]] const vector<Transition> &getPath() const;

private:
    long long incidentTimestamp{};

    vector<long> allEntities;
    vector<long> affectedEntities;
    vector<Alert> alertsInRange;

    vector<long> pcs;
    vector<long> users;
    vector<long> alerts;
    vector<Transition> transitions;
    vector<Transition> path;

    void get_all_entities(const vector<PC>& input_pcs, const vector<User>& input_users);
    void compute_summary(long alertThatGeneratedIncident,
                         const vector<Alert>& input_alerts);
    void compute_path(tuple<long,long> entitiesForHighestScorePath,
                      const vector<Alert>& input_alerts);
    vector<long> get_entities_from_alert(const Alert& alert, long previous_entity = -1);
    vector<tuple<Alert,int>> get_alerts_from_entity(long entity_id);
    void map_affected_entities(const vector<PC>& pcs,
                               const vector<User>& users);
public:
    explicit Output(const InputItems& input);
};


#endif //BITXDR_OUTPUT_H
