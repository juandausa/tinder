#include "base64_test.h"

TEST(Base64, Encode) {
    Base64 base64;
    std::string file = "this is a file. Testing.....";
    EXPECT_EQ("dGhpcyBpcyBhIGZpbGUuIFRlc3RpbmcuLi4uLg==", base64.encode((const unsigned char*) file.c_str(), file.length()));
}

TEST(Base64, Decode) {
    Base64 base64;
    std::string encoded = "dGhpcyBpcyBhIGZpbGUuIFRlc3RpbmcuLi4uLg==";
    EXPECT_EQ("this is a file. Testing.....", base64.decode(encoded.c_str()));
}
