//
#ifndef TINDER_LOCATION_H
#define TINDER_LOCATION_H

class Location {
public:
    Location();
    Location(double latitude,double longitude);
    ~Location();
    double getLatitude();
    double getLongitude();
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    
private:
    double latitude;
    double longitude; 

};

#endif //TINDER_LOCATION_H
