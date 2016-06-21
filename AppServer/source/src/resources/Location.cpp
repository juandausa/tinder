//
// Copyright 2016 FiUBA
//

#include "Location.h"

Location::Location() {
    this->latitude = 0;
    this->longitude = 0;
}


Location::Location(double latitude, double longitude) {
}

double Location::getLatitude() {
    return this->latitude;
}

double Location::getLongitude() {
    return this->longitude;
}

void Location::setLatitude(double latitude) {
    this->latitude = latitude;
}

void Location::setLongitude(double longitude) {
    this->longitude = longitude;
}

Location::~Location() {
}
