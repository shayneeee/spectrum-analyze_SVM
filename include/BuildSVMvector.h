#pragma once
#include "spectrum.h"
#include <vector>
#include <cmath>
extern const double EndWaveLength;
extern const double StaWaveLength;
extern const double Segment;

//根据寻峰完毕的光谱峰值信息，构建SVMvector
void BuildSVMvector(const spectrum &s,vector<double> &SVMvector);

