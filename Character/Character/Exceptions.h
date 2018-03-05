/*
 
 Specification file for the Exceptions class.
 
 */

#ifndef Exceptions_h
#define Exceptions_h

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cstring>
//using namespace std;

namespace AdventureErrors
{
    class BoundaryError : public std::range_error
    {
    public:
        BoundaryError(const char* arg) : std::range_error(arg) {}
        virtual const char* what() const throw()
        {
            return (std::range_error::what());
        }
    };
    
    class FileOpenError : public std::invalid_argument
    {
    public:
        FileOpenError(const char* arg) : std::invalid_argument(arg) {}
        virtual const char* what() const throw()
        {
            static char temp[300];
            strcpy(temp, "File ");
            strcat(temp, std::invalid_argument::what());
            strcat(temp, " cannot be opened.");
            return (temp);
        }
    };
}


#endif

