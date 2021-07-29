#include "report.h"
#include <iostream>
#include <algorithm>

Report::Report() {}

double Report::add_score(const std::string &sub, const std::string &sn, const std::string &tn, const int s, const int c)
{
    report.emplace_back(sub, sn, tn, s, c);
    return (report.end() - 1)->getCourseGPA();
}

void Report::print() const
{
    std::for_each(report.begin(), report.end(), [](const Score &s)
                  { s.print(); });
}

bool Report::delete_score(const std::string &sub)
{
    bool flag = true;
    auto tem = std::find_if(report.begin(), report.end(), [&sub](const Score &sc)
                            { return sub == sc.getSubject(); });
    if (tem != report.end())
        report.erase(tem);
    else
        flag = false;
    return flag;
}