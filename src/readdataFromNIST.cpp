#include <iostream>
#include "../include/readdataFromNIST.h"
using namespace std;


//从 path/type 读取第index个NIST数据库光谱HTML格式数据到spectrum中
void readdataFromNIST(spectrum &s, const string &path, const string &type,int index)
{
    string name=path + type + '/' + to_string(index) + ".data";
    //open file
    ifstream file(name);
    if(!file.is_open())
    {
        cerr<<"file open failed!"<<endl;
        exit(-1);
    }
    //read data
    while(!file.eof())
    {
        double wavelength;
        double intensity;
        
        string line;
        getline(file,line);
        stringstream ss(line);

        ss>>wavelength;
        ss>>intensity;
        
        intensity=pow(intensity,1.0/2.0);       //缩小光谱值范围
        intensity= intensity>1 ? intensity : 0;

        s.pushdata(make_pair(wavelength,intensity));
    }
    s.popdata();
    file.close();
}

//从 path/type 读取一组NIST数据到vector<spectrum>中,从st开始num个
void readdatasFromNIST(vector<spectrum> &v, const string &path, const string &type,int num,int st)
{
	cout << " *========== \n  read data..." << endl;
	cout << "  current typepath: " << path << type << endl;
	cout << "  data numbers: from " <<st<<" to "<< st+num-1 << endl;
	cout << " *==========" << endl;
    for(int i=st; i<(st+num); i++)
    {
        spectrum tmp;
        readdataFromNIST(tmp, path, type, i);
        v.push_back(tmp);
    }
}
