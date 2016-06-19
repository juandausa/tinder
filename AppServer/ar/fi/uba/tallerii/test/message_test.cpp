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

TEST(MessageTest, LoadFromString) {
    Message m("userA", "userB", "content");
    Message mLoaded;
    mLoaded.loadFromString(m.toString());
    ASSERT_EQ(m.getSender(), mLoaded.getSender());
    ASSERT_EQ(m.getReciever(), mLoaded.getReciever());
    ASSERT_EQ(m.getContent(), mLoaded.getContent());
}

