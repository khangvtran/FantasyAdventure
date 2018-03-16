/*
 
 Specification file for the Exceptions class.
 
 */

#ifndef Exceptions_h
#define Exceptions_h

#include <iostream>
#include <stdexcept>
#include <cstring>

namespace AdventureErrors
{
    class BoundaryError : public std::range_error
    {
     public:
        BoundaryError(const char* arg);
        virtual const char* what() const noexcept;
    };

    class FileOpenError : public std::invalid_argument
    {
     public:
        FileOpenError(const char* arg);
        virtual const char* what() const noexcept;
    };
    class InvalidMove : public std::invalid_argument
    {
     public:
        explicit InvalidMove(const char* what_arg);
        virtual const char* what() const noexcept;
    };

    class MissingObject : public std::logic_error
    {
     public:
        explicit MissingObject(const char* what_arg);
        virtual const char* what() const noexcept;
    };
    class CharacterDeath : public std::runtime_error
    {
     public:
        explicit CharacterDeath(const char* what_arg);
        virtual const char* what() const noexcept;
    };
}


#endif

