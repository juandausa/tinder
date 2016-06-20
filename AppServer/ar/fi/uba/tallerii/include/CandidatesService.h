//
// Created by agu on 02/06/16.
//

#ifndef TINDER_CANDIDATESSERVICE_H
#define TINDER_CANDIDATESSERVICE_H
#include <jsoncpp/json/json.h>
#include <math.h>
class CandidatesService {
public:
        bool filterCandidates(Json::Value myUser, Json::Value user, Json::Value interests, Json::Value myArrayOfInterests );
        Json::Value getArrayInterests();
private:
    Json::Value arrayInterests;
    const double MIN_DISTANCE = 10;
    const double MAX_SEARCHS = 10;
    bool filterByInterestsRule(Json::Value interests, Json::Value myArrayOfInterests );
    bool filterByMatchesRule(Json::Value myUser, Json::Value user);
    bool filterByOnePercentRule(Json::Value myUser, Json::Value user);
    bool filterByLimitSearchsRule(Json::Value myUser, Json::Value user);
    bool filterByLocationRule(Json::Value myUser, Json::Value user);
    bool isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests);
};


#endif //TINDER_CANDIDATESSERVICE_H