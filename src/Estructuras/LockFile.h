//
// Created by horacio on 9/24/16.
//

#ifndef TP1_LOCKFILE_H
#define TP1_LOCKFILE_H


#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstring>

class LockFile {

private:
    struct flock fl;
    int fd;
    std::string nombre;

public:
    LockFile(const std::string nombre);

    ~LockFile();

    int tomarLock();

    int liberarLock();

    ssize_t escribir(const void *buffer, const ssize_t buffsize) const;

    void clean();
};


#endif //TP1_LOCKFILE_H
