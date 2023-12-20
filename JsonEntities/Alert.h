//
// Created by sergi on 12/18/2023.
//

#ifndef BITXDR_ALERT_H
#define BITXDR_ALERT_H

#include<string>
#include<vector>

using namespace std;

struct Alert {
    long id;
    long long timestamp;
    string name;
    int score;
    vector<long> affected_entities;
};


#endif //BITXDR_ALERT_H
