#include<iostream>
#include<stdlib.h>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<cmath>
#include<ctime>
#include <algorithm>
using namespace std;



//�ռ����Ϊƽ��ֱ������ϵ��һ������
//����˵��
//    2    |    3
//         |    
//---------|-----------
//         |
//    1    |    0

typedef struct ObInf				//Ŀ���������ṹ��
{
	int l;
	int r;
}ObInf;

typedef struct QuadBox				//��ʾ��Χ�Ľṹ��
{
	int maxl;
	int minl;
	int maxr;
	int minr;
}QuadBox;

typedef struct QuadNode				//�Ĳ����ڵ�ṹ��
{
	QuadBox box;
	vector<ObInf> object;
	int ObCount;
	struct QuadNode *parent;
	struct QuadNode *children[4];
}QuadNode;

typedef struct QuadTree				//�Ĳ����ṹ��
{
	QuadNode *p;
	int depth;
}QuadTree;

typedef struct SplitPointInf
{
	double d;
	ObInf coordinate;
}SplitPointInf;


QuadTree *InitQuadTree(QuadBox box,vector<vector<int> > AdjMatrix);
void AddObject(ObInf splitpoint,QuadNode *p,ObInf ob);
QuadNode *AddNode(QuadNode *p,QuadBox box,QuadNode *parent);
QuadBox &InitQuadBox(vector<vector<int> > AdjMatrix);
void ViewTree(QuadNode *p,int n);
int GetNodeHight(QuadNode *p);
int &CalculateTreeHight(const int v);
vector<vector<int> > CreatDenMatrix(vector<vector<int> > AdjMatrix);
ObInf &GetSplitPoint(vector<vector<int> > AdjMatrix,vector<vector<int> > DenMatrix,int minsize,int splittimes,int nh,int v);
void SplitQuadNode(QuadTree *pt,QuadNode *p,const int splittimes,vector<vector<int> > AdjMatrix);
void InitQuadNode(ObInf splitpoint,QuadNode *p);
int NoisyCount(//double epsilon,				//��˽Ԥ��
			   double ranNum,
			   int ObCount,					//Ҷ�ӽڵ���1�ĸ���
			   int i,						//��ǰ���ĸ߶�
			   int h						//���ĸ߶�
	);
double RanNumber(int n);
vector<double> BubbleSort(vector<double> L,int n);//ð������
int ExpCount(int i,//��ǰ���ĸ߶�
			 int h,//���ĸ߶�
			 int v,//�����С
			 int n,//���ѵ���������ѵ�����Ĵ�С
			 vector<double> dis//�洢���ѵ��Ӧ�ܶȲ�
			 );