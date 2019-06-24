#pragma once
#include "spectrum.h"
#include <vector>

//Savitzky-Golay滤波 5点，7点，9点
void S_Gfilter5(spectrum &s);

void S_Gfilter7(spectrum &s);

void S_Gfilter9(spectrum &s);
