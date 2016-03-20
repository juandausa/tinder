/* Copyright 2016 FiUBA */

#include <unistd.h>
#include <wait.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <Lock.h>

void printCurrentDir() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        std::cout << "Current working dir: " << cwd << std::endl;
    else
        perror("getcwd() error");
}

int main(int arg, char** args) {
    std::cout << "Esto es un programa hecho con Clion." << std::endl;
    printCurrentDir();
    return 0;
}
