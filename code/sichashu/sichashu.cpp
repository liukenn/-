
#include"stdafx.h"


#include"declare.h"
using namespace std;

int main()
{
	vector<vector<int> > AdjMatrix,DenMatrix;									//AdjMatrix���洢�ڽӾ��� DenMatrix���洢���ɵ��ܶȾ��� ��ʹ�ö�ά��vector�洢

	int a;
	ifstream fin("adjmatrixtest.txt");
	//ifstream fin("D://test(4).txt");
	if(fin==NULL)
	{
		cout<<"open file failed!"<<endl;
		return 0;
	}
	int v;
	cout<<"�����ڽӾ����Сv��"<<endl;											//�����С��Ҫ�ֶ�����
	cin>>v;
	vector<int> temp(v);
	for(int i=0;i<v;++i)														//��ȡ�洢�ڲ����ļ��е��ڽӾ��� ʵ�ʳ�����֮ǰӦ���Ѿ������� ����ûд�ɺ���
	{
		for(int j=0;j<v;++j)
		{
			fin>>a;
			temp[j]=a;
		}
		AdjMatrix.push_back(temp);

	}																			//�����ڽӾ���
	cout<<"�ѳɹ������ڽӾ������ܶȾ���"<<endl;								//������ʹ������ڽӾ������Ĳ���


	QuadTree *pt;																//����������Ĳ���
	QuadBox box;
	vector<ObInf> ob;
	box=InitQuadBox(AdjMatrix);													
	pt=InitQuadTree(box,AdjMatrix);
	cout<<"�Ѹ����ڽӾ����ʼ���Ĳ���!"<<endl;
	int splittimes=CalculateTreeHight(v);	
	SplitQuadNode(pt,pt->p,splittimes,AdjMatrix);
	cout<<"��������Ĳ����߶���"<<pt->depth<<endl;
	int n=1;
	ViewTree(pt->p,n);	//�����������Ĳ���

	return 0;
}



QuadBox &InitQuadBox(vector<vector<int> > AdjMatrix)
{
	int size;
	QuadBox box;
	size=AdjMatrix.size();
	box.maxl=size;
	box.maxr=size;
	box.minl=1;
	box.minr=1;
	return box;
}


QuadTree *InitQuadTree(QuadBox box,vector<vector<int> > AdjMatrix)					//��ʼ���Ĳ�������Ҫ����Ϊ��Χ��Сbox��֮ǰ���ɵ��ڽӾ���
{
	QuadTree *pt;
	pt=(QuadTree *)new(QuadTree);
	if(pt==NULL)
	{
		cout<<"��ʼ�ռ�������"<<endl;
		system("PAUSE");
		return 0;		
	}
	pt->p=AddNode(pt->p,box,NULL);
	pt->depth=0;
	int size=AdjMatrix.size();
	ObInf tempob;
	for(int i=0;i<size;++i)
		for(int j=0;j<size;++j)
		{
			if(AdjMatrix[i][j]==1)
			{
				tempob.l=i+1;
				tempob.r=j+1;
				pt->p->object.push_back(tempob);
				++(pt->p->ObCount);
			}
		}
	return pt;
}


QuadNode *AddNode(QuadNode *p,QuadBox box,QuadNode *parent)							//��ӽڵ�
{
	p=(QuadNode *)new(QuadNode);
	if(p!=NULL)
	{
		p->ObCount=0;
		p->box.maxl=box.maxl;
		p->box.maxr=box.maxr;
		p->box.minl=box.minl;
		p->box.minr=box.minr;
		p->children[0]=NULL;
		p->children[1]=NULL;
		p->children[2]=NULL;
		p->children[3]=NULL;
		p->parent=parent;
		return p;
	}
	else 
	{
		cout<<"�ռ�������"<<endl;
		system("PAUSE");
		return 0;
	}
}



void AddObject(ObInf splitpoint,QuadNode *p,ObInf ob)
{
	if(ob.l>splitpoint.l&&ob.r>splitpoint.r)
	{
		p->children[0]->object.push_back(ob);
		++p->children[0]->ObCount;
	}
	else  if(ob.l>splitpoint.l&&ob.r<=splitpoint.r)
	{
		p->children[1]->object.push_back(ob);
		++p->children[1]->ObCount;
	}
	else  if(ob.l<=splitpoint.l&&ob.r<=splitpoint.r)
	{
		p->children[2]->object.push_back(ob);
		++p->children[2]->ObCount;
	}
	else  if(ob.l<=splitpoint.l&&ob.r>splitpoint.r)
	{
		p->children[3]->object.push_back(ob);
		++p->children[3]->ObCount;
	}
	return;
}



