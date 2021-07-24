#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <iostream>

//Score类，由学生单门课程信息组成
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
    Score();
    //构造函数，传参：学科、学生姓名、授课教师、百分制成绩、学分
    Score(const std::string &, const std::string &, const std::string &, const int, const int);

    //打印信息
    virtual void print() const;

    //设置成绩
    void setScore(const int);

    void setSubject(const std::string &s) { subject = s; }
    void setStudentName(const std::string &sn) { student_name = sn; }
    void setTeacherName(const std::string &tn) { teacher_name = tn; }

    std::string getSubject() const { return subject; }
    std::string getStudentName() const { return student_name; }
    std::string getTeacherName() const { return teacher_name; }
    int getHundredMarkScore() const { return HundredMark_Score; }
    std::string getGradedScore() const { return Graded_Score; }
    double getCourseGPA() const { return courseGPA; }
    int getCredit() const { return credit; }

    friend std::istream &operator>>(std::istream &, Score &);
    friend std::ostream &operator<<(std::ostream &, const Score &);
};

#endif