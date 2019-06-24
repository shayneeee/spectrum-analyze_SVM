#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include "spectrum.h"

//从 path/type 读取第index个NIST数据库光谱HTML格式数据到spectrum中
void readdataFromNIST(spectrum &s, const string &path, const string &type,int index);

//从 path/type 读取一组NIST数据到vector<spectrum>中,从st开始num个
void readdatasFromNIST(vector<spectrum> &v, const string &path, const string &type,int num,int st=1);
