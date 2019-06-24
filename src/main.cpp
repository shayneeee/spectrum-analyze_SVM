#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "../include/spectrum.h"
#include "../include/BuildElementDatabase.h"
#include "../include/MatchElement.h"
#include "../include/readdata.h"
#include "../include/data_standard.h"
#include "../include/readdataFromNIST.h"
#include "../include/debackground.h"
#include "../include/BuildSVMvector.h"
#include "../include/CWavelet.h"
#include "../include/CWaveDenoise.h"
#include "../include/ClassificationSVM.h"
#include "../include/trans_vector_matrix.h"
#include "../include/svm.h"
#include "../include/MySQLSet.h"

using namespace std;

//设定光谱数据路径
const string DataPath = "/home/shayne/c++project/spectrum_analysis/NISTdata/";

//设定有效光谱范围(nm)
const double StaWaveLength=200;
const double EndWaveLength=900;

//设定光谱分段长度(nm)
const double Segment=5;

//存放元素发射谱峰数据文件路径
const string elementdatapath="/home/shayne/c++project/spectrum_analysis/element.data";

//定义数据库相关参数
const char host[]=     "localhost";
const char username[]= "root";
const char psw[]=      "root";
const char database[]= "peak";
const int port=        3306;
MYSQL conn;
MYSQL_RES *result;//代表返回行的一个查询结果集

//存放SVMvector数据，多个函数需要使用所以设为全局
vector<vector<double>> SVMvectors1;
vector<vector<double>> SVMvectors2;
vector<vector<double>> SVMvectors3;



//对读取的数据去噪并标准化并去背景
//对每个光谱对象寻峰，匹配峰形
void PreprocessAndFindPeak(spectrum &s)
{
    /* CWaveDenoise(s); */
    data_standard1(s);
    /* debackground(s); */
    s.FindPeak();
    s.PeakShapSelect();
}


void ReadSpectrumData()     //读入光谱数据并转换为SVMvector
{
    cout<<"*================================"<<endl;
    cout<<"[readdata]"<<endl;
    cout<<"*================================"<<endl;

    //读取第一类光谱数据
    //从 DataPath/type1/ 内第一张开始读取num个光谱数据到spectrums1中
    vector<spectrum> spectrums1;
    cout<<"please enter typenname1:"<<endl;
    string type1;
    cin>>type1;
    cout<<"please enter the number of spectrums:"<<endl;
    int num=0;
    cin>>num;
    readdatasFromNIST(spectrums1,DataPath,type1,num);

    //读取第二类光谱数据
    //从 DataPath/type2/ 内第一张开始读取num个光谱数据到spectrums2中
    vector<spectrum> spectrums2;
    cout<<"please enter typenname2:"<<endl;
    string type2;
    cin>>type2;
    cout<<"please enter the number of spectrums:"<<endl;
    num=0;
    cin>>num;
    readdatasFromNIST(spectrums2,DataPath,type2,num);

    //读取第三类光谱数据
    //从 DataPath/type3/ 内第一张开始读取num个光谱数据到spectrums3中
    vector<spectrum> spectrums3;
    cout<<"please enter typenname3:"<<endl;
    string type3;
    cin>>type3;
    cout<<"please enter the number of spectrums:"<<endl;
    num=0;
    cin>>num;
    readdatasFromNIST(spectrums3,DataPath,type3,num);
    
    cout<<"*================================"<<endl;
    cout<<"[process and find peak...]"<<endl;
    cout<<"*================================"<<endl;
    sleep(2);
    //对光谱数据小波去噪，标准化，去背景
    //对光谱数据寻峰，峰形匹配
    for(auto &i:spectrums1)
    {
        PreprocessAndFindPeak(i);
    }
    for(auto &i:spectrums2)
    {
        PreprocessAndFindPeak(i);
    }
    for(auto &i:spectrums3)
    {
        PreprocessAndFindPeak(i);
    }

    cout<<"*================================"<<endl;
    cout<<"[transform SVMvector...]"<<endl;
    cout<<"*================================"<<endl;
    //将每组光谱数据转换为SVMvector

    vector<double> svmvector;   //临时储存每一个计算出的svmvector
    
    for(int i=0; i<(int)spectrums1.size(); i++)
    {
        svmvector.clear();
        BuildSVMvector(spectrums1[i],svmvector);
        SVMvectors1.push_back(svmvector);
    }
    for(int i=0; i<(int)spectrums2.size(); i++)
    {
        svmvector.clear();
        BuildSVMvector(spectrums2[i],svmvector);
        SVMvectors2.push_back(svmvector);
    }
    for(int i=0; i<(int)spectrums3.size(); i++)
    {
        svmvector.clear();
        BuildSVMvector(spectrums3[i],svmvector);
        SVMvectors3.push_back(svmvector);
    }

}
ClassificationSVM* SVMTrain()//建立SVM模型
{
    
    cout<<"*================================"<<endl;
    cout<<"[select samples...]"<<endl;
    cout<<"*================================"<<endl;
    //建立Type1正负样本
    vector<vector<double>> PosiSamples;
    vector<vector<double>> NegaSamples;
    int numofs;
    while(1)
    {
        cout<<"inmput num of PosiSamples from type1: "<<endl;
        cin>>numofs;
        if(numofs>(int)SVMvectors1.size())
            cout<<"invalid num."<<endl;
        else
            break;
    }
    for(int i=0; i<numofs; i++)
        PosiSamples.push_back(SVMvectors1[i]);
    while(1)
    {
        cout<<"inmput num of NegaSamples form type2 and type3: "<<endl;     //负样本用另外两类对半建立
        cin>>numofs;
        if(numofs>(int)SVMvectors2.size()+(int)SVMvectors3.size())
            cout<<"invalid num."<<endl;
        else
            break;
    }
    for(int i=0; i<numofs/2; i++)
        NegaSamples.push_back(SVMvectors2[i]);
    for(int i=numofs/2; i<numofs; i++)
        NegaSamples.push_back(SVMvectors3[i-numofs/2]);
    
    cout<<"*================================"<<endl;
    cout<<"[building SVMmodel...]"<<endl;
    cout<<"*================================"<<endl;
    //通过SVMvector训练SVM模型 并保存为modelname
    ClassificationSVM *pType_SVM=new ClassificationSVM();
    cout<<"input name of SVMmodel:"<<endl;
    cin>>pType_SVM->modelname;
    pType_SVM->trainSVM(PosiSamples,NegaSamples);
    cout<<"*================================"<<endl;
    cout<<"[done!]"<<endl;
    cout<<"*================================"<<endl;
    return pType_SVM;
}

