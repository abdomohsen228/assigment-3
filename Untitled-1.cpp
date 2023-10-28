#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#define ll long long
#define mx INT_MAX
#define mn INT_MIN
#define endl '\n'
//for(int i=0;i<n;i++)
#define mohsen cin.tie(0), cout.tie(0), cin.sync_with_stdio(0), cout.sync_with_stdio(0);
using namespace std;
struct domino
{
    int leftDots;
    int rightDots;
};
vector<domino>solve;
map<int,domino>vis;
int fn(domino& d,int size,vector<domino>&v)
{

    for(int i=0;i<size;i++)
    {
        if(d.rightDots==v[i].leftDots)
        {
            solve.push_back(v[i]);
            auto it =v.begin()+i;
            v.erase(it);
            fn(v[i+1],size,v);
        }
    }
    if(solve.size()==size)return 1;
    else
    {
        return 0;
    }
}
int main()
{
    int size;
    cin>>size;
    vector<domino>v(size);
    for(int i=0;i<size;i++)
    {
        cin>>v[i].leftDots;
        cin>>v[i].rightDots;
    }
    vector<domino>vpath(size);
    vpath=v;
    int f=0;
    for(int i=0;i<size;i++)
    {
        solve.push_back(v[i]);
        if(fn(v[i],v.size(),vpath)==1)
        {
            f=1;
            break;
        }
        else
        solve.clear();
    }
     if(f)
    {
        cout<<"true"<<endl;
        for(int i=0;i<size;i++)
        {
            cout<<solve[i].leftDots<<'|';
            cout<<solve[i].rightDots;
            if(i!=size-1)
            cout<<" - ";
        }
    }else
    {
        cout<<"false";
    }
}














/*int lCm(ll a,ll b){
    ll r1=a,r2=b;
    while(b!=0){
        ll a2=a;
        a=b;
        b=a2%b;
    }
    return r1/a*r2;

}*/
/*int gCd(int a,int b){
    while(b!=0){
        ll a2=a;
        a=b;
        b=a2%b;
    }
    return a;

}*/

/*number theory
mudlar arthmitc
ll add(ll a,ll b,ll m){
    return ((a%m)+(b%m))%m;
}
ll sub(ll a,ll b,ll m){
    return ((a%m)-(b%m)+m)%m;
}
ll mul(ll a,ll b,ll m){
    return ((a%m)*(b%m))%m;
}*/
//---------------------------------------
/* fast power log 
if n even (x^2)^n/2
odd x^n*x^n-1
 int x,n;
    cin>>x>>n;
    //xpowern
    int re=1;
    while(n>0){
        if(n%2) re=re*x;   //re=re*x%m   if n ll; 
        x=x*x;    //x=(x*x)%m if n ll
        if x is ll the (x*x)%m is error then arc low  ((x%m)*(x%m))%m;
        n=n/2; 
    }cout<<re;
    */

/*template<typename abdo>
abdo mymax(abdo a,abdo b){
    if(a>b){
        return a;
    }return b;
}
int main() {
  FAST;
  cout<<mymax(2,5)<<endl;  //work as int 
    cout<<mymax(2.5,5.4)<<endl;  //work as double
      cout<<mymax('a','b')<<endl;  //work as char
      //  cout<<mymax(2.5,5)<<endl;   error this is one type only!!!!!
  return 0;
}*/

/*fast   gcd
    ll int n,k;
    cin>>n>>k;
    vector<ll>v;
    v.push_back(n);
    for(ll i=1;i*i<=n;i++){
        if(n%i==0){
            v.push_back(i);
            if(i*i<n){
                v.push_back(n/i);
            }
        }
    }ll siz=v.size();
    //cout<<siz<<endl;
    sort(v.begin(),v.end());
    if(k<siz){
       cout<<v[k-1];
    }else{
        cout<<-1;
    }*/

// int n;
//  cin>>n;
//  int arr[n];int ans;
//  for (int i =0 ; i<n ;i++){
//      cin>>arr[i];
//  }for (int i=1; i<n ;i++){
//      arr[i]=arr[i]+arr[i-1];
//  }int q; cin>>q;
//  while (q--){
//      int l,r;
//      cin>>l>>r;
//      ans=arr[r];
//      if (l>0){
//          ans-=arr[l-1];
//      }cout<<ans<<endl;
//          }

// }
/*#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n=10,x;cin>>x;
    vector<int>v ={1,2,3,4,5,6,7,8,9};
    int l=0, r=n-1;
    while(l<=r){
        int mid=(l+r)/2;
        if (v[mid] ==x){
            cout<<"yes" ;return 0;
        }else if (v[mid]<x){
            l= mid+1;
        } else {
            r=mid-1;
        }
    }*/

/*void fac(int x){
    if(x==0){
        return ;
    }else{
        cout<<x%10<<endl;
        fac(x/10);
    }
}
int main()
{
    int x;0
    cin>>x;
    fac(x);

}*/

/*int fac(int x,int y){
    if(x==y){
        return x;
    }else{
        return y+fac(x,y-1);
    }

}
int main()
{
    int x,y;
    cin>>x>>y;
    cout<<fc(x,y)

}*/
/*int fac(int x){
    if(x==0|| x==1){;
        return x;
    }else{
        return x+fac(x-1);
    }

}int main()
{
    int c;
    cin>>c;
    cout<<fac(c);
}*/

/*int fac(int x){
    if(x==0 || x==1){
        return x;
    }else{
        return fac(x-1)+fac(x-2);
    }

}int main()
{
    int x;
    cin>>x;
    cout<<fac(x);

}*/
/*int fac(int x){
    if(x==0){
        return 1;
    }else{
        return x*fac(x-1);
    }
}int main()
{
    int x;
    cin>>x;
    cout<<fac(x);
}*/

/*void f(int n){
    if(n<1){//based case
        return;
    }else{
        cout<<"round: "<<n<<endl;//logic
        f(n-1);//call by it self (sub problem)
    }
}
int main(){
    int x;
    cin>>x;
    f(x);
}*/
