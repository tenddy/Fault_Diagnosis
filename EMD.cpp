#include "EMD.h"
#include <iostream>
#include <cmath>
using namespace std;

EMD::EMD()
{
}
EMD::~EMD()
{
}

//find max peaks
vector<double> EMD::findmaxpeaks(const vector<double> &y)
{
	vector<double> peak;
	for(int i=1;i<y.size()-1;i++)
	{
		if(y[i]>=y[i-1] && y[i]>y[i+1])
		{
			peak.push_back(y[i]);
		}
	}
	return peak;
}
//find min peaks
vector<double> EMD::findminpeaks(const vector<double> &y)
{
	vector<double> peak;
	for(int i=1;i<y.size()-1;i++)
	{
		if(y[i]>=y[i-1] && y[i]>y[i+1])
		{
			peak.push_back(y[i]);
		}
	}
	return peak;
}

/**三次样条拟合是查找极点，首尾节点均当做极点
**/
void EMD::findpeaks(const vector<double> &x,const vector<double> &y)
{
	if(x.size() != y.size())
			cout<<"error:the dimension isn't equal!\n";
	else if(x.size() < 3 )
		cout<<"error:the points are less than 3.\n";

	localmax.x.push_back(x[0]);
	localmax.y.push_back(y[0]);
	localmin.x.push_back(x[0]);
	localmin.y.push_back(y[0]);
	unsigned int n=x.size();
	for(unsigned int i=1;i<n-2;i++)
	{
		if(y[i]>=y[i-1] && y[i]>y[i+1])
		{
			localmax.x.push_back(x[i]);
			localmax.y.push_back(y[i]);
		}
		if(y[i] <= y[i-1] && y[i] < y[i+1])
		{
			localmin.x.push_back(x[i]);
			localmin.y.push_back(y[i]);
		}
	}
	localmax.x.push_back(x[n-1]);
	localmax.y.push_back(y[n-1]);
	localmin.x.push_back(x[n-1]);
	localmin.y.push_back(y[n-1]);
}
/**
 **	x:x of peak points
 ** y:y of peak points
 ** xx:x of origin points
 ** return y of origin points
 **/
vector<double> EMD::spline(const vector<double> &x, const vector<double> &y ,const vector<double> &xx)
{
	cout<<"spline..."<<endl;
	vector<double> A,B,C,D,H;
	unsigned int n = x.size();
	unsigned int i,j;
	vector<double> yy(xx.size());
	vector<double> E(n-2);
	vector<double> ai(n-1),bi(n-1),ci(n-1),di(n-1),mi(n);
	for(i=0;i<n-1;i++)
		H.push_back(x[i+1]-x[i]);

	for(i =0 ;i<n-2;i++)
	{
		A.push_back(H[i]);
		B.push_back(2*(H[i]+H[i+1]));
		C.push_back(H[i+1]);
		D.push_back(6*((y[i+2]-y[i+1])/H[i+1]-(y[i+1]-y[i])/H[i]));
	}

	E=TDMA(A,B,C,D);
	mi[0] = 0;
	mi[n-1] = 0;
	for(i=1;i<n-1;i++)
		mi[i] = E[i-1];
	for(i=0;i<n-1;i++)
	{
		ai[i] = y[i];
		bi[i] = (y[i+1]-y[i])/H[i]-mi[i]*H[i]/2-H[i]*(mi[i+1]-mi[i])/6;
		ci[i] = mi[i]/2;
		di[i] = (mi[i+1]-mi[i])/(6.0*H[i]);
	}
	i=0;
	j=0;
	while(i<n-1&&j<xx.size())
	{
		if(x[i]-xx[j]<=1e-5 && xx[j]-x[i+1]<=1e-5)
		{
			double detax=xx[j]-x[i];
			double detax2=detax*detax;
			yy[j] = ai[i]+bi[i]*detax+ci[i]*detax2+di[i]*detax*detax2;
			j++;
		}
		else
		{
			i++;
		}
	}
	return yy;
}
/** 求解三对角矩阵
 [B0 C0 0  0  ...   0    0
 [A1 B1 C1 0  ...   0    0
 [	 A2 B2 C2 0 ... 0    0
 [	...            Bn-2  Cn-2
 [0  0  0  0 ...   An-1  Bn-1
 ** 返回拟合曲线的系数ci的中间n-3个值
**/
vector<double> EMD::TDMA(vector<double> &A,vector<double> &B,vector<double> &C,vector<double> &D)
{
	unsigned int n = A.size();
	vector<double> X(n);
	double temp;	;
	C[0] = C[0]/B[0];
	D[0] = D[0]/B[0];
	for(unsigned int i=1;i<n;i++)
	{
		temp = B[i] - A[i] * C[i-1];
		C[i] = C[i]/temp;
		D[i] = (D[i]-A[i]*D[i-1])/temp;
	}
	X[n-1] = D[n-1];
	//逆向求解X
	for(int i=n-2;i >= 0; i--)
		X[i] = D[i] - C[i] * X[i+1];

	return X;
}

