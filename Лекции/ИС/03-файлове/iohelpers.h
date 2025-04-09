#pragma once

#ifndef _IOHELPERS_HEADER_INCLUDED
#define _IOHELPERS_HEADER_INCLUDED

#include <cctype>
#include <iostream>

inline void skipSpaces()
{
    while (isspace(std::cin.get()))
        ;
    std::cin.unget();
}


#endif //_IOHELPERS_HEADER_INCLUDED
