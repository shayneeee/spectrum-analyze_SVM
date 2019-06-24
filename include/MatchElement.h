#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include </usr/include/mysql/mysql.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "MySQLSet.h"
#include "spectrum.h"
using namespace std;

extern const char host[];
extern const char username[];
extern const char psw[];
extern const char database[];
extern const int port;
extern MYSQL conn;
extern MYSQL_RES *result;

//链接数据库对光谱s进行元素匹配，若光谱未寻峰会先寻峰，返回元素匹配结果集
vector< pair< string,vector<double> > >matchelement(spectrum &s);

//将匹配结果打印到控制台
void printresult(vector< pair< string, vector<double> > > &result);