void ViewTree(QuadNode *p,int n)													//��ʾ�����Ϣ
{
	QuadNode *vp;
	vp=p;

	if(vp->children[0]==NULL&&vp->children[1]==NULL&&vp->children[2]==NULL&&vp->children[3]==NULL)
		cout<<"["<<vp->box.minl<<","<<vp->box.maxl<<";"<<vp->box.minr<<","<<vp->box.maxr<<"]"<<"	"<<vp->ObCount<<"--"<<
		NoisyCount(RanNumber(n),vp->ObCount,GetNodeHight(p),CalculateTreeHight(100))<<endl;
	for(int i=0;i<4;++i)
		if(vp->children[i]!=NULL)
		{
			n++;
			ViewTree(vp->children[i],n);
			
		}
	
	return;
}




int GetNodeHight(QuadNode *p)												//��õ�ǰ�ڵ�߶�
{
	int h=0;
	while(p->parent!=NULL)
	{
		++h;
		p=p->parent;
	}
	return h;
}									



int &CalculateTreeHight(const int v)									//�������ĸ߶�
{
	int h=1;
	double t=(pow(2,1/3.0)-1)*v*v/pow(2,0.5);
	while(pow(2,2*h+1/3.0)-pow(2,5*h/3.0)<=t)
		++h;
	h--;
	return h;
}



vector<vector<int> > CreatDenMatrix(vector<vector<int> > AdjMatrix)		//�����ܶȾ���ĺ��� ����Ϊ�����ɵ��ڽӾ��� �������ɵ��ܶȾ���
{
	int l=AdjMatrix.size(),r=AdjMatrix[0].size();
	vector<vector<int> > DenMatrix(l,r);
	for(int i=0;i<l;++i)
	{
		for(int j=0;j<r;++j)
		{
			if(i==0&&j==0)
				DenMatrix[i][j]=AdjMatrix[i][j];
			else if(i==0&&j!=0)
				DenMatrix[i][j]=DenMatrix[i][j-1]+AdjMatrix[i][j];
			else if(i!=0&&j==0)
				DenMatrix[i][j]=DenMatrix[i-1][j]+AdjMatrix[i][j];
			else
				DenMatrix[i][j]=DenMatrix[i-1][j]+DenMatrix[i][j-1]-DenMatrix[i-1][j-1]+AdjMatrix[i][j];
		}
	}
	return DenMatrix;
}



ObInf &GetSplitPoint(vector<vector<int> > AdjMatrix,vector<vector<int> > DenMatrix,int minsize,int splittimes,int nh,int v)							//������ѵ㺯��������Ϊ��Ҫ������ѵ���ڽӾ���ͷ��ѵ���С�����С������Ϊ���Ӿ���ģ����ѵ�����
{
	//int h=splittimes;//���ĸ߶�
	
	
	
	int l=AdjMatrix.size(),r=AdjMatrix[0].size();
	SplitPointInf p;
	p.d=-1;
	p.coordinate.l=-1;
	p.coordinate.r=-1;

	//double *dis=new double[]; 
	vector<double> dis;
	//int k=0;//dis[]�Ĵ�С
	vector<int> larray;
	vector<int> rarray;




	for(int i=0;i<l;++i)
	{
		for(int j=0;j<r;++j)
		{
			if((i+1)*(j+1)>minsize&&(i+1)*(r-j-1)>minsize&&(l-i-1)*(j+1)>minsize&&(l-i-1)*(r-j-1)>minsize)
			{
				double d0=(DenMatrix[i][j]+0.0)/((i+1.0)*(j+1.0)),
					d1=(DenMatrix[i][r-1]-DenMatrix[i][j]+0.0)/((r-j-1.0)*(i+1.0)),
					d2=(DenMatrix[l-1][j]-DenMatrix[i][j]+0.0)/((j+1.0)*(l-i-1.0)),
					d3=(DenMatrix[l-1][r-1]-DenMatrix[l-1][j]-DenMatrix[i][r-1]+DenMatrix[i][j]+0.0)/((r-j-1.0)*(l-i-1.0));
				double d=max(d0,max(d1,max(d2,d3)))-min(d0,min(d1,min(d2,d3)));

				dis.push_back(d);
				larray.push_back(i+1);
				rarray.push_back(j+1);
				if(i>=(l/2)&&j>=(r/2)&&(l-i-1)*(r-j-2)==minsize)
				{
					int point=ExpCount(nh,splittimes,v,dis.size(),dis);
					p.d=dis[point];
					p.coordinate.l=larray[point];
					p.coordinate.r=rarray[point];
				}

				
			}
		}
	}

			
	return p.coordinate;
}	





