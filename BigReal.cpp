#include "iostream"
#include "bits//stdc++.h"
#include "string"
using namespace std;
class BigReal
{
    private:
        char sign='+';
        string real_number;
        string integr="0",fraction="0";
    public:
        BigReal(string real)
        {
            real_number=real;
        }
        void validation();
        string operator +(BigReal&bigreal);
        string operator-(BigReal&bigreal);
        ostream  operator <<(ostream& output);        

friend ostream & operator <<(ostream &output ,BigReal &bireal);
};
void BigReal::validation()
{
    if(regex_match(real_number,regex("[+-]?\\d*.?\\d+")))
    {
        int f=0;
        if(real_number[0]=='-')
        {
            sign='-';
            f=1;
            real_number[0]=0;
        }
        else if(real_number[0]=='+')
        {
            f=1;
            real_number[0]=0;
        }
        if(real_number.find('.')<real_number.size())
        {
            if(real_number.find('.')==1)
            {
                fraction=real_number.substr(2,real_number.size()-1);
            }
            else
            {
                real_number.find('.');
                if(f==0)integr=real_number.substr(f,real_number.find('.'));
                else{
                    integr=real_number.substr(f,real_number.find('.')-1);
                }
                fraction=real_number.substr(real_number.find('.')+1,real_number.size()-1);
            }
        }
        else
        {
            integr=real_number.substr(1,real_number.size()-1);
        }
    }else
    {
        real_number="000";
    }
}

ostream & operator <<(ostream& output ,BigReal &bireal)
{
    output<<bireal.sign<<" "<<bireal.integr<<" . "<<bireal.fraction;
}

string BigReal::operator+(BigReal&bigreal)
{
    string int_s1=bigreal.integr;
    string int_s2=integr;
    int int_size1=bigreal.integr.size();
    int int_size2=integr.size();
    string frac1=bigreal.fraction;
    string frac2=fraction;
    int frac_siz1=bigreal.fraction.size();
    int frac_siz2=fraction.size();
    if(sign==bigreal.sign)
    {
    if(int_size1>int_size2)
    {
        int dif=int_size1-int_size2;
        string trans;
        for(int i=0;i<dif;i++)
        {
            trans+='0';
        }int_s2=trans+int_s2;
    }
    else if(int_size1<int_size2)
    {
        int dif=int_size2-int_size1;
        string trans;
        for(int i=0;i<dif;i++)
        {
            trans+='0';
        }int_s1=trans+int_s1;
    }
    if(frac_siz1>frac_siz2)
    {
        int dif=frac_siz1-frac_siz2;
        string trans;
        for(int i=0;i<dif;i++)
        {
            trans+='0';
        }frac2=frac2+trans;
    }
    else if(frac_siz1<frac_siz2)
    {
        int dif=frac_siz2-frac_siz1;
        string trans;
        for(int i=0;i<dif;i++)
        {
            trans+='0';
        }frac1=frac1+trans;
    }
    string result_frac;
    int pls=0;
    int carry=0;
    for(int i=frac1.size()-1;i>=0;i--)
    {
        int digit1=frac1[i]-'0';
        int digit2=frac2[i]-'0';
        int digit_res=digit1+digit2+carry;
        if(digit_res<10)
        {
            carry=0;
            char mak_char=digit_res+'0';
            result_frac.push_back(mak_char);
        }else
        {
            digit_res-=10;
            carry=1;
            char mak_char=digit_res+'0';
            result_frac.push_back(mak_char);
            if(i==0)
            {
                if(carry==1)
                {
                    result_frac='0'+result_frac;
                    pls=1;
                }
            }
        }
    }reverse(result_frac.begin(),result_frac.end());
    string result_int;
    int carry2=0;
    for(int i=int_s1.size()-1;i>=0;i--)
    {
        int digit1=int_s1[i]-'0';
        int digit2=int_s2[i]-'0';
        int digit_res=digit1+digit2+carry2+pls;
        if(digit_res<10)
        {
            carry2=0;
            char mak_char=digit_res+'0';
            result_int.push_back(mak_char);
        }else
        {
            digit_res-=10;
            carry2=1;
            char mak_char=digit_res+'0';
            result_int.push_back(mak_char);
        }    
        if(i==0)
        {
            if(carry2==1)
                result_int.push_back('1');
        }
        pls=0;
    }reverse(result_int.begin(),result_int.end());
    
    string final_res=sign+result_int+'.'+result_frac;
        return final_res;
    }
    else
    {


    }
}
string BigReal::operator-(BigReal&bigreal)
{
    string int_s1=bigreal.integr;
    string int_s2=integr;
    int int_size1=bigreal.integr.size();
    int int_size2=integr.size();
    string frac1=bigreal.fraction;
    string frac2=fraction;
    int frac_siz1=bigreal.fraction.size();
    int frac_siz2=fraction.size();
    string big_int;
    string big_frac;
    string little_frac;
    string little_int;
    string finl_res;
    int f=0;
    if(int_size1>int_size2)
    {
        int dif=int_size1-int_size2;
        string trans;
        for(int i=0;i<dif;i++)
        {
            trans+='0';
        }int_s2=trans+int_s2;
    }
    else if(int_size1<int_size2)
    {
        int dif=int_size2-int_size1;
        string trans;
        for(int i=0;i<dif;i++)
        {
            trans+='0';
        }int_s1=trans+int_s1;
    }
    for(int i=0;i<int_size1;i++)
    {
        if(int_s1[i]>int_s2[i])
        {
            f=1;
            big_int=int_s1;
            big_frac=frac1;
            little_int=int_s2;
            little_frac=frac2;
            break;
        }else if(int_s1[i]<int_s2[i])
        {
            f=1;
            big_int=int_s2;
            big_frac=frac2;
            little_int=int_s1;
            little_frac=frac1;
            break;
        }else
        {
            continue;
        }   
    }
    if(f==0)
    {
        for(int i=0;i<frac_siz1;i++)
        {
            if(frac1[i]>frac2[i])
            {
                f=1;
                big_int=int_s1;
                big_frac=frac1;
                little_int=int_s2;
                little_frac=frac2;
                break;
            }else if(frac1[i]<frac2[i])
            {
                f=1;
                big_int=int_s2;
                big_frac=frac2;
                little_int=int_s1;
                little_frac=frac1;
                break;
            }else
            {
                continue;
            }
        }
    }
    if(f==0)
    {
        finl_res="0";
        return finl_res;
    }
    




}

int main()
{
    BigReal br("-554565.1234");
    BigReal b("-586.90156");
    b.validation();
    br.validation();


    return 0;
}