vector<double> EMD::calcmeans(vector<double> &lmax, vector<double> &lmin)
{
	int n=lmax.size();
	vector<double> means(n);
	for(int i=0;i<n;i++)
		means[i]=(lmax[i]+lmin[i])/2.0;
	return means;
}

double EMD::CalcStdDeviation(const vector<double> &yy)
{
	double mean,sum=0;
	int i,n=yy.size();
	for(i=0;i<n;i++)
		sum+=yy[i];
	mean = sum/n;
	sum=0;
	for(i=0;i<n;i++)
		sum+=(yy[i]-mean)*(yy[i]-mean);
	return std::sqrt(sum/n);
}

int EMD::zero_polar(const vector<double> &yy)
{
	int zero=0, polar=0;
	int n=yy.size();
	for(int i=1;i<n;i++)
	{
		if(i<n-1 && ((yy[i]>=yy[i-1]&&yy[i]>=yy[i+1])||(yy[i]<=yy[i-1]&&yy[i]<=yy[i+1])))
		{
			polar++;
		}
		if(yy[i]!=0&&yy[i-1]*yy[i]<=0)
		{
			zero++;
		}
	}
	if(yy[n-1]==0)
		zero++;
	return std::abs(polar-zero);
}

bool EMD::imf_stop(const vector<double> &y)
{
	//cout<<"zero_polar:"<<zero_polar(y)<<endl;
	//cout<<"deviation:"<<CalcStdDeviation(y)<<endl;
	if(zero_polar(y)<=1 || CalcStdDeviation(y)<0.3)
		return false;           //不满足条件
	else
		return true;				//满足条件
}

bool EMD::emd_stop(const vector<double> &y)
{
	int u=findmaxpeaks(y).size()*findminpeaks(y).size();
	if(u>0)
		return false;  //y 不是单调
	else
		return true; //y单调 分解结束
}

vector<double> EMD::subvector(const vector<double> &x1,const vector<double> &x2)
{
	vector<double> sub;
	if(x1.size() == x2.size())
		for(int i=0;i<x1.size();i++)
			sub.push_back(x1[i]-x2[i]);
	return sub;
}

#if 1
void EMD::calcimf(const vector<double> &x, const vector<double> &y)
{
	unsigned int n=y.size();
	vector<double> left=y;
	vector<double> imfyy(n),mean(n),maxyy,minyy;

	while(!emd_stop(left))
	{
		imfyy = left;
		while(imf_stop(imfyy))
		{
			findpeaks(x,imfyy);
			minyy=spline(localmin.x,localmin.y,x);
			maxyy = spline(localmax.x,localmax.y,x);
			mean=calcmeans(maxyy,minyy);
			imfyy= subvector(imfyy,mean);
		}
		imf.resize(imf.size()+1,vector<double> (n));
		imf[imf.size()-1]=imfyy;
		left = subvector(left,imfyy);
	}
	r=left;
	//cout<<"r:"<<endl;
	//print(r);
}
#endif

void EMD::print(vector<double> x)
{
	cout.setf(ios_base::showpoint);
	cout.precision(4);
	for(unsigned int i=0;i<x.size();i++)
	{
		cout.width(10);
		cout<<x[i];
	}
	cout<<endl;
}
void EMD::Display()
{
	cout<<"r:"<<endl;
	print(r);

	cout<<"imf:"<<imf.size()<<endl;
	for(int i=0;i<imf.size();i++)
	{
		cout<<"imf"<<i<<":\n";
		for(int j=0;j<imf[0].size();j++)
		{
			cout.width(10);
			cout<<imf[i][j];
		}
		cout<<endl;
	}
}
