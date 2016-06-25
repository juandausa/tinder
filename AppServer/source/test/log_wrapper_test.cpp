//
// Created by juan on 25/06/16.
//

#include "log_wrapper_test.h"

TEST(LogWrapper, Print) {
    Log *logger = Log::getInstance();
    std::string message("hello 2");
    logger->printLog("hello", Log::WARNING);
    logger->printLog("hello", Log::INFO);
    logger->printLog(message, Log::WARNING);
    logger->printLog(message, Log::INFO);
}

TEST(LogWrapper, Write) {
    Log *logger = Log::getInstance();
    std::string message("hello 2");
    logger->writeLog("hello", Log::WARNING);
    logger->writeLog("hello", Log::INFO);
    logger->writeLog(message, Log::WARNING);
    logger->writeLog(message, Log::INFO);
}

TEST(LogWrapper, WriteAndPrint) {
    std::string message("hello 2");
    Log *logger = Log::getInstance();
    logger->writeAndPrintLog("hello", Log::WARNING);
    logger->writeAndPrintLog("hello", Log::INFO);
    logger->writeAndPrintLog(message, Log::WARNING);
    logger->writeAndPrintLog(message, Log::INFO);
}