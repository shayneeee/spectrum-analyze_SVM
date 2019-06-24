#include"data_standard.h"

void data_standard(vector<spectrum> &v)
{
	int n = v.size();		//样本个数
	int p = v[0].size();	//样本特征数


	////对每一个特征进行进行中心化及无量纲化
	//vector<double> average;		//存放特征的均值
	//vector<double> variance;	//存放特征的方差
	////计算均值
	//for (int j = 0; j < p; j++)
	//{
	//	double sum = 0;
	//	for (int i = 0; i < n; i++)
	//	{
	//		sum += v[i].getvalue(j);
	//	}
	//	average.push_back(sum / n);
	//}
	////计算方差
	//for (int j = 0; j < p; j++)
	//{
	//	double tmp = 0;
	//	for (int i = 0; i < n; i++)
	//	{
	//		tmp += pow(v[i].getvalue(j) - average[j], 2);
	//	}
	//	variance.push_back(tmp / n);
	//}
	////数据处理
	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < p; j++)
	//	{
	//		v[i].setvalue(j, v[i].getvalue(j) - average[j]);
	//		if (variance[j]!=0)
	//			v[i](j, v[i].getvalue(j)/ variance[j]);
	//	}
	//		
	//}

	//将每个样本印射在[0,100]范围内
	for (int i = 0; i < n; i++)
	{
        data_standard1(v[i]);
	}
}

//将样本映射在1-100
void data_standard1(spectrum &s)
{
    vector<double> value;
    s.getvalue_vector(value);
	double max = *max_element(value.begin(), value.end());
	double min = *min_element(value.begin(), value.end());
	for (auto &elem : value)
    {
        if(elem<0)
            elem=0;
        else
            elem = (elem - min) * 100 / (max - min);
    }
    s.setvalue_vector(value);
}
