#include"../include/readdata.h"

void readdatas(vector<spectrum> &s,const string &path, const string &type,int num,int st)
{
	cout << " *========== \n  read data..." << endl;
	cout << "  current typepath: " << path << type << endl;
	cout << "  data numbers: from " <<st<<" to "<< st+num-1 << endl;
	cout << " *==========" << endl;
    for(int i=st;i<(st+num);i++)
    {
        spectrum tmps;
        read1data(tmps,path,type,i);
        s.push_back(tmps);
    }
	
}

void read1data(spectrum &s,const string &path,const string &type, int index)//读取单个文件
{

	string name = path + type + '/' + to_string(index) + ".data";
	//open file
	ifstream file(name);
	if (!file.is_open())
	{
		cerr << "file open failed!" << endl;
		exit(-1);
	}
	//read data
	//cout << "readdata: " << name << endl;
	while (!file.eof())
	{
		double wl;
		double tmpd;
		double sum1 = 0;
        double sum2 = 0;
		for (int k = 0; k < 2; k++)			//将相邻2个光谱数据取平均作为一个特征数据
		{
			string line;
			getline(file, line);			//一次读取一行数据
			stringstream ss(line);			//将读到的一行绑定在string流

			ss >> wl;				    	//第一个读到的是编号  无用
			ss >> wl;				    	//第二个读到的是光谱波长
			ss >> tmpd;						//第三个读到的是数据  需要保存
            sum1 += wl;
			sum2 += tmpd;
		}
        sum1 /= 2;
        sum2 /= 2;
        s.pushdata(make_pair(sum1,sum2));
	}
    s.popdata();
	file.close();
}


