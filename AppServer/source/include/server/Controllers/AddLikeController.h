//
//

#ifndef TINDER_ADD_LIKE_H
#define TINDER_ADD_LIKE_H

#include "GenericController.h"
#include "UserService.h"
class AddLikeController: public GenericController {

public:
    void operation(Request &request, Response &response);

private:
    UserService userService;
    std::string getUserTo(const std::string body);
};


#endif //TINDER_ADD_LIKE_H
