#pragma once

#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include"../include/spectrum.h"
using namespace std;


//从 path\type 内从第st个数据开始读取num个文件,每个文件数据放在一个vector<double>内,将num个文件的数据push_back到v中
void readdatas(vector<spectrum> &v,const string &path,const string &type,int num,int st=1);	
//从 path\type 内读取第index个文件，存放在v内
void read1data(spectrum &s, const string &path,const string &type, int index);
