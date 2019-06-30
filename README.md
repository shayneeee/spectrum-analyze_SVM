# spectrum-analyze_SVM


## 一个基于SVM分类器实现的光谱识别软件，主要有两个功能：
1. 利用SVM分类器对光谱数据进行建模，预测所属类别
2. 利用MySQL建立元素谱峰数据库，用其c++的API进行谱峰匹配

附带两组光谱数据./datas 和 ./NISTdata

## 光谱分类：
>对一类物质光谱建立一个ClassificationSVM类，分别输入正负样本进行训练模型并保存，再输入任意待测光谱以及SVM模型名称，可进行类型识别。多分类问题可使用一对多建模。
## 元素匹配：
>建立数据库时需要按照程序内格式在MySQL内建立peak数据库和两个表，然后可以用程序中的函数填充数据库内容。
利用MySQL的c++API，将MySQL匹配脚本传入数据库，再获取结果。

### 更多光谱数据
https://www.nist.gov/pml/atomic-spectroscopy-databases
