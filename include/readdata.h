#pragma once

#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include"../include/spectrum.h"
using namespace std;


//�� path\type �ڴӵ�st�����ݿ�ʼ��ȡnum���ļ�,ÿ���ļ����ݷ���һ��vector<double>��,��num���ļ�������push_back��v��
void readdatas(vector<spectrum> &v,const string &path,const string &type,int num,int st=1);	
//�� path\type �ڶ�ȡ��index���ļ��������v��
void read1data(spectrum &s, const string &path,const string &type, int index);
