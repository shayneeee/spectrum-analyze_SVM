#include <iostream>
#include "../include/MySQLSet.h"
using namespace std;


bool ConnectDatabase()  //链接数据库
{
    mysql_init(&conn);
    if(!mysql_real_connect(&conn,host,username,psw,database,port,NULL,0))
    {
        cout<<"database connect errot!"<<endl;
        return false;
    }
    else
        return true;
}
void FreeConnect()      //关闭链接释放资源
{
    mysql_free_result(result);
    mysql_close(&conn);
    mysql_library_end();
}
