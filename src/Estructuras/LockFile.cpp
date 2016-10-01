//
// Created by horacio on 9/24/16.
//

#include "LockFile.h"

LockFile :: LockFile ( const std::string nombre ) {
    this->nombre = nombre;
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    int openFd = open( this->nombre.c_str(),O_CREAT|O_WRONLY,0777 );
    if(openFd < 0) {
        std::string errMsg = std::string(std::string (strerror(errno)));
        throw "Fallo al abrir lock file with number: " + errMsg;
    }
    this->fd = openFd;
}

int LockFile :: tomarLock () {
    this->fl.l_type = F_WRLCK;
    int lock = fcntl ( this->fd,F_SETLKW,&(this->fl) );
    if(lock < 0 ) {
        std::string errMsg = std::string(std::string (strerror(errno)));
        throw "Fallo al abrir lock file with number: " + errMsg;
    }
    return lock;
}

int LockFile :: liberarLock () {
    this->fl.l_type = F_UNLCK;
    return fcntl ( this->fd,F_SETLK,&(this->fl) );
}

ssize_t LockFile :: escribir ( const void* buffer,const ssize_t buffsize ) const {
    lseek ( this->fd,0,SEEK_END );
    return write ( this->fd,buffer,buffsize );
}

LockFile :: ~LockFile () {
    close ( this->fd );
}

void LockFile :: clean() {
    unlink(this->nombre.c_str());
}
