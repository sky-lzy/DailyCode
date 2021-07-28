#include "database.h"
#include "exception.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void Database::ReadAll()
{
    try
    {
        ReadStudent("student_in.txt");
        ReadTeacher("Teacher_in.txt");
        ReadScore("score_in.txt");
    }
    catch (const Exception &e)
    {
        throw e;
    }
}

void Database::WriteAll() const
{
    try
    {
        WriteStudent("teacher_out.txt");
        WriteTeacher("teacher_out.txt");
        WriteCourse("course_out.txt");
    }
    catch (const Exception &e)
    {
        throw e;
    }
}

void Database::ReadStudent(const std::string &StudentFile_in)
{
    std::ifstream student_in(StudentFile_in, std::ios::in);
    if (!student_in.is_open())
        throw Exception(StudentFile_in, "打开文件", "只读");

    Student tempStudent;
    while (!student_in.eof())
    {
        if (!(student_in >> tempStudent))
            throw Exception(StudentFile_in, "读取数据", "只读");

        Student_List.emplace_back(tempStudent);
    }

    student_in.close();
}

void Database::ReadTeacher(const std::string &TeacherFile_in)
{
    std::ifstream teacher_in(TeacherFile_in, std::ios::in);
    if (!teacher_in.is_open())
        throw Exception(TeacherFile_in, "打开文件", "只读");

    Teacher tempTeacher;
    while (!teacher_in.eof())
    {
        if (!(teacher_in >> tempTeacher))
            throw Exception(TeacherFile_in, "读取数据", "只读");

        Teacher_List.emplace_back(tempTeacher);
    }

    teacher_in.close();
}

void Database::ReadScore(const std::string &ScoreFile_in)
{
    std::ifstream score_in(ScoreFile_in, std::ios::in);
    if (!score_in.is_open())
        throw Exception(ScoreFile_in, "打开文件", "只读");

    Score tempScore;
    while (!score_in.eof())
    {
        if (!(score_in >> tempScore))
            throw Exception(ScoreFile_in, "读取数据", "只读");

        Score_List.emplace_back(tempScore);
        std::string tempStudentName = tempScore.getStudentName();
        std::string tempTeacherName = tempScore.getTeacherName();
        std::string tempCourseName = tempScore.getSubject();

        auto ptrStudent = std::find_if(Student_List.begin(), Student_List.end(), [&tempStudentName](const Student &st)
                                       { return tempStudentName == st.getName(); });
        ptrStudent->add_score(tempScore);

        auto ptrTeacher = std::find_if(Teacher_List.begin(), Teacher_List.end(), [&tempTeacherName](const Teacher &st)
                                       { return tempTeacherName == st.getName(); });
        ptrTeacher->add_course(tempTeacherName);

        auto ptrCourse = std::find_if(Course_List.begin(), Course_List.end(), [&tempCourseName](const Course &st)
                                      { return tempCourseName == st.getSubject(); });
        if (ptrCourse == Course_List.end())
            Course_List.emplace_back(tempScore.getSubject(), tempScore.getTeacherName(), tempScore.getCredit());
        else
            ptrCourse->add_score(tempScore);
    }

    score_in.close();
}

void Database::WriteStudent(const std::string &StudentFile_out) const
{
    std::ofstream student_out(StudentFile_out, std::ios::out | std::ios::trunc);
    if (!student_out.is_open())
        throw Exception(StudentFile_out, "打开文件", "写入");

    std::for_each(Student_List.begin(), Student_List.end(), [&student_out](const Student &st)
                  { student_out << st; });

    student_out.close();
}

void Database::WriteTeacher(const std::string &TeacherFile_out) const
{
    std::ofstream teacher_out(TeacherFile_out, std::ios::out | std::ios::trunc);
    if (!teacher_out.is_open())
        throw Exception(TeacherFile_out, "打开文件", "写入");

    std::for_each(Teacher_List.begin(), Teacher_List.end(), [&teacher_out](const Teacher &st)
                  { teacher_out << st; });

    teacher_out.close();
}

void Database::WriteCourse(const std::string &CourseFile_out) const
{
    std::ofstream course_out(CourseFile_out, std::ios::out | std::ios::trunc);
    if (!course_out.is_open())
        throw Exception(CourseFile_out, "打开文件", "写入");

    std::for_each(Course_List.begin(), Course_List.end(), [&course_out](const Course &st)
                  { course_out << st; });

    course_out.close();
}

void Database::showAll() const
{
    showStudent();
    showTeacher();
    showCourse();
}

void Database::showStudent() const
{
    std::cout << "共有 " << Student_List.size() << " 个学生，如下：" << std::endl;
    std::for_each(Student_List.begin(), Student_List.end(), [](const Student &s)
                  { s.print(); });
}

void Database::showTeacher() const
{
    std::cout << "共有 " << Teacher_List.size() << " 个教师，如下：" << std::endl;
    std::for_each(Teacher_List.begin(), Teacher_List.end(), [](const Teacher &t)
                  { t.print(); });
}

void Database::showCourse() const
{
    std::cout << "共有 " << Course_List.size() << " 门课程，如下：" << std::endl;
    std::for_each(Course_List.begin(), Course_List.end(), [](const Course &c)
                  { c.print(); });
}