#pragma once

#include <vector>
#include "CWavelet.h"
#include "spectrum.h"

void CWaveDenoise(spectrum &s)
{
    vector<double> data;
    s.getvalue_vector(data);
    int length=data.size();

    double *datad=new double[length];   //将vector内数据转换到double*中

    for(int i=0; i<length; i++)
    {
        datad[i]=data[i];
    }

    double *dndata=new double[length];  //小波阈值去噪以后的数据
    wavelet::CWavelet cw;
    int scale=3;
    int dbn=3;
    cw.InitDecInfo(length,scale,dbn);
    cw.thrDenoise(datad,dndata,true);

    for(int i=0; i<length; i++)
    {
        data[i]=dndata[i];
    }
    s.setvalue_vector(data);
    delete []datad;
    delete []dndata;
}



