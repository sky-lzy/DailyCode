#ifndef REPORT_H
#define REPORT_H

#include "score.h"
#include <vector>

class Report
{
protected:
    std::vector<Score> report;

public:
    virtual double add_score(const std::string &sub, const std::string &sn, const std::string &tn, const int s, const int c);
    bool delete_score(const std::string &sub);
    virtual void print() const;
};

#endif