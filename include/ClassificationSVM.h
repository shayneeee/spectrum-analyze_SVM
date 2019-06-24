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

    //������������ѵ�����ݲ�����ΪSVMģ��
	void trainSVM(vector<vector<double>> PositiveSamples,
                  vector<vector<double>> NegativeSamples);	
    //��������Ԥ��
    bool predictSVM(const vector<double> &SVMvector); 

    //SVMģ������
    string modelname;

private:
    svm_node* SVMvector2svmnode(const vector<double> &v);       //��vector<double>ת��Ϊsvm_node[]
	/* svm_node* spectrum2svmnode(const spectrum &s);				//��spectrumת��Ϊsvm_node[] */
	void setParam();
	void readTrainData(const vector<vector<double>> &SVMvector, bool tag);	//����SVM�������ϵ����ݣ�����¼��Ӧ��ǩΪtag��������Ϊtrue��������Ϊfalse��

private:
	svm_parameter param;
	svm_problem prob;					//all the data to train.
	std::deque<svm_node*> datas;		//fatures of all the sample
	std::deque<double> tags;			//type of all the sample
	int SampleNum;
};
