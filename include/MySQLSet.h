#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include </usr/include/mysql/mysql.h>
using namespace std;

extern const char host[];
extern const char username[];
extern const char psw[];
extern const char database[];
extern const int port;
extern MYSQL conn;
extern MYSQL_RES *result;

bool ConnectDatabase();  //链接数据库
void FreeConnect();      //关闭链接释放资源
