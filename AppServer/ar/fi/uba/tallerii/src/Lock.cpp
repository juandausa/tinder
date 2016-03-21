/* Copyright 2016 FiUBA */

#include "Lock.h"
#include <string>
Lock :: Lock(const std::string nombre) {
    this->nombre = nombre;
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    this->fd = open(this->nombre.c_str(), O_CREAT|O_WRONLY, 0777);
    this->liberado = true;
}

int Lock :: tomarLock() {
    this->fl.l_type = F_WRLCK;
    int resultado = fcntl(this->fd, F_SETLKW, &(this->fl));
    if (resultado != -1) {
        this->liberado = false;
    }

    return resultado;
}

int Lock :: liberarLock() {
    this->fl.l_type = F_UNLCK;
    int resultado = fcntl(this->fd, F_SETLK, &(this->fl));
    if (resultado != -1) {
        this->liberado = true;
    }

    return resultado;
}

ssize_t Lock :: escribir(const void* buffer, const size_t buffsize) const {
    if (this->liberado) {
        // Si el lock no esta tomado no escribo.
        return 0;
    }

    lseek(this->fd, 0, SEEK_END);
    return write(this->fd, buffer, buffsize);
}

ssize_t Lock :: escribir(const void* buffer,
    const size_t buffsize, int desde) const {
    if (this->liberado) {
        // Si el lock no esta tomado no escribo.
        return 0;
    }

    lseek(this->fd, 0, desde);
    return write(this->fd, buffer, buffsize);
}

int Lock::leer() {
    if (this-> liberado) {
        return -1;
    }
    lseek(this->fd, 0, SEEK_SET);
    int cant;

    while (read(this->fd, &cant, sizeof(int)) != -1) {
    }

    return cant;
}

Lock :: ~Lock() {
    close(this->fd);
}
