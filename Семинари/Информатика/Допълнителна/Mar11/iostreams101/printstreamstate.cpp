#include <iostream>

using namespace std;

std::ostream & printstreamstate(std::istream const & is)
{
    return cout << (is.good()?" GOOD ":"~good")
                << (is.fail()?" FAIL ":"~fail")
                << (is.eof()?" EOF ":"~eof")
                << (is.bad()?" BAD ":"~bad") << endl;
}
