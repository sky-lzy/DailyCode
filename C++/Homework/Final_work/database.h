#ifndef DATABASE_H
#define DATABASE_H

#include "score.h"
#include "report.h"
#include "course.h"
#include "student.h"
#include "teacher.h"
#include <vector>

//数据库类
class Database
{
private:
    std::vector<Student> Student_List; //学生信息
    std::vector<Teacher> Teacher_List; //教师信息
    std::vector<Score> Score_List;     //课程分数信息
    std::vector<Course> Course_List;   //课程信息

public:
    //构造函数
    Database() {}
    //析构函数
    ~Database() {}

    //读入全部数据
    void ReadAll();
    //保存全部数据
    void WriteAll() const;

    //读取各数据
    void ReadStudent(const std::string &StudentFile_in);
    void ReadTeacher(const std::string &TeacherFile_in);
    void ReadScore(const std::string &ScoreFile_in);

    //保存各数据
    void WriteStudent(const std::string &StudentFile_out) const;
    void WriteTeacher(const std::string &TeacherFile_out) const;
    void WriteCourse(const std::string &CourseFile_out) const;

    //显示所有信息
    void showAll() const;

    //显示具体信息
    void showStudent() const;
    void showTeacher() const;
    void showCourse() const;

    //查找并显示相关信息
    void searchStudent(const std::string &StudentName);
    void searchTeacher(const std::string &TeacherName);
    void searchCourse(const std::string &CourseName);

    //增加信息
    void AddStudent(const Student &addStudent);
    void AddTeacher(const Teacher &addTeacher);
    void AddCourse(const Course &addCourse);
    void AddScore(const Score &addScore);

    //删除信息
    void DeleteScore(const Score &deleteScore);
};

#endif