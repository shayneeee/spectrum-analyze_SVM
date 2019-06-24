#ifndef _WAVELET_H_
#define _WAVELET_H_

#include <vector>
using namespace std;

namespace wavelet
{
	//С���˲���
	typedef struct tagWaveFilter
	{
		vector<double> Lo_D;  // С���任�ֽ��ͨ�˲���
		vector<double> Hi_D; // С���任�ֽ��ͨ�˲���
		vector<double> Lo_R;  // С���任�ع���ͨ�˲���
		vector<double> Hi_R; // С���任�ع���ͨ�˲���
		int filterLen;
	}WaveFilter;

	typedef struct tagCL1D
	{//���ṹ�����ڽ���һάͼ��ֽ���Ϣ����������Ĵ�������
		vector<int> msgLen;
		int Scale;//�ֽ�߶�
		int dbn;//dbС���ı��
		int allSize;//�����ݳ���
	}msgCL1D;


	//typedef struct tagCL2D
	//{//���ṹ�����ڽ��ն�άͼ��ֽ���Ϣ����������Ĵ�������
	//	vector<int> msgHeight;
	//	vector<int> msgWidth;
	//	int Scale;//�ֽ�߶�
	//	int dbn;//dbС���ı��
	//	int allSize;//�����ݳ���
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
		

		// ��ά���ݵ�С���ֽ�
		//void  DWT2(
		//	double *pSrcImage,//Դͼ������(�洢��һά���ݣ������ȴ洢)
		//	int height,//ͼ��ĸ�
		//	int width,//ͼ��Ŀ�
		//	double *pImagCeof//�ֽ������ϵ��
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

		// ��άС���༶�ֽ�
		//bool WaveDec2(
		//	double *pSrcData,
		//	double *pDstCeof
		//	);

		//// �ع�����ά�ź�
		//bool WaveRec2(
		//	double *pSrcCoef,//�༶�ֽ����Դϵ��
		//	double *pDstData//�ع��������ź�
		//	);

		// ��ʼ���˲���
		void InitFilter();//�Ž��ڴ�

		// ѡ���˲���
		void SetFilter(int dbn);

		// ��ȡ��ֵ
		double getThr(
			double *pDetCoef,
			int detlen,
			bool is2D =false
			);

		//�������ݣ����ǽ���Ƶ���ݷ���ǰ��
		bool AdjustData(
			double *pDetCoef, 
			const int height,//��ϵ���ĸ߶�
			const int width//��ϵ���Ŀ��
			);

		//���������ԭ��Ƶ���ݵ�λ��
		bool IAdjustData(
			double *pDetCoef,
			const int height,//��ϵ���ĸ߶�
			const int width//��ϵ���Ŀ��
			);

		//bool thrDenoise2D(
		//	double *pNoiseImag,//����ͼ��
		//	double *pDstImag,//�Ѿ�ȥ���ͼ��
		//	bool isHard = true);

	public:
		msgCL1D m_msgCL1D;
		/*msgCL2D m_msgCL2D;*/
	private:
		bool m_bInitFlag1D; //�Ƿ��ʼ���ı�־
		//bool m_bInitFlag2D; //�Ƿ��ʼ���ı�־
		WaveFilter m_dbFilter;//�ֽ��˲���
	};
}
#endif
