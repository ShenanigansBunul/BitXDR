//
// Created by sergi on 12/19/2023.
//

#ifndef BITXDR_TRANSITION_H
#define BITXDR_TRANSITION_H

#include<string>
#include "../json.hpp"

using ordered_json = nlohmann::ordered_json;
using namespace std;

class Transition {
    long first_entity;
    long second_entity;
    string alert_name;
    int alert_score;

public:
    explicit Transition(const long &first_ent, const long &second_ent, const string &a_name, const int &a_score);

    Transition reverseEntities();

    [[nodiscard]] long getFirstEntity() const;

    [[nodiscard]] long getSecondEntity() const;

    [[nodiscard]] const string &getAlertName() const;

    [[nodiscard]] int getAlertScore() const;

    bool operator==(const Transition &other) const;
};


namespace std {
    template <>
    struct hash<Transition> {
        size_t operator()(const Transition &t) const {
            return hash<long>{}(min(t.getFirstEntity(), t.getSecondEntity()))
                   ^ hash<long>{}(max(t.getFirstEntity(), t.getSecondEntity()))
                   ^ hash<string>{}(t.getAlertName())
                   ^ hash<int>{}(t.getAlertScore());
        }
    };
}


#endif //BITXDR_TRANSITION_H
