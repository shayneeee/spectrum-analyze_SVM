#include <iostream>
#include "../include/Savitzky_Golay.h"
using namespace std;


void S_Gfilter5(spectrum &s)
{
   vector<double> v;
   s.getvalue_vector(v); 
   vector<double> v1;
   v1.push_back(v[0]);
   v1.push_back(v[1]);
   int length=v.size();
   for(int i=2; i<length-2; i++)
   {
       v1.push_back((2*v[i-2]-v[i-1]-2*v[i]-v[i+1]+2*v[i+2])/7);
   }
   v1.push_back(v[length-2]);
   v1.push_back(v[length-1]);
   s.setvalue_vector(v1);
}

void S_Gfilter7(spectrum &s)
{
   vector<double> v;
   s.getvalue_vector(v); 
   vector<double> v1;
   v1.push_back(v[0]);
   v1.push_back(v[1]);
   v1.push_back(v[2]);
   int length=v.size();
   for(int i=3; i<length-3; i++)
   {
       v1.push_back((-2*v[i-3]+3*v[i-2]+6*v[i-1]+7*v[i]+6*v[i+1]+3*v[i+2]-2*v[i+3])/21);
   }
   v1.push_back(v[length-3]);
   v1.push_back(v[length-2]);
   v1.push_back(v[length-1]);
   s.setvalue_vector(v1);
}

void S_Gfilter9(spectrum &s)
{
   vector<double> v;
   s.getvalue_vector(v); 
   vector<double> v1;
   v1.push_back(v[0]);
   v1.push_back(v[1]);
   v1.push_back(v[2]);
   v1.push_back(v[3]);
   int length=v.size();
   for(int i=4; i<length-4; i++)
   {
       v1.push_back((28*v[i-4]+7*v[i-3]-8*v[i-2]-17*v[i-1]-20*v[i]-17*v[i+1]-8*v[i+2]+7*v[i+3]+28*v[i+4])/462);
   }
   v1.push_back(v[length-3]);
   v1.push_back(v[length-2]);
   v1.push_back(v[length-1]);
   v1.push_back(v[length-4]);
   s.setvalue_vector(v1);
}
