//
// Created by fabrizio on 22/06/16.
//

#ifndef TINDER_PHOTOSERVICE_H
#define TINDER_PHOTOSERVICE_H

#include <string>

using namespace std;

class PhotoService {
public:
    static bool update(std::string userId, std::string photoBase64);
};


#endif //TINDER_PHOTOSERVICE_H
