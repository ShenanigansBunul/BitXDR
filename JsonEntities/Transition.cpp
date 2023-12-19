//
// Created by sergi on 12/19/2023.
//

#include "Transition.h"

Transition::Transition(const long &first_ent, const long &second_ent, const string &a_name, const int &a_score) {
    first_entity = first_ent;
    second_entity = second_ent;
    alert_name = a_name;
    alert_score = a_score;
}

long Transition::getFirstEntity() const {
    return first_entity;
}

long Transition::getSecondEntity() const {
    return second_entity;
}

const string &Transition::getAlertName() const {
    return alert_name;
}

int Transition::getAlertScore() const {
    return alert_score;
}

bool Transition::operator==(const Transition &other) const {
    return (this->first_entity == other.first_entity && this->second_entity == other.second_entity) ||
           (this->first_entity == other.second_entity && this->second_entity == other.first_entity);
}

/**
 * Create a copy of the Transition object with the first_entity and second_entity member values reversed.
 * @return The copy of the object.
 */
Transition Transition::reverseEntities() {
    Transition copy(*this);
    copy.first_entity = second_entity;
    copy.second_entity = first_entity;
    return copy;
}
