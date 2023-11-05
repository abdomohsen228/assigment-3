//problem 6 b Printing Many Numbers
#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <iostream>
#define ll long long
#define endl '\n'
#define FAST cin.tie(0), cout.tie(0), cin.sync_with_stdio(0), cout.sync_with_stdio(0);
using namespace std;
vector<string>result;
vector<string>poss;
void numbers(vector<int>&permut, vector<int>&elemnts,vector<bool>&visit,string prefix,int k)
{
    int t=0;
    string permut2;//countanier for convert int to char
    if(permut.size()==k)
    {
        for(auto i:permut)permut2+=char(i+'0');//convert int to char
        auto it=find(poss.begin(),poss.end(),permut2);//check all permution 
        if(it!=poss.end())
        {
            t=0;//permution is exist 
        }else
        {
            t=1;
            poss.push_back(permut2); //isnot exist 
        }
        if(t)
        {
            string res=prefix+permut2;
            result.push_back(res);
        }
    }
    else
    {
        for(int i=0;i<elemnts.size();i++)
        {
            if(visit[i]==true)
            {
                continue;
            }
            visit[i]==true;
            permut.push_back(elemnts[i]);
            numbers(permut,elemnts,visit,prefix,k);//recall 
            permut.pop_back(); //backtracing part
            visit[i]=false; //backtracing part
        }
    }
}
int main()
{
    string pre;
    int x;
    cin>>pre>>x;
    vector<bool>check(x,false);//if take the number before or not
    vector<int>elemnts;
    for(int i=0;i<x;i++){//making zeros and ones vector
    if(i%2)elemnts.push_back(0);
    else elemnts.push_back(1);
    }
    vector<int>permut;
    numbers(permut,elemnts,check,pre,x);
    for(int i=0;i<result.size();i++)//output
    {
        cout<<result[i]<<endl;
    }
}