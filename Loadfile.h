#ifndef LOADFILE_H_
#define LOADFILE_H_
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

class Loadfile
{
private:
  vector<vector<double> > data;
public:
    ifstream fin;
    Loadfile(const char *file){fin.open(file);}
    vector<vector<double> > StrToDouble();
    vector<double> StrToDouble(const string str);
    vector<vector<double> > GetData(){return data;}
};

//transform the text file including datalist to 2-dimension vector
vector<vector<double> > Loadfile::StrToDouble()
{
    vector<vector<double> > v_data;
    vector<double> t_data;
    string line;
    int i=0,j;
    getline(fin,line);
    while(line.length()!=0)
    {
        t_data=StrToDouble(line);
        v_data.resize(i+1,vector<double>(t_data.size())); //allocate new space for new row;
        v_data[i]=t_data;
        getline(fin,line);
        i++;
    }
    data=v_data;
    return v_data;
}

//transform the string to double of vector
vector<double> Loadfile::StrToDouble(const string str)
{
    vector<double> dt;
    int i,first,last;
    bool flag;
    int n=str.length();
    first=last=0;
    for(i=1;i<n;i++)
    {
        flag=false;
        if(!flag)
        {
            if((str[i]==' '||str[i]=='\t')&&(str[i-1]==' '||str[i-1]== '\t'))  //both str[i]&&str[i-1] are <space> or <tab>?
            {
                first++;
                continue;
            }
            if((((str[i]==' ')||(str[i]=='\t'))&&((str[i-1]!=' ')||(str[i-1]!='\t')))||i==n-1)
            {
                last=i;
                flag=true;
            }
        }
        if(flag)
        {

            if(last!=n-1)
            {
                dt.push_back(atof(str.substr(first,last-first).c_str()));
                first=last+1;
                flag=false;
            }
            else
            {
                dt.push_back(atof(str.substr(first,last-first+1).c_str()));
                break;
            }
        }
    }
    return dt;
}
#endif
