//
// Created by juan on 25/04/16.
//

#include "photo_service_test.h"

TEST(PhotoService, UpdatePhotoOnNotExistingSite) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testphotoservice")){
        PhotoService photoService;
        EXPECT_NO_THROW(photoService.update("urlnotexist", "photo"));
    } else {
        EXPECT_EQ(1, 0);
    }
}
