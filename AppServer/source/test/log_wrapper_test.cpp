//
// Created by juan on 25/06/16.
//

#include "log_wrapper_test.h"

TEST(LogWrapper, Write) {
    Log *logger = Log::getInstance();
    logger->printLog("hello", Log::WARNING);
    logger->printLog("hello", Log::INFO);
}

TEST(LogWrapper, WriteAndPrint) {
    Log *logger = Log::getInstance();
    logger->writeAndPrintLog("hello", Log::WARNING);
    logger->writeAndPrintLog("hello", Log::INFO);
}