#include "../include/ClassificationSVM.h"

//设置参数
void ClassificationSVM::setParam()
{
	param.svm_type = C_SVC;
	param.kernel_type = POLY;
	param.degree = 3;
	param.gamma = 0.5;
	param.coef0 = 0;
	param.nu = 0.5;
	param.cache_size = 50;
	param.C = 500;
	param.eps = 1e-3;
	param.p = 0.1;
	param.shrinking = 1;
	param.nr_weight = 0;
	param.weight = NULL;
	param.weight_label = NULL;
}

//读取SVM向量的集合，将tags设置为tag(是否为该类物质)
void ClassificationSVM::readTrainData
(const vector<vector<double>> &SVMvectors, bool tag)
{
	//将vector内数据按格式读入datas和tag
	for (int i = 0; i < (int)SVMvectors.size(); i++)		//处理每一个SVM向量
	{
        svm_node *sample=SVMvector2svmnode(SVMvectors[i]);
		double dtag = tag ? 1 : 0;		//将tag转换为double

		datas.push_back(sample);
		tags.push_back(dtag);
		SampleNum++;
	}
}

//将spectrum转换为svm_node[]
/* svm_node* ClassificationSVM::spectrum2svmnode(const spectrum &s) */
/* { */
/* 	int l = s.size(); */
/* 	svm_node* sn = new svm_node[l+1]; */
/* 	for (int i=0; i<l; i++) */
/* 	{ */
/* 		sn[i].index = i + 1;	//index从1开始 */
/* 		sn[i].value = s.getvalue(i); */
/* 	} */
/* 	sn[l].index = -1;			//标志结束 */
/* 	return sn; */
/* } */

//将vector<double>转换为svm_node
svm_node* ClassificationSVM::SVMvector2svmnode(const vector<double> &v)
{
    int l=v.size();
    svm_node *sn=new svm_node[l+1];
    for(int i=0; i<l; i++)
    {
        sn[i].index=i+1;
        sn[i].value=v[i];
    }
    sn[l].index=-1;
    return sn;

}

//利用光谱数据训练模型并存为ModelFileName
void ClassificationSVM::trainSVM(
vector<vector<double>> PositiveSamples,
vector<vector<double>> NegativeSamples)
{
    //set parameter
	setParam();
    
	//reading positive datas
	readTrainData(PositiveSamples, true);

	//reading first negative datas
	readTrainData(NegativeSamples, false);


	if ((int)datas.size() != SampleNum || (int)tags.size() != SampleNum)//长度检验
	{
		cout << "datas or tags length error." << endl;
		return;
	}
	prob.l = SampleNum;
	prob.x = new svm_node *[prob.l];
	prob.y = new double[prob.l];


	//将数据读入svm_problem
	int index = 0;
	while (!datas.empty())
	{
		prob.x[index] = datas.front();
		prob.y[index] = tags.front();
		datas.pop_front();
		tags.pop_front();
		index++;
	}

	svm_model *SVMmodel= svm_train(&prob, &param);
	
    cout<<"*============================"<<endl;
    cout<<"saving SVMmodel..."<<endl;
    cout<<"*============================"<<endl;
	svm_save_model(modelname.c_str(), SVMmodel);

}

//单个数据预测
bool ClassificationSVM::predictSVM(const vector<double> &SVMvector)		
{
	svm_node *sample =SVMvector2svmnode(SVMvector);
	svm_model *SVMmodel = svm_load_model(modelname.c_str());
	double predictvalue = svm_predict(SVMmodel, sample);		//返回值为1或0
	return predictvalue ? true : false;
}

/* //一组数据预测 */
/* void ClassificationSVM::multi_predictSVM */
/* (vector<bool> &v,               //存放预测结果 */
/*  const string &ModelFileName)   //预测所用的模型名称 */			
/* { */
/* 	string modelname, type; */
/* 	int st, num; */
/* 	cout << "start predicting..."<<endl; */
/* 	cout << "input predict datas (type startindex number):" << endl; */
/* 	cin >> type; */
/* 	cin >> st; */
/* 	cin >> num; */
/* 	cout << "predicting..." << endl; */
/* 	vector<spectrum> datav; */
/* 	readdatas(datav, path,type, num, st);				//读取预测数据到datav中 */
/* 	vector<bool> judge; */

/* 	for (auto v : datav) */
/* 	{ */
/* 		data_standard1(v); */
/* 		judge.push_back(predictSVM(v, ModelFileName.c_str())); */
/* 	} */

/* 	cout << "classification resluts:" << endl; */
/* 	cout << boolalpha;			//控制输出true和false而不是1和0 */
/* 	for (auto b : judge) */
/* 	{ */
/* 		cout << b << " "; */
/* 	} */
/* 	cout << noboolalpha<<endl; */
/* } */
