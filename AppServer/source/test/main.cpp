//
// Copyright 2016 juanchi
//

#include <gtest/gtest.h>
#include <glog/logging.h>

int main(int argc, char **argv) {
    ::testing::FLAGS_gtest_output = "xml:./res.xml";
    testing::InitGoogleTest(&argc, argv);
    google::SetLogDestination(google::GLOG_INFO, "/tmp/tinderTests.log");
    google::SetLogDestination(google::GLOG_ERROR, "");
    google::SetLogDestination(google::GLOG_FATAL, "");
    google::SetLogDestination(google::GLOG_WARNING, "");
    google::InitGoogleLogging(argv[0]);
    int result = RUN_ALL_TESTS();
    google::ShutdownGoogleLogging();
    return result;
}
