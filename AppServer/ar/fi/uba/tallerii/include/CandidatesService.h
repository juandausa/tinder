//
// Created by agu on 02/06/16.
//

#ifndef TINDER_CANDIDATESSERVICE_H
#define TINDER_CANDIDATESSERVICE_H
#include <jsoncpp/json/json.h>

class CandidatesService {
public:
        bool filterCandidates(Json::Value user, Json::Value interests, Json::Value myArrayOfInterests );
        Json::Value getArrayInterests();
private:
    Json::Value arrayInterests;
    bool filterByInterestsRule(Json::Value interests, Json::Value myArrayOfInterests );
    bool filterByMatchesRule(Json::Value user);
    bool filterByOnePercentRule(Json::Value user);
    bool filterByLimitDayRule(Json::Value user);
    bool filterByLocationRule(Json::Value user);
    bool isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests);
};


#endif //TINDER_CANDIDATESSERVICE_H
