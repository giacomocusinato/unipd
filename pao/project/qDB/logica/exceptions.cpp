#include "exceptions.h"

ConstructorException::ConstructorException(std::string s): message(s) {}

const char* ConstructorException::what() const throw()
{
    return message.c_str();
}
