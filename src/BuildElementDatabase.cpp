#include "../include/BuildElementDatabase.h"

void InsertElement()    //构建表 element 存放元素序号及其名称
{
    //先清空表 element
    int res=0;
    string cleartable=
        "TRUNCATE element";
    const char *pq=cleartable.data();
    res=mysql_query(&conn,pq);
    if(res==1)
        cout<<"truncate element table error!"<<endl;

    //像表内插入数据
    string insertelement=
        "INSERT INTO element \
        (elementnum,element) \
        VALUES \
        ('1','H'), \
        ('2','He'), \
        ('3','Li'), \
        ('4','Be'), \
        ('5','B'), \
        ('6','C'), \
        ('7','N'), \
        ('8','O'), \
        ('9','F'), \
        ('10','Ne'), \
        ('11','Na'), \
        ('12','Mg'), \
        ('13','Al'), \
        ('14','Si'), \
        ('15','P'), \
        ('16','S'), \
        ('17','Cl'), \
        ('18','Ar'), \
        ('19','K'), \
        ('20','Ca'), \
        ('21','Sc'), \
        ('22','Ti'), \
        ('23','V'), \
        ('24','Cr'), \
        ('25','Mn'), \
        ('26','Fe'), \
        ('27','Co'), \
        ('28','Ni'), \
        ('29','Cu'), \
        ('30','Zn'), \
        ('31','Ga'), \
        ('32','Ge'), \
        ('33','As'), \
        ('35','Br'), \
        ('36','Kr'), \
        ('47','Ag'), \
        ('50','Sn'), \
        ('53','I'), \
        ('74','w'), \
        ('79','Au'), \
        ('80','Hg'), \
        ('82','Pb')";
    const char *q=insertelement.data();
    res=mysql_query(&conn,q);
    if(res==1)
        cout<<"InsertElement error!"<<endl;
    else 
        cout<<"InsertElement success!"<<endl;
}

//向表peak插入一条数据 包括谱峰位置和元素序号
void InsertOnePeak(int elementnum, double wavelength, string element)
{
    int res=0;
    string inserpeak=
        "INSERT INTO peak \
        (elementnum,wavelength) \
        VALUES \
        ('"+to_string(elementnum)+"','"+to_string(wavelength)+"')";
    const char *q=inserpeak.data();
    res=mysql_query(&conn,q);
    if(res==1)
        cout<<"InsertPeak error! element: "<<element<<" wavelength: "<<wavelength<<endl;
}

//用elementdata文件内容构造表peak
void InsertPeak()
{
    //先清空表peak
    int res=0;
    string cleartable=
        "TRUNCATE peak";
    const char *pq=cleartable.data();
    res=mysql_query(&conn,pq);
    if(res==1)
        cout<<"truncate peak table error!"<<endl;

    //打开数据文件并写入表peak
    ifstream file(elementdatapath);
    //open file
    if(!file.is_open())
    {
        cout<<"elementdata open failed!"<<endl;
        return;
    }
    //read datas
    while(!file.eof())
    {
        int elementnum;
        string element;
        double wavelength;

        string line;
        getline(file,line);
        if(!line.empty())
        {
            stringstream ss(line);

            ss>>elementnum;      //读取元素序号
            ss>>element;         //读取元素名称
            while(ss>>wavelength)//读取元素峰位置
            {
                InsertOnePeak(elementnum,wavelength,element);
            }
            cout<<"elementdata of "<<element<<" insert success!"<<endl;
        }
    }
}

//构造元素数据库
void buildelementdatabase()
{
    ConnectDatabase();  //链接数据库
    InsertElement();    //构造element表
    InsertPeak();       //构造peak表
    FreeConnect();      //断开链接
}
