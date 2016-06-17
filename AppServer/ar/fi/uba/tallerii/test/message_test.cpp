//
// Created by juan on 17/06/16.
//

#include "include/message_test.h"

TEST(MessageTest, ConstructorAndGetters) {
    Message m("userA", "userB", "content");
    ASSERT_EQ("userA", m.getSender());
    ASSERT_EQ("userB", m.getReciever());
    ASSERT_EQ("content", m.getContent());
}

TEST(MessageTest, ToString) {
    Message m("userA", "userB", "content");
    ASSERT_EQ("userAN_NuserBN_Ncontent", m.toString());
}