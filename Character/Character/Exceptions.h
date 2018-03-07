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
    class InvalidMove : public std::invalid_argument
    {
     public:
        explicit InvalidMove(const char* what_arg) : std::invalid_argument(what_arg){ }
        virtual const char* what() const noexcept
        {
            return invalid_argument::what();
        }
    };

    class MissingObject : public std::logic_error
    {
     public:
        explicit MissingObject(const char* what_arg) : std::logic_error(what_arg){ }
        virtual const char* what() const noexcept
        {
            return logic_error::what();
        }
    };
    class CharacterDeath : public std::runtime_error
    {
     public:
        explicit CharacterDeath(const char* what_arg) : std::runtime_error(what_arg){ }
        virtual const char* what() const noexcept
        {
            return runtime_error::what();
        }
        
    };
}


#endif

