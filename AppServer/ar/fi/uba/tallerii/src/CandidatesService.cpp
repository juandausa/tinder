//
// Created by agu on 02/06/16.
//

#include "CandidatesService.h"

bool CandidatesService::isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests){
    for (unsigned int i = 0; i < myArrayOfInterests.size(); i++){
        if (interest.compare(myArrayOfInterests[i]["value"]) == 0){
            return true;
        }
    }
    return false;
}

// No repetir el candidato: si el usuario y el candidato ya tuvieron un match anterior, este no será un candidato futuro.
bool CandidatesService::filterByMatchesRule(Json::Value user) {
    return true;
}

// Regla del 1%: Para poder lograr un balance equitativo de candidatos, los usuarios que
// se encuentren dentro del 1% con más matches serán seleccionados con menos
// frecuencia como candidatos. Dentro de este 1% tambien se consideraran los candidatos
// que reciban un voto positivo pero el match no se realiza.
bool CandidatesService::filterByOnePercentRule(Json::Value user)  {
    return true;
}

// Debe existir un límite diario de búsquedas de candidatos por usuario.
bool CandidatesService::filterByLimitDayRule(Json::Value user) {
    return true;
}

// Filtro por cercanía: los posibles candidatos deben poder filtrarse en función de la ubicación del usuario.
bool CandidatesService::filterByLocationRule(Json::Value user) {
    return true;
}


// Tanto el usuario como el candidato deben compartir algún interés en común
bool CandidatesService::filterByInterestsRule(Json::Value interests, Json::Value myArrayOfInterests ){
    int interestInCommon = 0;
    for (unsigned int j = 0; j < interests.size(); j++) {
        this->arrayInterests.append(interests[j]["value"]);
        if (this->isInMyArrayOfInterest(interests[j]["value"], myArrayOfInterests)){
            interestInCommon++;
        }
    }
    return (interestInCommon >= 1);
}



bool CandidatesService::filterCandidates(Json::Value user, Json::Value interests, Json::Value myArrayOfInterests ) {
    return (this->filterByInterestsRule(interests,myArrayOfInterests) &&
            this->filterByMatchesRule(user) &&
            this->filterByOnePercentRule(user) &&
            this->filterByLimitDayRule(user) &&
            this->filterByLocationRule(user));
}

Json::Value CandidatesService::getArrayInterests(){
    return this->arrayInterests;
}