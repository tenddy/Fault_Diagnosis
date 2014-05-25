#include <iostream>
#include <cmath>
#include "EMD.h"

using namespace std;
void print(vector<double> x);
int main()
{
    vector<double> A(4),B(4),C(4),X(4),D(4);
    A[0]=1;A[1]=1;A[2]=1;A[3]=1;
	B[0]=2;B[1]=2;B[2]=2;B[3]=2;
	C[0]=1;C[1]=1;C[2]=1;C[3]=1;
	D[0]=1;D[1]=1;D[2]=1;D[3]=1;
	EMD emd;
	X=emd.TDMA(A,B,C,D);
	print(X);
	#if 1
	vector<double> x(21),y(21),xx(201),yy(201),maxyy,minyy;
	x[0]=0;
	for(int i=0;i<21;i++)
	{
		if(i!=0)
			x[i]=x[i-1]+0.1;
		y[i]=std::sin(2*3.1415*x[i]+std::cos(2*3.1415*x[i]))+2;
	}
	//cout<<"y:"<<endl;
	//print(y);
	xx[0]=0;
	for(int i=1;i<201;i++)
		xx[i]=xx[i-1]+0.01;
	//cout<<"xx:"<<endl;
	//print(xx);
	yy = emd.spline(x,y,xx);
	//cout<<xx.size()<<endl;
	cout<<"yy:"<<yy.size()<<endl;
	print(yy);
	#endif
	//emd.findpeaks(xx,yy);
	#if 0
	for(int i=0;i<101;i++)
		realyy[i]=std::sin(2*3.1415*xx[i]);
	cout<<"realyy:"<<endl;
	print(realyy);
	#endif
	//cout<<emd.zero_polar(yy)<<endl;
	emd.calcimf(xx,yy);
	emd.Display();
    return 0;
}

void print(vector<double> x)
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

