//
// Created by sergi on 12/18/2023.
//

#ifndef BITXDR_INPUTITEMS_H
#define BITXDR_INPUTITEMS_H

#include<vector>
#include "JsonEntities/PC.h"
#include "JsonEntities/User.h"
#include "JsonEntities/Alert.h"
#include "InputItems.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class InputItems {
private:
    vector<PC> pcs;
    vector<User> users;
    vector<Alert> alerts;
    long alert_that_generated_incident;
    tuple<long, long> entities_for_highest_score_path;

    template<typename T>
    void initializeFromJsonArray(const json &j, const string &key, vector<T> &container, const string &errorMessage);

public:
    explicit InputItems(const json &json);

    [[nodiscard]] const vector<PC> &getPcs() const;

    [[nodiscard]] const vector<User> &getUsers() const;

    [[nodiscard]] const vector<Alert> &getAlerts() const;

    [[nodiscard]] long getAlertThatGeneratedIncident() const;

    [[nodiscard]] const tuple<long, long> &getEntitiesForHighestScorePath() const;
};


#endif //BITXDR_INPUTITEMS_H
