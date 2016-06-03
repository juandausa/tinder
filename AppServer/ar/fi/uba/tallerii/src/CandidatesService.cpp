//
// Copyright 2016 FiUBA
//

#include "CandidatesService.h"

/* TODO: Ver porque se rompe en esta funcion */
bool CandidatesService::isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests) {
    for (unsigned int i = 0; i < myArrayOfInterests.size(); i++) {
        if (interest.compare(myArrayOfInterests[i]["value"]) == 0) {
            return true;
        }
    }
    return false;
}

// No repetir el candidato: si el usuario y el candidato ya tuvieron un match anterior, este no será un candidato futuro.
bool CandidatesService::filterByMatchesRule(Json::Value myUser, Json::Value user) {
    /*TODO: ver como recuperar si ya hubo un match anterior */
    return true;
}

// Regla del 1%: Para poder lograr un balance equitativo de candidatos, los usuarios que
// se encuentren dentro del 1% con más matches serán seleccionados con menos
// frecuencia como candidatos. Dentro de este 1% tambien se consideraran los candidatos
// que reciban un voto positivo pero el match no se realiza.
bool CandidatesService::filterByOnePercentRule(Json::Value myUser, Json::Value user)  {
    /*TODO: ver como recuperar los usuarios con mas o menos matches*/
    return true;
}

// Debe existir un límite diario de búsquedas de candidatos por usuario.
bool CandidatesService::filterByLimitSearchsRule(Json::Value myUser, Json::Value user) {
    /*TODO: ver como recuperar la cantidad de busquedas diarias que realizo un usuario*/
    return true;
}

// Filtro por cercanía: los posibles candidatos deben poder filtrarse en función de la ubicación del usuario.
bool CandidatesService::filterByLocationRule(Json::Value myUser, Json::Value user) {
    double userLatitude = user["location"].get("latitude", 0).asDouble();
    double userLongitude = user["location"].get("longitude", 0).asDouble();
    double myUserLatitude = myUser["location"].get("latitude", 0).asDouble();
    double myUserLongitude = myUser["location"].get("longitude", 0).asDouble();
    double distancia = sqrt(pow(myUserLatitude - userLatitude, 2) + pow(myUserLongitude - userLongitude, 2));
    if (distancia >= this->MIN_DISTANCE) {
        return false;
    }
    return true;
}


// Tanto el usuario como el candidato deben compartir algún interés en común
bool CandidatesService::filterByInterestsRule(Json::Value interests, Json::Value myArrayOfInterests ) {
    int interestInCommon = 0;
    for (unsigned int j = 0; j < interests.size(); j++) {
        this->arrayInterests.append(interests[j]["value"]);
        if (this->isInMyArrayOfInterest(interests[j]["value"], myArrayOfInterests)) {
            interestInCommon++;
        }
    }
    return (interestInCommon >= 1);
}

bool CandidatesService::filterCandidates(Json::Value myUser, Json::Value user, Json::Value interests, Json::Value myArrayOfInterests ) {
    return (this->filterByInterestsRule(interests, myArrayOfInterests) &&
            this->filterByMatchesRule(myUser, user) &&
            this->filterByOnePercentRule(myUser, user) &&
            this->filterByLimitSearchsRule(myUser, user) &&
            this->filterByLocationRule(myUser, user));
}

Json::Value CandidatesService::getArrayInterests() {
    return this->arrayInterests;
}
