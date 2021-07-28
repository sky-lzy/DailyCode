#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

struct Exception
{
    std::string FileName;
    std::string operate;
    std::string OpenMode;

    Exception(const std::string &fn, const std::string &orp, const std::string &om)
        : FileName(fn), operate(orp), OpenMode(om) {}
};

#endif