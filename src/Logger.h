#ifndef TP1_LOGGER_H
#define TP1_LOGGER_H

#include <string.h>

class Logger {
private:
    Logger() {

    }

    ~Logger() {
    }

public:
    Logger(const Logger &) = delete;

    Logger &operator=(const Logger &) = delete;

    static Logger &getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string &msg);
};


#endif //TP1_LOGGER_H
