#ifndef _ERROR_H_
#define _ERROR_H_

#include "Common.h"

template<typename U>
void logError(const U& Message) {
    std::cerr << Message << std::endl;
}

template<typename T, typename... Y>
void logError(const T& Message, const Y&... Error) {
    std::cerr << Message;
    logError(Error...);
}

template<typename U>
void logMessage(const U& Message) {
    std::cout << Message << std::endl;
}

template<typename T, typename... Y>
void logMessage(const T& Message, const Y&... Rest) {
    std::cout << Message;
    logMessage(Rest...);
}

#endif
