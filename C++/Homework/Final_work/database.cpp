#include "database.h"
#include "exception.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void Database::ReadAll()
{
    try
    {
        ReadStudent("C++\\Homework\\Final_work\\student_in.txt");
        ReadTeacher("C++\\Homework\\Final_work\\teacher_in.txt");
        ReadScore("C++\\Homework\\Final_work\\score_in.txt");
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
        WriteStudent("C++\\Homework\\Final_work\\student_out.txt");
        WriteTeacher("C++\\Homework\\Final_work\\teacher_out.txt");
        WriteCourse("C++\\Homework\\Final_work\\course_out.txt");
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
    while (student_in.peek() != EOF)
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
    while (teacher_in.peek() != EOF)
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
    while (score_in.peek() != EOF)
    {
        if (!(score_in >> tempScore))
            throw Exception(ScoreFile_in, "读取数据", "只读");

        Score_List.emplace_back(tempScore);
        const std::string tempStudentName = tempScore.getStudentName();
        const std::string tempTeacherName = tempScore.getTeacherName();
        const std::string tempCourseName = tempScore.getSubject();

        auto ptrStudent = std::find_if(Student_List.begin(), Student_List.end(), [&tempStudentName](const Student &st)
                                       { return tempStudentName == st.getName(); });
        ptrStudent->add_score(tempScore);

        auto ptrTeacher = std::find_if(Teacher_List.begin(), Teacher_List.end(), [&tempTeacherName](const Teacher &st)
                                       { return tempTeacherName == st.getName(); });
        ptrTeacher->add_course(tempCourseName);

        auto ptrCourse = std::find_if(Course_List.begin(), Course_List.end(), [&tempCourseName, &tempTeacherName](const Course &st)
                                      { return tempCourseName == st.getSubject() && tempTeacherName == st.getTeacherName(); });
        if (ptrCourse == Course_List.end())
        {
            Course_List.emplace_back(tempScore.getSubject(), tempScore.getTeacherName(), tempScore.getCredit());
            (Course_List.end() - 1)->add_score(tempScore);
        }
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
    std::cout << std::endl;
}

void Database::showTeacher() const
{
    std::cout << "共有 " << Teacher_List.size() << " 个教师，如下：" << std::endl;
    std::for_each(Teacher_List.begin(), Teacher_List.end(), [](const Teacher &t)
                  { t.print(); });
    std::cout << std::endl;
}

void Database::showCourse() const
{
    std::cout << "共有 " << Course_List.size() << " 门课程，如下：" << std::endl;
    std::for_each(Course_List.begin(), Course_List.end(), [](const Course &c)
                  { c.print(); });
    std::cout << std::endl;
}

void Database::searchStudent(const std::string &StudentName) const
{
    auto ptrStudent = std::find_if(Student_List.begin(), Student_List.end(), [&StudentName](const Student &st)
                                   { return StudentName == st.getName(); });
    if (ptrStudent != Student_List.end())
        ptrStudent->print(true);
    else
        throw "没有找到该学生！";
}

void Database::searchTeacher(const std::string &TeacherName) const
{
    auto ptrTeacher = std::find_if(Teacher_List.begin(), Teacher_List.end(), [&TeacherName](const Teacher &t)
                                   { return TeacherName == t.getName(); });
    if (ptrTeacher != Teacher_List.end())
        ptrTeacher->print(true);
    else
        throw "没有找到该教师！";
}

void Database::searchCourse(const std::string &CourseName) const
{
    auto ptrCourse = std::find_if(Course_List.begin(), Course_List.end(), [&CourseName](const Course &c)
                                  { return CourseName == c.getSubject(); });
    if (ptrCourse != Course_List.end())
        ptrCourse->print(true);
    else
        throw "没有找到该课程！";
}

void Database::AddStudent(const Student &addStudent)
{
    const std::string tempName = addStudent.getName();
    if (std::find_if(Student_List.begin(), Student_List.end(), [&tempName](const Student &st)
                     { return tempName == st.getName(); }) != Student_List.end())
        throw "该学生已存在！";
    else
        Student_List.emplace_back(addStudent);
}

void Database::AddTeacher(const Teacher &addTeacher)
{
    const std::string tempName = addTeacher.getName();
    if (std::find_if(Teacher_List.begin(), Teacher_List.end(), [&tempName](const Teacher &st)
                     { return tempName == st.getName(); }) != Teacher_List.end())
        throw "该教师已存在！";
    else
        Teacher_List.emplace_back(addTeacher);
}

void Database::AddCourse(const Course &addCourse)
{
    const std::string tempName = addCourse.getSubject();
    if (std::find_if(Course_List.begin(), Course_List.end(), [&tempName](const Course &st)
                     { return tempName == st.getSubject(); }) != Course_List.end())
        throw "该课程已存在！";
    else
        Course_List.emplace_back(addCourse);
}

void Database::AddScore(const Score &addScore)
{
    if (std::find_if(Score_List.begin(), Score_List.end(), [&addScore](const Score &tem)
                     { return addScore.getStudentName() == tem.getStudentName() && addScore.getSubject() == tem.getSubject(); }) != Score_List.end())
        throw "该成绩已存在！";

    auto ptrStudent = std::find_if(Student_List.begin(), Student_List.end(), [&addScore](const Student &st)
                                   { return addScore.getStudentName() == st.getName(); });
    if (ptrStudent == Student_List.end())
        throw "该学生不存在！";

    auto ptrTeacher = std::find_if(Teacher_List.begin(), Teacher_List.end(), [&addScore](const Teacher &tea)
                                   { return addScore.getTeacherName() == tea.getName(); });
    if (ptrTeacher == Teacher_List.end())
        throw "该授课教师不存在！";

    auto ptrCourse = std::find_if(Course_List.begin(), Course_List.end(), [&addScore](const Course &cour)
                                  { return addScore.getSubject() == cour.getSubject(); });
    if (ptrCourse == Course_List.end())
        throw "该课程不存在！";

    Score_List.emplace_back(addScore);
    ptrStudent->add_score(addScore);
    ptrCourse->add_score(addScore);
    ptrTeacher->add_course(addScore.getSubject());
}

void Database::DeleteScore(const Score &deleteScore)
{
    auto ptrScore = std::find_if(Score_List.begin(), Score_List.end(), [&deleteScore](const Score &tem)
                                 { return deleteScore.getStudentName() == tem.getStudentName() && deleteScore.getSubject() == tem.getSubject(); });
    if (ptrScore == Score_List.end())
        throw "该成绩不存在！";
    Score_List.erase(ptrScore);

    auto ptrStudent = std::find_if(Student_List.begin(), Student_List.end(), [&deleteScore](const Student &st)
                                   { return deleteScore.getStudentName() == st.getName(); });
    ptrStudent->delete_score(deleteScore.getSubject());

    auto ptrCourse = std::find_if(Course_List.begin(), Course_List.end(), [&deleteScore](const Course &cour)
                                  { return deleteScore.getSubject() == cour.getSubject(); });
    ptrCourse->delete_score(deleteScore.getSubject());
}