//
// Created by juan on 20/06/16.
//

#include "include/converter_test.h"
#include "Constant.h"

TEST(Converter, IntToString) {
    EXPECT_EQ("100", Converter::intToString(100));
}

TEST(Converter, CalculateAge) {
    EXPECT_EQ("16", Converter::calculateAge("01/01/2000"));
}

TEST(Converter, CalculateGenderNoInput) {
    EXPECT_EQ(Constant::male, Converter::validateGenderOrReturnDefault(""));
}

TEST(Converter, CalculateGenderMaleInput) {
    EXPECT_EQ(Constant::male, Converter::validateGenderOrReturnDefault("male"));
}

TEST(Converter, CalculateGenderFemaleInput) {
    EXPECT_EQ(Constant::female, Converter::validateGenderOrReturnDefault("female"));
}

TEST(Converter, ValidateTimeNoInput) {
    EXPECT_EQ(Constant::defaultBirthday, Converter::validateTimeOrReturnDefault(""));
}

TEST(Converter, ValidateTimeCorrectInput) {
    EXPECT_EQ("12/10/1978", Converter::validateTimeOrReturnDefault("12/10/1978"));
}