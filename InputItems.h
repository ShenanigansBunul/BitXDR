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
public:
    [[nodiscard]] const vector<PC> &getPcs() const;

    [[nodiscard]] const vector<User> &getUsers() const;

    [[nodiscard]] const vector<Alert> &getAlerts() const;

    [[nodiscard]] long getAlertThatGeneratedIncident() const;

    [[nodiscard]] const tuple<long, long> &getEntitiesForHighestScorePath() const;

private:
    vector<PC> pcs;
    vector<User> users;
    vector<Alert> alerts;
    long alert_that_generated_incident;
    [[maybe_unused]] tuple<long, long> entities_for_highest_score_path;

public:
    explicit InputItems(const json &json);
};


#endif //BITXDR_INPUTITEMS_H
