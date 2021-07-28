#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

struct Exception
{
    std::string FileName;
    std::string operate;
    std::string OpenMode;

    Exception(const std::string &fn, const std::string & or, const std::string &om)
        : FileName(fn), operate(or), OpenMode(om) {}
};

#endif