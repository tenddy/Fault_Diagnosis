#ifndef APEN_H_
#define APEN_H_
#include<iostream>
#include<stack>
#include<vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
class ApEn
{
private:
    int m;//dimention
    float r;//
    int N; //data number
    //vector <vector<double> > subx;
public:
    ApEn(int m_m,float m_r,int m_N):m(m_m),r(m_r),N(m_N>5000?5000:m_N) {}
    vector<double> get_mv(const vector<double> x,int i,int j);
    vector <vector<double> > get_subx(const vector<double> x,int dm);
    double max_distance(const vector<double> xi,const vector<double> yj);
    vector<vector<double> > distance(const vector<vector<double> > sx);
    double  calc_fim(const vector<double> x,int dm);
    double calc_apen(const vector<double> x,int dm);
    void Display();
};

#if 1
vector<double> ApEn::get_mv(const vector<double> x,int i,int j)
{
    vector<double> rx;
    int k;
    int len=x.size();
    rx.clear();
    if(i>j||j>len)
    {
        cout<<"error"<<endl;
        return rx;
    }
    for(k=i;k<=j;k++)
        rx.push_back(x[k-1]);
    return rx;
}
#endif
#if 0
vector<double> ApEn::get_mv(const vector<double> x,int i,int m)
{
    vector<double> rx;
    int k;
    for(k=i;k<i+m;k++)
        rx.push_back(x[k-1]);
}
#endif

vector <vector<double> > ApEn::get_subx(const vector<double> x,int dm)
{
    vector<vector<double> > sx;
    sx.resize(N-dm+1,vector<double>(dm));
    int i,j;
    for(i=0;i<N-dm+1;i++)
        sx[i]=get_mv(x,i+1,i+dm);
        //for(j=0;j<m;j++)
        //{
        //  sx[i][j]=x[i+j];
        //}
   // subx=sx;
    return sx;
}

double ApEn::max_distance(const vector<double> xi,const vector<double> yj)
{
    double maxdis;
    int k;
    if(xi.size()!=yj.size())
    {
        cout<<"dimention is error!"<<endl;
        return -1;
    }

    maxdis=fabs(xi[0]-yj[0]);
    for(k=1;k<xi.size();k++)
        if(fabs(xi[k]-yj[k])>maxdis)
            maxdis=fabs(xi[k]-yj[k]);
    return maxdis;
}
vector<vector<double> > ApEn::distance(const vector<vector<double> > sx)
{
    vector<vector<double> > dis(sx.size(),vector<double>(sx.size()));
    int i,j;
    for(i=0;i<sx.size();i++)
    {
        for(j=0;j<sx.size();j++)
        {
            if(i==j)
                dis[i][j]=0.0;
            dis[i][j]=max_distance(sx[i],sx[j]);
        }
    }
    return dis;
}

double ApEn::calc_fim(const vector<double> x,int dm)
{
    vector<vector<double> > dis;
    vector<vector<double> > sx(N-dm+1,vector<double> (dm));
    vector<int> num(N-dm+1);
    vector<double> cim(N-dm+1);
    double sum=0;
    int i,j;
    sx=get_subx(x,dm);
    dis.resize(sx.size(),vector<double>(sx.size()));
    dis=distance(sx);

    for(i=0;i<dis.size();i++)
    {
        for(j=0;j<dis.size();j++)
            cout<<dis[i][j]<<"\t";
        cout<<endl;
    }

    cout<<endl;
    for(i=0;i<dis.size();i++)
    {
        for(j=0;j<dis.size();j++)
            if(dis[i][j]<r)
                num[i]++;
        cim[i]=double(num[i])/(N-dm+1);
    }
    for(i=0;i<dis.size();i++)
        sum+=log(cim[i]);
    return sum/(N-dm+1);
}

//calculate approximate entropy
double ApEn::calc_apen(const vector<double> x,int dm)
{
    return (calc_fim(x,dm)-calc_fim(x,dm+1));
}

void ApEn::Display()
{
    #if 0
    int i,j;
    for(i=0;i<subx.size();i++)
    {
        for(j=0;j<subx[0].size();j++)
        cout<<subx[i][j]<<"\t";
        cout<<endl;
    }
    cout<<endl;
    #endif
}

//计算min到max之间的随机数
vector<double> get_rand(int N,double min,double max)
{
    vector<double> x;
    x.clear();
    int i;
    srand(time(NULL));
    for(i=0;i<N;i++)
    {
        x.push_back(min+(rand()%9)/9.0*(max-min));
    }
    return x;
}

//计算x的均值
double means(vector<double> x)
{
    int i,l=x.size();
    double sum;
    for(i=0;i<l;i++)
        sum+=x[i];
    return sum/l;
}
#endif
