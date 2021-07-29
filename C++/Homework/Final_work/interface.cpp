#include "interface.h"
#include <iostream>

bool Interface::First = true;

Interface::Interface() {}

bool Interface::Running()
{
    system("cls");    //清屏
    std::cin.clear(); //排除错误
    std::cin.sync();  //清空输入缓冲区

    if (First) //第一次读取文件信息
    {
        First = false;
        try
        {
            database.ReadAll();
        }
        catch (const Exception &e)
        {
            std::cout << e.FileName << " 文件在以 " << e.OpenMode << " 方式 " << e.operate << " 时出错！" << std::endl;
            return false;
        }
    }

    FirstInterface(); //打印首界面

    int mode;
    while (true)
    {
        if (!(std::cin >> mode) || (mode > 6 || mode < 1))
        {
            std::cout << "输入有误！请重新输入(1~6)：";
            std::cin.clear();
            std::cin.sync();
            continue;
        }
        break;
    }

    switch (mode)
    {
    case 1:
        Show();
        break;
    case 2:
        while (Search())
            ;
        break;
    case 3:
        while (AddData())
            ;
        break;
    case 4:
        while (AddScore())
            ;
        break;
    case 5:
        while (DeleteScore())
            ;
        break;
    case 6:
        exit();
        return false;
        break;

    default:
        std::cout << "输入有误！请重新输入！" << std::endl;
        break;
    }

    pause();
    return true;
}

void Interface::FirstInterface() const
{
    std::cout << "****************************" << std::endl;
    std::cout << "    ××大学学生成绩管理系统    " << std::endl
              << std::endl;
    std::cout << "    1. 查询数据库信息        " << std::endl;
    std::cout << "    2. 查询具体信息          " << std::endl;
    std::cout << "    3. 增加数据信息          " << std::endl;
    std::cout << "    4. 录入学生成绩          " << std::endl;
    std::cout << "    5. 删除学生成绩          " << std::endl;
    std::cout << "    6. 退出系统             " << std::endl;
    std::cout << "****************************" << std::endl
              << std::endl;
    std::cout << "请输入您需要进行的操作：";
}

void Interface::Show() const
{
    system("cls");
    std::cin.clear();
    std::cin.sync();

    std::cout << "    查询数据库信息" << std::endl
              << std::endl;
    std::cout << "    1. 显示所有信息" << std::endl;
    std::cout << "    2. 显示学生信息" << std::endl;
    std::cout << "    3. 显示教师信息" << std::endl;
    std::cout << "    4. 显示课程信息" << std::endl;
    std::cout << "    5. 返回上一级目录" << std::endl
              << std::endl;
    std::cout << "请输入您需要进行的操作：";

    int mode;
    while (true)
    {
        if (!(std::cin >> mode) || (mode > 5 || mode < 1))
        {
            std::cout << "输入有误！请重新输入(1~5)：";
            std::cin.clear();
            std::cin.sync();
            continue;
        }
        break;
    }

    switch (mode)
    {
    case 1:
        database.showAll();
        break;
    case 2:
        database.showStudent();
        break;
    case 3:
        database.showTeacher();
        break;
    case 4:
        database.showCourse();
        break;
    case 5:
        break;

    default:
        std::cout << "输入有误！请重新输入！" << std::endl;
        break;
    }
}

bool Interface::Search() const
{
    system("cls");
    std::cin.clear();
    std::cin.sync();

    std::cout << "    查询具体信息" << std::endl
              << std::endl;
    std::cout << "    1. 查找学生" << std::endl;
    std::cout << "    2. 查找教师" << std::endl;
    std::cout << "    3. 查找课程" << std::endl;
    std::cout << "    4. 返回上一级目录" << std::endl
              << std::endl;
    std::cout << "请输入您需要进行的操作：";

    int mode;
    while (true)
    {
        if (!(std::cin >> mode) || (mode > 4 || mode < 1))
        {
            std::cout << "输入有误！请重新输入(1~4)：";
            std::cin.clear();
            std::cin.sync();
            continue;
        }
        break;
    }

    std::cout << "请输入姓名：";
    std::cin.clear();
    std::cin.sync();

    std::string name;
    while (true)
    {
        if (!(std::cin >> name))
        {
            std::cout << "输入有误！请重新输入。";
            std::cin.clear();
            std::cin.sync();
            continue;
        }
        break;
    }

    try
    {
        switch (mode)
        {
        case 1:
            database.searchStudent(name);
            break;
        case 2:
            database.searchTeacher(name);
            break;
        case 3:
            database.searchCourse(name);
            break;
        case 4:
            break;
        default:
            break;
        }
    }
    catch (const std::string &s)
    {
        std::cout << s << std::endl;
        return true;
    }
    return false;
}

bool Interface::AddScore()
{
    system("cls");
    std::cin.clear();
    std::cin.sync();

    std::cout << "    增加数据信息" << std::endl
              << std::endl;
    std::cout << "    1. 增加学生信息" << std::endl;
    std::cout << "    2. 增加教师信息" << std::endl;
    std::cout << "    3. 增加课程信息" << std::endl;
    std::cout << "    4. 返回上一级目录" << std::endl
              << std::endl;
    std::cout << "请输入您需要进行的操作：";

    int mode;
    while (true)
    {
        if (!(std::cin >> mode) || (mode > 4 || mode < 1))
        {
            std::cout << "输入有误！请重新输入(1~4)：";
            std::cin.clear();
            std::cin.sync();
            continue;
        }
        break;
    }

    std::cout << "请输入信息：";
    std::cin.clear();
    std::cin.sync();

    try
    {
        Student tempStudent;
        Teacher tempTeacher;
        Course tempCourse;
        switch (mode)
        {
        case 1:
            if (!(std::cin >> tempStudent))
                throw "输入学生信息有误！";
            database.AddStudent(tempStudent);
            break;
        case 2:
            if (!(std::cin >> tempTeacher))
                throw "输入教师信息有误！";
            database.AddTeacher(tempTeacher);
            break;
        case 3:
            if (!(std::cin >> tempCourse))
                throw "输入课程信息有误！";
            database.AddCourse(tempCourse);
            break;
        case 4:
            
        default:
            break;
        }
    }
    catch (const std::string &s)
    {
        std::cout << s << std::endl;
        return true;
    }
    return false;
}

bool Interface::AddScore()
{
    
}