/*
 
 Specification file for the Exceptions class.
 
 */

#ifndef Exceptions_h
#define Exceptions_h

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cstring>
using namespace std;

class BoundaryError : public range_error
{
public:
    BoundaryError(const char* arg) : range_error(arg) {}
    virtual const char* what() const throw()
    {
        return (range_error::what());
    }
};

class FileOpenError : public invalid_argument
{
public:
    FileOpenError(const char* arg) : invalid_argument(arg) {}
    virtual const char* what() const throw()
    {
        static char temp[300];
        strcpy(temp, "File ");
        strcat(temp, invalid_argument::what());
        strcat(temp, " cannot be opened.");
        return (temp);
    }
};

#endif

