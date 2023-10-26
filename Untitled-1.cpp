//problem 6 a One Binary Number
#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <iostream>
#define ll long long
#define endl '\n'
#define FAST cin.tie(0), cout.tie(0), cin.sync_with_stdio(0), cout.sync_with_stdio(0);
using namespace std;
int binaryprint(int n)
{
    if(n==0)
    {
        return 0;
    }
    return (n%2+10*binaryprint(n/2));

}

int main()
{
    int n;
    cin>>n;
    cout<<binaryprint(n);


}

