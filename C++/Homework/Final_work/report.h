#ifndef REPORT_H
#define REPORT_H

#include "score.h"
#include <vector>

//Report类，包含学生成绩信息
class Report
{
protected:
    std::vector<Score> report;

public:
    //构造函数
    Report();

    //向report中添加成绩，返回对应绩点
    virtual void add_score(const std::string &sub, const std::string &sn, const std::string &tn, const int s, const int c);

    //删除给出科目成绩，返回是否成功
    virtual bool delete_score(const std::string &sub);

    //打印信息
    virtual void print() const;
};

#endif