//
// Copyright 2016 FiUBA
//

#include "MatchesService.h"
#include "DataBase.h"

MatchesService::MatchesService() {
	this->database = DataBase::getInstance();
}

MatchesService::~MatchesService() {
}
