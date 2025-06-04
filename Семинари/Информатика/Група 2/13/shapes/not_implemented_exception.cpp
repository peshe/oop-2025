#include "not_implemented_exception.h"

const char* NotImplementedException::what() const {
	return "Not implemented!";
}