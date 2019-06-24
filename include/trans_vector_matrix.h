#pragma once

#include <vector>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

MatrixXd vector2matrix(const vector<vector<double>> &v);

vector<vector<double>> matrix2vector(const MatrixXd &m);
