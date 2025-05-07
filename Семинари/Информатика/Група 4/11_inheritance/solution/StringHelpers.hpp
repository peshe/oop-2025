#ifndef STRINGHELPERS_HPP
#define STRINGHELPERS_HPP

#include <cstring>

namespace StringHelpers {
    inline char *duplicateString(const char *s) {
        if (!s) {
            char *newStr = new char[1];
            newStr[0] = '\0';
            return newStr;
        }
        size_t len = strlen(s) + 1;
        char *newStr = new char[len];
        strcpy(newStr, s);
        return newStr;
    }
}


#endif //STRINGHELPERS_HPP
