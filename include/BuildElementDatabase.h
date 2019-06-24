#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include </usr/include/mysql/mysql.h>
#include <string>
#include <fstream>
#include <sstream>
#include "MySQLSet.h"
using namespace std;

extern const string elementdatapath;

extern const char host[];
extern const char username[];
extern const char psw[];
extern const char database[];
extern const int port;
extern MYSQL conn;
extern MYSQL_RES *result;

void buildelementdatabase(); //构造元素数据库
