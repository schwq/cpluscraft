#ifndef _ERROR_H_
#define _ERROR_H_

#include "common.h"

template<typename U>
void errorLog(const U& Message) {
    std::cerr << Message << std::endl;
}

template<typename T, typename... Y>
void errorLog(const T& Message, const Y&... Error) {
    std::cerr << Message;
    errorLog(Error...);
}

template<typename U>
void msgLog(const U& Message) {
    std::cout << Message << std::endl;
}

template<typename T, typename... Y>
void msgLog(const T& Message, const Y&... Rest) {
    std::cout << Message;
    msgLog(Rest...);
}

#endif
