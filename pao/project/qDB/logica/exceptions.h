#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class ConstructorException : public std::exception
{
public:
    ConstructorException(std::string);
    ~ConstructorException() throw() {}
    const char* what() const throw();
private:
    std::string message;
};

#endif // EXCEPTIONS_H
