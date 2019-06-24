#include"trans_vector_matrix.h"

MatrixXd vector2matrix(const vector<vector<double>> &v)
{
	MatrixXd m;
	int x = v.size();		//矩阵行数
	int y = v[0].size();	//矩阵列数
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
			m(i,j) = v[i][j];
	}
	return m;
}

vector<vector<double>> matrix2vector(const MatrixXd &m)
{
	vector<vector<double>> v;
	int x = m.rows();
	int y = m.cols();
	for (int i = 0; i < x; i++)
	{
		vector<double> tmpv;
		for (int j = 0; j < y; j++)
		{
			tmpv.push_back(m(i, j));
		}
		v.push_back(tmpv);
	}
	return v;
}