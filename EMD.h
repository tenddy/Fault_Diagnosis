#ifndef _EMD_H
#define _EMD_H

#include <vector>
using std::vector;
class EMD
{
private:
	vector<vector<double> > imf; //save imf
	vector<double> r;
	//class points;

	struct LocalMax{
		vector<double> x;
		vector<double> y;
	}localmax;

	struct LocalMin{
		vector<double> x;
		vector<double> y;
	}localmin;

public:
	EMD();
	~EMD();

	vector<double> findmaxpeaks(const vector<double> &y);
	vector<double> findminpeaks(const vector<double> &y);
	void findpeaks(const vector<double> &x,const vector<double> &y);
	vector<double> spline(const vector<double> &x,const vector<double> &y , const vector<double> &xx);
	vector<double> TDMA(vector<double> &A,vector<double> &B,vector<double> &C,vector<double> &D);
	vector<double> calcmeans(vector<double> &lmax, vector<double> &lmin);
	double CalcStdDeviation(const vector<double> &yy);
	int zero_polar(const vector<double> &yy);
	bool imf_stop(const vector<double> &yy);
	bool emd_stop(const vector<double> &yy);
	vector<double> subvector(const vector<double> &x1,const vector<double> &x2);
	void calcimf(const vector<double> &x, const vector<double> &y);
	void print(vector<double> x);
	void Display();
};


#endif
