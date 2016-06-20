//
// Copyright 2016 FiUBA
//

#include "Log.h"
#include <string>
#include "Constant.h"

Log* Log::logInstance = NULL; 

std::string Log::INFO = "INFO";
std::string Log::ERROR = "ERROR";
std::string Log::WARNING = "WARNING";
std::string Log::FATAL = "FATAL";

Log* Log::getInstance() {
    if (!logInstance) {
        logInstance = new Log();
    }
   return logInstance;
}

Log::Log() {
    google::SetLogDestination(google::GLOG_INFO, Constant::GLOG_INFO_PATH.c_str());
    google::SetLogDestination(google::GLOG_ERROR, Constant::GLOG_ERROR_PATH.c_str());
    google::SetLogDestination(google::GLOG_FATAL, Constant::GLOG_FATAL_PATH.c_str());
    google::SetLogDestination(google::GLOG_WARNING, Constant::GLOG_WARNING_PATH.c_str());
}

void Log::init(char *executableName){
    google::InitGoogleLogging(executableName);
}

void Log::writeLog(const char msj[], const std::string level){
    this->msj = std::string(msj);
    if (level == Log::INFO){
        LOG(INFO) << this->msj;
    } else if (level == Log::ERROR) {
        LOG(ERROR) << this->msj;
    } else if (level == Log::WARNING) {
        LOG(WARNING) << this->msj;
    } else if (level == Log::FATAL) {
        LOG(FATAL) << this->msj;
    } 
}

void Log::printLog(const char msj[], const std::string level){
    this->msj = std::string(msj);
    if (level == Log::INFO){
        std::cout << "INFO: " << this->msj << std::endl;
    } else if (level == Log::ERROR) {
        std::cout << "ERROR: " << this->msj << std::endl;
    } else if (level == Log::WARNING) {
        std::cout << "WARNING: " << this->msj << std::endl;
    } else if (level == Log::FATAL) {
        std::cout << "FATAL: " << this->msj << std::endl;
    }
}

void Log::writeAndPrintLog(const char msj[], const std::string level){
    this->printLog(msj,level);
    this->writeLog(msj,level);
}

Log::~Log() {
    google::ShutdownGoogleLogging();
}
