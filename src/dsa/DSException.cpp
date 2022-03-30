#include <string>
#include <exception>
#include "Structures.h"

/****************************************************************************************
 *                               _structures Exception Operation                                  *
 *****************************************************************************************/

/**
 *
 * this function invoked creation of Exception
 * */


_structures::DSException::DSException(std::string &msg, std::string &file, int line)
{
    this->msg = msg;
    this->file = file;
    this->line = line;
}

/**
 *
 * destructor
 * */

_structures::DSException::~DSException()
{
}

/**
 *
 * this function returns msg of Exception
 * */
const char *_structures::DSException::what() const throw()
{
    return this->msg.c_str();
}

/****************************************************************************************
 *                               _structures Exception Operation                                  *
 *****************************************************************************************/