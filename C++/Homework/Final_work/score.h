#ifndef SCORE_H
#define SCORE_H

#include <string>

class Score
{
protected:
    std::string subject;      //科目
    std::string student_name; //学生姓名
    std::string teacher_name; //授课教师
    int HundredMark_Score;    //百分制成绩
    std::string Graded_Score; //等级制成绩
    double courseGPA;         //课程学分绩
    int credit;               //学分

public:
    Score(const std::string &, const std::string &, const std::string &, const int, const int);
    virtual void print_score() const;
    void setScore(const int);

    const std::string getStudent_Name() const { return student_name; }
    const std::string getTeacher_Name() const { return teacher_name; }
    const double getCourseGPA() const { return courseGPA; }
    const int getCredit() const { return credit; }
};

#endif