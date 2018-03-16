/*
 
 Implementation file for the Exceptions class.
 
 */

#include "Exceptions.h"

namespace AdventureErrors
{
    BoundaryError::BoundaryError(const char* arg) : std::range_error(arg) {}
    const char* BoundaryError::what() const noexcept
    {
        return (std::range_error::what());
    }
    
    FileOpenError::FileOpenError(const char* arg) : std::invalid_argument(arg) {}
    const char* FileOpenError::what() const noexcept
    {
        static char temp[300];
        strcpy(temp, "File ");
        strcat(temp, std::invalid_argument::what());
        strcat(temp, " cannot be opened.");
        return (temp);
    }
    
    InvalidMove::InvalidMove(const char* what_arg) : std::invalid_argument(what_arg) {}
    const char* InvalidMove::what() const noexcept
    {
        return invalid_argument::what();
    }
    
    MissingObject::MissingObject(const char* what_arg) : std::logic_error(what_arg) {}
    const char*  MissingObject::what() const noexcept
    {
        return logic_error::what();
    }
    
    CharacterDeath::CharacterDeath(const char* what_arg) : std::runtime_error(what_arg) {}
    const char* CharacterDeath::what() const noexcept
    {
        return runtime_error::what();
    }
 
}

