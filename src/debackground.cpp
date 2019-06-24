#include "../include/debackground.h"

//迭代拟合法进行基线除去
int m1=4;    //两倍半高宽
int numofiteration=40;    //迭代次数
void debackground(spectrum &s)
{
    vector<double> data;
    vector<double> data1;   //处理后的数据
    s.getvalue_vector(data);
    while(numofiteration--)
    {
        for(int i=0; i<m1; i++)
        {
            data1.push_back(data[i]);
        }
        for(int i=m1; i<(int)data.size()-m1; i++)
        {
            data1.push_back((data[i-m1]+data[i+m1])/2);
        }
        for(int i=(int)data.size()-m1; i<(int)data.size(); i++)
        {
            data1.push_back(data[i]);
        }
        data.clear();
        data=data1;
        data1.clear();
    }

    //原始数据减去基线
    s.getvalue_vector(data1);
    if(data1.size()!=data.size())
        cerr<<"length error";
    for(int i=0; i<(int)data.size(); i++)
    {
        if(data1[i]-data[i]>20)
            data1[i]-=data[i];
        else
            data1[i]=0;
    }
    s.setvalue_vector(data1);
}