bool PredictSpectrum(ClassificationSVM *pType_SVM)
{
    cout<<"*================================"<<endl;
    cout<<"[pridict sample...]"<<endl;
    cout<<"*================================"<<endl;
    //预测光谱类型
    cout<<"input type(1-3) and index:"<<endl;
    int predicttype;
    int predictindex;
    cin>>predicttype;
    cin>>predictindex;

    vector<double> predictSVMvector;
    switch(predicttype)
    {
    case 1:
        predictSVMvector=SVMvectors1[predictindex];
        break;
    case 2:
        predictSVMvector=SVMvectors2[predictindex];
        break;
    case 3:
        predictSVMvector=SVMvectors3[predictindex];
        break;
    default:
        cout<<"invalid predictSVMvector."<<endl;
    }

    bool predictresult=pType_SVM->predictSVM(predictSVMvector);
    cout<<boolalpha<<"predict result: "<<predictresult<<endl<<noboolalpha;
    return predictresult;
}


void test()
{
    string type="type2";
    int index=1;
    spectrum s;
    readdataFromNIST(s,DataPath,type,index);
    /* CWaveDenoise(s); */
    data_standard1(s);
    /* debackground(s); */
    s.FindPeak();
    s.PeakShapSelect();
    vector<double> svmvec;
    BuildSVMvector(s,svmvec);

}

void elementmatch()
{
    cout<<"please input type and index:"<<endl;
    string type;
    cin>>type;

    for(int index=1; index<21; index++)
    {
        spectrum s;
        readdataFromNIST(s,DataPath,type,index);
        vector<pair<string,vector<double>>> result=matchelement(s);
        printresult(result);
    }

}

int main()
{
    
    ReadSpectrumData();
    ClassificationSVM *pSVM=SVMTrain();
    while(1)
        PredictSpectrum(pSVM);

    /* buildelementdatabase(); */

    /* while(1) */
    /*     elementmatch(); */

	return 0;
}
