#include <unistd.h>
#include <iostream>
#include <wait.h>
#include <ctime>
#include <fstream>
#include <Lock.h>



using namespace std;

void printCurrentDir() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        cout<< "Current working dir: "<< cwd<<endl;
    else
        perror("getcwd() error");
}

int main(int arg, char** args) {
    cout << "Esto es un programa hecho con Clion." << endl;
    printCurrentDir();
    return 0;
}