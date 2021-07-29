#include <iostream>
#include <fstream>
#include "student.h"
#include "teacher.h"
#include "course.h"
#include "database.h"
#include "interface.h"
#include "exception.h"

int main()
{
    Interface interface;
    while (interface.Running())
        ;
    return 0;
}