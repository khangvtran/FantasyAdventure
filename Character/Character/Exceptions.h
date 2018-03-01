/*
 
 Specification file for the Exceptions class.
 
 */

#ifndef Exceptions_h
#define Exceptions_h

#include <iostream>
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

#endif

