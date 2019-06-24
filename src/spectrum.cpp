#include "../include/spectrum.h"

void spectrum::getvalue_vector(vector<double> &v)const
{
    if(!v.empty())  //导入数据前判断v是否为空
    {
        v.clear();
    }
    for(auto p:datas)
    {
        v.push_back(p.second);
    }
}

void spectrum::setvalue_vector(vector<double> &v)
{
    int l=v.size();
    for(int i=0;i<l;i++)
    {
        datas[i].second=v[i];
    }
    v.clear();
}


void spectrum::getwavelength_vector(vector<double> &v)const
{
    if(!v.empty())  //导入数据前判断v是否为空
    {
        v.clear();
    }
    for(auto p:datas)
    {
        v.push_back(p.first);
    }

}

int spectrum::size()const
{
    return datas.size();
}

double spectrum::getvalue(int index)const
{
    return datas[index].second;
}

void spectrum::setvalue(int index,double value)
{
    datas[index].second=value;
}

double spectrum::getwavelength(int index)const
{
    return datas[index].first;
}

void spectrum::printdata(const string &path,const string &name)const
{
    /* string printpath="/home/shayne/c++project/spectrum_analysis/printdata/"+name; */
    string printpath=path+name;
    ofstream of(printpath);
    if(!of)
    {
        cerr<<"open ofstream failed!"<<endl;
        exit(-1);
    }
    for(auto p:datas)
    {
        of<<p.first<<" "<<p.second<<endl;
    }
    of.close();
}

void spectrum::FindPeak()
{
    int length=datas.size();
    vector<double> value;   //datas中的数值信息
    getvalue_vector(value);
    
    for(int i=3; i<length-3; i++)   //7点寻峰头尾各3各数据舍去
    {
        if(value[i]>value[i-1] && value[i-1]>value[i-2] && value[i-2]>value[i-3]
           && value[i]>value[i+1] && value[i+1]>value[i+2] && value[i+2]>value[i+3]
           && value[i]>5)
            peak.push_back(i);
    }
}

//将数值调整在1-100以后两端的平均斜率大于1.5的峰保留
void spectrum::PeakShapSelect()
{
    for(auto iter=peak.begin(); iter!=peak.end(); iter++)
    {
        int index=*iter;  //谱峰在datas中的下标
        //计算谱峰附近4点的斜率
        double k1=fabs((datas[index+2].second-datas[index+1].second)/(datas[index+2].first-datas[index+1].first));
        double k2=fabs((datas[index+1].second-datas[index].second)/(datas[index+1].first-datas[index].first));
        double k3=fabs((datas[index].second-datas[index-1].second)/(datas[index].first-datas[index-1].first));
        double k4=fabs((datas[index-1].second-datas[index-2].second)/(datas[index-1].first-datas[index-2].first));

        double k=(k1+k2+k3+k4)/4;   //谱峰附近平均斜率

        if(k<1.5)
            peak.erase(iter);
        if(iter==peak.end())
            break;
    }
}
