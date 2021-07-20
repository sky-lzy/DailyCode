#include "report.h"
#include <iostream>
#include <algorithm>

double Report::add_score(const std::string &sub, const std::string &sn, const std::string &tn, const int s, const int c)
{
    return report.emplace_back(sub, sn, tn, s, c).getCourseGPA();
}

void Report::print() const
{
    std::for_each(report.begin(), report.end(), [](const Score &s)
                  { s.print_score(); });
}