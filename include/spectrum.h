#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class spectrum
{
public:
    spectrum()=default;
    ~spectrum()=default;
    void pushdata(pair<double,double> p){datas.push_back(p);}//将数据读入datas
    void popdata(){datas.pop_back();}                       //pop出datas的最后一组数据
    void getvalue_vector(vector<double> &v)const;           //将value数组copy入v中
    void setvalue_vector(vector<double> &v);                //将v的数据导入value,并清空v
    void getwavelength_vector(vector<double> &v)const;      //将波长数组copy入v中
    int size()const;                                        //返回样本特征数
    double getvalue(int index)const;                        //获取第index个数据对应的value
    void setvalue(int index,double value);                  //设置第index个数据对应的value
    double getwavelength(int index)const;                   //获取第index个数据对应的wavelength
    void printdata(const string &path,const string &name)const; //将光谱导出到path内名为name的文件内

    void FindPeak();        //将光谱谱峰下标放入peak
    void PeakShapSelect();  //筛选光谱谱峰峰形，去除peak中的无效谱峰
    bool HavePeak()const {return !peak.empty();}   //判断光谱数据是否完成寻峰

    vector<int> peak;    //peak内元素为谱峰在datas中的下标
private:
    //pair 中第一个double为波长，第二个double为对应的value数值
    vector<pair<double,double>> datas;
    //存放谱峰位置信息
};

