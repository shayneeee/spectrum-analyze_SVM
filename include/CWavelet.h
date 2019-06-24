#ifndef _WAVELET_H_
#define _WAVELET_H_

#include <vector>
using namespace std;

namespace wavelet
{
	//小波滤波器
	typedef struct tagWaveFilter
	{
		vector<double> Lo_D;  // 小波变换分解低通滤波器
		vector<double> Hi_D; // 小波变换分解高通滤波器
		vector<double> Lo_R;  // 小波变换重构低通滤波器
		vector<double> Hi_R; // 小波变换重构高通滤波器
		int filterLen;
	}WaveFilter;

	typedef struct tagCL1D
	{//本结构体用于接收一维图像分解信息，避免参数的大量传送
		vector<int> msgLen;
		int Scale;//分解尺度
		int dbn;//db小波的编号
		int allSize;//总数据长度
	}msgCL1D;


	//typedef struct tagCL2D
	//{//本结构体用于接收二维图像分解信息，避免参数的大量传送
	//	vector<int> msgHeight;
	//	vector<int> msgWidth;
	//	int Scale;//分解尺度
	//	int dbn;//db小波的编号
	//	int allSize;//总数据长度
	//}msgCL2D;


	typedef bool SORH;

	class  CWavelet
	{
	public:
		CWavelet(int dbn=3);
		~CWavelet();

		int  DWT(
			double *pSrcData,
			int srcLen,
			double *pDstCeof
			);

		void  IDWT(double *pSrcCoef,
			int dstLen,
			double *pDstData
			);
		

		// 二维数据的小波分解
		//void  DWT2(
		//	double *pSrcImage,//源图像数据(存储成一维数据，行优先存储)
		//	int height,//图像的高
		//	int width,//图像的宽
		//	double *pImagCeof//分解出来的系数
		//	);

		//void  IDWT2(
		//	double *pSrcCeof,
		//	int height,
		//	int width,
		//	double *pDstImage
		//	);


		bool WaveDec(
			double *pSrcData,
			double *pDstCeof
			);

		bool WaveRec(
			double *pSrcCoef,
			double *pDstData
			);


		bool InitDecInfo(
			const int srcLen,
			const int Scale,
			const int dbn =3
			);

		/*bool InitDecInfo2D(
			const int height,
			const int width,
			const int Scale,
			const int dbn = 3
			);*/

		bool thrDenoise(
			double *pSrcNoise,
			double *pDstData,
			bool isHard=true
			);

		void Wthresh(
			double *pDstCoef,
			double thr,
			const int allsize,
			const int gap,
			SORH  ish
			);

		// 二维小波多级分解
		//bool WaveDec2(
		//	double *pSrcData,
		//	double *pDstCeof
		//	);

		//// 重构出二维信号
		//bool WaveRec2(
		//	double *pSrcCoef,//多级分解出的源系数
		//	double *pDstData//重构出来的信号
		//	);

		// 初始化滤波器
		void InitFilter();//放进内存

		// 选择滤波器
		void SetFilter(int dbn);

		// 获取阈值
		double getThr(
			double *pDetCoef,
			int detlen,
			bool is2D =false
			);

		//调整数据，总是将低频数据放在前面
		bool AdjustData(
			double *pDetCoef, 
			const int height,//该系数的高度
			const int width//该系数的宽度
			);

		//逆调整，还原低频数据的位置
		bool IAdjustData(
			double *pDetCoef,
			const int height,//该系数的高度
			const int width//该系数的宽度
			);

		//bool thrDenoise2D(
		//	double *pNoiseImag,//噪声图像
		//	double *pDstImag,//已经去噪的图像
		//	bool isHard = true);

	public:
		msgCL1D m_msgCL1D;
		/*msgCL2D m_msgCL2D;*/
	private:
		bool m_bInitFlag1D; //是否初始化的标志
		//bool m_bInitFlag2D; //是否初始化的标志
		WaveFilter m_dbFilter;//分解滤波器
	};
}
#endif
