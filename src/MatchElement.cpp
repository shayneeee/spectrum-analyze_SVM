#include "../include/MatchElement.h"

 //匹配波长为wavelength对应的元素放入element，若匹配不到则返回false
bool matchpeak(double wavelength,string &element)  {
    int res=0;
    string matchpeak=
        "SELECT abs(wavelength-"+to_string(wavelength)+") AS diff , element \
        FROM element, peak \
        WHERE element.elementnum=peak.elementnum \
        ORDER BY diff \
        limit 1";
    const char *q=matchpeak.data();
    res=mysql_query(&conn,q);
    if(res==1)
        cout<<"matchpeak error!"<<endl;

    result=mysql_store_result(&conn);
    int rows=mysql_num_rows(result);
    if(rows!=1)
    {
        cout<<"ElementMatch return not 1 row !";    //正常情况下应该返回一行 rows=1
        return false;
    }

    MYSQL_ROW row=mysql_fetch_row(result);
    //返回的一行row的结构为： 
    //偏差(nm)  元素名称
    char *c_diff=row[0];     
    char *c_elemrnt=row[1];
    double diff=atof(c_diff);
    if(diff<0.3)  //允许偏差设为：+-0.3nm
    {
        element=c_elemrnt;
        return true;
    }
    else
        return false;
}

//对光谱s进行元素匹配，返回匹配结果
//其中pair<string,vector<double>> string时元素名称，vector<double>是光谱中匹配该元素的谱峰位置
vector< pair< string,vector<double> > >matchelement(spectrum &s)
{
    if(!s.HavePeak())   //若光谱数据还未寻峰则先寻峰
    {
        s.FindPeak();
        s.PeakShapSelect();
    }

    ConnectDatabase();   //链接数据库

    vector<double> peaks;
    for(auto i:s.peak)      //将s.peak内对应的谱峰波长存入peaks
        peaks.push_back(s.getwavelength(i));

    vector< pair<string, vector<double> > > elementvect;    //用来保存返回的匹配结果
    
    for(auto i:peaks)       //对光谱s的每一个峰值进行匹配
    {
        string element;
        //如果该峰匹配到一个元素,若匹配结果集合已包含该元素则将该峰位置存入匹配结果中元素对应的vector内
        //若匹配结果还未包含该元素，则将该元素和峰值位置插入匹配结果中
        if(matchpeak(i,element))    
        {
            bool elementexist=false;    //标志匹配的元素是否在匹配结果集中
            for(auto &j:elementvect)
            {
                if(j.first==element)    //匹配结果集已有该元素，添加对应的谱峰位置
                {
                    j.second.push_back(i);
                    elementexist=true;
                }
            }
            if(!elementexist)           //匹配结果集还没有该元素，将元素和谱峰位置都加入结果集
            {
                vector<double> peakofelement;
                peakofelement.push_back(i);
                elementvect.push_back(make_pair(element,peakofelement));
            }
        }
    }

    //将元素匹配后峰值个数小于3个的元素舍去
    for(int i=0; i<(int)elementvect.size(); i++)    
    {
        if(elementvect.at(i).second.size()<3)
        {
            elementvect.erase(elementvect.begin()+i);
            i-=1;
        }
    }

    FreeConnect();   //断开数据库链接并释放资源

    //返回匹配结果集
    return elementvect;
}

//将匹配结果打印到控制台
void printresult(vector< pair< string, vector<double> > > &result)
{
    int numofelement=result.size();
    if(numofelement<1)
        return;

    cout<<"*=======match result:"<<endl;
    cout<<"there are "<<numofelement<<" element(s) in this spectrum."<<endl;
    for(auto i:result)
    {
        cout<<i.first<<" : "<<'('<<i.second.size()<<')'<<" ";
        for(auto j:i.second)
            cout<<j<<" ";
        cout<<endl;
    }
    cout<<"*======="<<endl;
}