void SplitQuadNode(QuadTree *pt,QuadNode *p,const int splittimes,vector<vector<int> > AdjMatrix)								//�����Ĳ�������
{
	int h=GetNodeHight(p);
	if(h<splittimes)
	{
		int v=AdjMatrix.size();
		int minsize=v*v/(int)pow(4.0,h+2);
		vector<vector<int> > newmatrix;
		vector<int> temp(p->box.maxr-p->box.minr+1);
		for(int i=p->box.minl-1;i<p->box.maxl;++i)
		{
			int t=0;
			for(int j=p->box.minr-1;j<p->box.maxr;++j)
			{
				temp[t]=AdjMatrix[i][j];
				++t;
			}
			newmatrix.push_back(temp);
		}
		vector<vector<int> > DenMatrix=CreatDenMatrix(newmatrix);
		ObInf point=GetSplitPoint(newmatrix,DenMatrix,minsize,splittimes,h,v);
		if(point.l==-1)
		{
			for(int i=0;i<4;++i)
				if(p->ObCount<0.8*v*v/pow(4.0,splittimes))
				{
					free(p);
					p->children[i]=NULL;
				}
				return;
		}
		ObInf npoint;
		npoint.l=point.l+p->box.minl-1;
		npoint.r=point.r+p->box.minr-1;
		InitQuadNode(npoint,p);
		for(int i=p->box.minl-1;i<p->box.maxl;++i)
			for(int j=p->box.minr-1;j<p->box.maxr;++j)
				if(AdjMatrix[i][j]==1)
				{
					ObInf ob;
					ob.l=i+1;
					ob.r=j+1;
					AddObject(npoint,p,ob);
				}
		for(int i=0;i<4;++i)
		{
			QuadNode *np;
			np=p->children[i];
			h=GetNodeHight(np);
			if(h>pt->depth)
				pt->depth=h;
			double d;
			QuadBox nbox;
			nbox.maxl=np->box.maxl-p->box.minl+1;
			nbox.minl=np->box.minl-p->box.minl+1;
			nbox.maxr=np->box.maxr-p->box.minr+1;
			nbox.minr=np->box.minr-p->box.minr+1;
			if(nbox.minl==1&&nbox.minr!=1)
				d=(DenMatrix[nbox.maxl-1][nbox.minr-1]-DenMatrix[nbox.maxl-1][nbox.minr-2])/((np->box.maxl-np->box.minl+1)*(np->box.maxr-np->box.minr+1.0));
			else if(nbox.minr==1&&nbox.minl!=1)
				d=(DenMatrix[nbox.maxl-1][nbox.minr-1]-DenMatrix[nbox.minl-2][nbox.maxr-1])/((np->box.maxl-np->box.minl+1)*(np->box.maxr-np->box.minr+1.0));
			else if(nbox.minr==1&&nbox.minl==1)
				d=DenMatrix[nbox.maxl-1][nbox.minr-1]/((np->box.maxl-np->box.minl+1)*(np->box.maxr-np->box.minr+1.0));
			else 
				d=(DenMatrix[nbox.maxl-1][nbox.minr-1]-DenMatrix[nbox.maxl-1][nbox.minr-2]-DenMatrix[nbox.minl-2][nbox.maxr-1]+DenMatrix[nbox.minl-2][nbox.maxr-2])/((np->box.maxl-np->box.minl+1)*(np->box.maxr-np->box.minr+1.0));
			if(d<=0.8&&np->ObCount>=0.8*v*v/pow(4.0,splittimes)&&h<splittimes)
				SplitQuadNode(pt,np,splittimes,AdjMatrix);
			else if(np->ObCount<0.8*v*v/pow(4.0,splittimes))
			{
				free(np);
				p->children[i]=NULL;
			}
		}
	}
	else 
	{
		for(int i=0;i<4;++i)
			p->children[i]=NULL;
	}
	return;
}




void InitQuadNode(ObInf splitpoint,QuadNode *p)
{
	QuadBox nbox;
	nbox.minl=p->box.minl;
	nbox.minr=p->box.minr;
	nbox.maxl=splitpoint.l;
	nbox.maxr=splitpoint.r;
	p->children[2]=AddNode(p->children[2],nbox,p);
	nbox.minl=p->box.minl;
	nbox.minr=splitpoint.r+1;
	nbox.maxl=splitpoint.l;
	nbox.maxr=p->box.maxr;
	p->children[3]=AddNode(p->children[3],nbox,p);
	nbox.minl=splitpoint.l+1;
	nbox.minr=p->box.minr;
	nbox.maxl=p->box.maxl;
	nbox.maxr=splitpoint.r;
	p->children[1]=AddNode(p->children[1],nbox,p);
	nbox.minl=splitpoint.l+1;
	nbox.minr=splitpoint.r+1;
	nbox.maxl=p->box.maxl;
	nbox.maxr=p->box.maxr;
	p->children[0]=AddNode(p->children[0],nbox,p);
	return;
}



