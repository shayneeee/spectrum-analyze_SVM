#pragma once

#include<vector>
#include<cmath>
#include<algorithm>
#include "../include/spectrum.h"
using namespace std;

//数据去无量纲化及去中心化
void data_standard(vector<spectrum> &v);

void data_standard1(spectrum &s);
