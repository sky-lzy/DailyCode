#ifndef INTERFACE_H
#define INTERFACE_H

#include "database.h"
#include "exception.h"
#include <memory>

class Interface
{
private:
    std::shared_ptr<Database> ptrDatabase;

public:
    //构造函数
    Interface();

    //程序运行
    bool Running();

    //程序指令
    void FirstInterface(); //首界面
    bool Show();           //查询整体数据信息
    bool Search();         //查询具体信息
    bool Modify();         //修改信息
};

#endif