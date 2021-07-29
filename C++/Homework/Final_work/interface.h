#ifndef INTERFACE_H
#define INTERFACE_H

#include "database.h"
#include "exception.h"

class Interface
{
private:
    Database database; //数据库
    static bool First; //首次执行

public:
    //构造函数
    Interface();

    //程序运行
    bool Running();

    //程序指令
    void FirstInterface() const; //首界面
    void Show() const;           //查询整体数据信息
    bool Search() const;         //查询具体信息
    bool AddData();              //增加数据信息
    bool AddScore();             //录入学生成绩
    bool DeleteScore();          //删除学生成绩
    void exit() const;           //退出系统

    //暂停
    void pause() const;
};

#endif