int NoisyCount(//double epsilon,			//��˽Ԥ��**************************************������˹����**********************
			   double ranNum,				//�����
			   int ObCount,					//Ҷ�ӽڵ���1�ĸ���
			   int i,						//��ǰ���ĸ߶�
			   int h						//���ĸ߶�
			   )
{


	//double epsilon=0.5;
	double epsilon=1;

	double delta=1;	//ȫ�����ж�
	epsilon=pow(2,i/3.0)*(pow(2,1/3.0)-1)*epsilon/(pow(2,(h+1)/3.0)-1);

	double b = delta / epsilon;
	//�Ȳ���0��1֮��������������4λС��


	double lapNoise;//�ֱ��Ǹ�����������



	//�õ�����ֵ*************************************************************
	//������������������˹�ֲ�

	if(ranNum < 0.5)//������Ϊ��
		lapNoise = log(2 * ranNum) * b;
	else //������Ϊ��
		lapNoise = -log(2 * (1 - ranNum)) * b;

	//***********************************************************************
	cout<<"��ӵ���������"<<lapNoise<<endl;
	
	int NoisyCount=ObCount+(int)lapNoise;
	return NoisyCount;
}
double RanNumber(int n)															//���������
{

	double ranNum;//0��1֮����ȷֲ������������Ϊ������˹�ֲ�ֵ
	srand( (unsigned)time( NULL ) );//srand()��������һ���Ե�ǰʱ�俪ʼ��������� 


    //for(int k=0;k<50;k++)
	cout<<"n:"<<n<<endl;
	for(int k=0;k<n;k++)
		ranNum = rand()%1000;
	ranNum=ranNum / 1000.0;//0��1֮����ȷֲ��������

	cout<<"�������ֵ��"<<ranNum<<endl;
	return ranNum;

}




vector<double> BubbleSort(vector<double> p,int n)//ð������
{
	int i ,j;
	//bool ischanged;//�����������
	for(j=n;j>0;j--)
	{
		//ischanged =false;
		for(i=0;i<j-1;i++)
		{
			if(p[i]>p[i+1])//������ֽ���Ԫ�ؾ�����ƶ�
			{
				double temp=p[i];
				p[i]=p[i+1];
				p[i+1]=temp;
				//ischanged =true;
			}
		}
		//if(!ischanged)//��û���ƶ���˵�������Ѿ�����ֱ������
			//break;
	}
	return p;
}


//ָ������
int ExpCount(int i,//��ǰ���ĸ߶�
			 int h,//���ĸ߶�
			 int v,//�����С
			 int n,//���ѵ���������ѵ�����Ĵ�С
			 vector<double> dis//�洢���ѵ��Ӧ�ܶȲ�
			 )
{
	double epsilon=1;//��˽Ԥ��


	//���жȺ���
	double delta;
	delta=pow(4.0,i+1)/pow((double)v,2);

	double sum=0;//���Ŵ��ĸ�����ӣ�ʹ���ĸ��ʺ�Ϊ1

	vector<double> p;
	//vector<double> temp;
	//int k=0;//dis[]�Ĵ�С



	for(int k=0;k<n;k++)//�������ֵ�����ʺ�
	{
		p.push_back(exp(epsilon*delta/(2*h*delta)*dis[k]));
		sum+=p[k];
	}

	for(int k = 0; k < n; k++)//����ֲ�ֵ
	{
		p[k] /= sum;
		
	}
	vector<double> temp(p);
	//���������
	double ranNum=RanNumber(n+20);
	
	//������ֵ����
	//quick_sort(p,0,n-1);
	vector<double> p1(BubbleSort(p,n));
	int pm=0;

	for(int k = 1; k < n-1; k++)//����ֲ�ֵ
	{
		if(ranNum<p1[k-1])
		{
			//cout<<p[k]<<endl;
			//cout<<k+1<<endl;//a[]�ж�Ӧ���ѵ�����
			pm=k;
			break;
		}
		p1[k]+=p1[k-1];
	}
	for(int k = 0; k < n; k++)//����ֲ�ֵ
	{
		if(temp[k]==p1[pm])
		{
			pm=k;
			break;
		}

	}
	cout<<pm<<endl;
	return pm;
}