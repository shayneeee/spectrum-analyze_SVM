#include <iostream>
#include "../include/BuildSVMvector.h"
using namespace std;


/*计算SVMvector模块*/
//波长加权函数 可将区间[0,m]投影到[10,1] y=-(9/m)*x+10
double wlweight(double start,double segment,double wavelength)
{
    return -(9/segment)*(wavelength-start)+10;
}
//计算SVMvector中的每个区间加权谱峰强度值 光谱区间起点为start，长度为length
double WeightPeak(double start, double segment, const spectrum &s)
{
    //导出光谱的波长和强度信息
    vector<double> wavelength;
    vector<double> value;
    s.getwavelength_vector(wavelength);
    s.getvalue_vector(value);
    double weight=0;        //该区间的加权谱峰强度
    for(auto index:s.peak)
    {
        if(wavelength[index]>start && wavelength[index]<start+segment)
            weight+=wlweight(start,segment,wavelength[index])*sqrt(value[index]);
    }
    return weight;
}
//根据寻峰完毕的光谱峰值信息，构建SVMvector
void BuildSVMvector(const spectrum &s,vector<double> &SVMvector)
{
    if(!s.HavePeak())
    {
        cout<<"spectrum has no peak!"<<endl;
        return;
    }
    SVMvector.clear();
    
    int n=(EndWaveLength-StaWaveLength)/Segment; //总分段个数
    for(int i=0; i<n; i++)
    {
        double weight=WeightPeak(StaWaveLength+i*Segment,Segment,s);
        SVMvector.push_back(weight);
    }

}

