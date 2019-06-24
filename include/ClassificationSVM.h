#pragma once
#include "../include/svm.h"
#include "../include/readdata.h"
#include "../include/data_standard.h"
#include "../include/spectrum.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

class ClassificationSVM
{
public:
	ClassificationSVM() :SampleNum(0) {};
    ~ClassificationSVM() = default;

    //输入正负样本训练数据并保存为SVM模型
	void trainSVM(vector<vector<double>> PositiveSamples,
                  vector<vector<double>> NegativeSamples);	
    //单个数据预测
    bool predictSVM(const vector<double> &SVMvector); 

    //SVM模型名称
    string modelname;

private:
    svm_node* SVMvector2svmnode(const vector<double> &v);       //将vector<double>转换为svm_node[]
	/* svm_node* spectrum2svmnode(const spectrum &s);				//将spectrum转换为svm_node[] */
	void setParam();
	void readTrainData(const vector<vector<double>> &SVMvector, bool tag);	//读入SVM向量集合的数据，并记录对应标签为tag（正样本为true，负样本为false）

private:
	svm_parameter param;
	svm_problem prob;					//all the data to train.
	std::deque<svm_node*> datas;		//fatures of all the sample
	std::deque<double> tags;			//type of all the sample
	int SampleNum;
};
