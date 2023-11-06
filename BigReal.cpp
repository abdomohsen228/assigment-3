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
        bool operator >(BigReal&bigreal);
        bool operator <(BigReal&bigreal);
        bool operator ==(BigReal&bigreal);
        ostream  operator <<(ostream& output);
friend ostream & operator <<(ostream &output ,BigReal &bigreal);
};
//---------------------------------- validation
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
            if(real_number.find('.')==1 && f==0)
            {
                fraction=real_number.substr(2,real_number.size()-1);
                integr=real_number[0];
            }
            else
            {
                if(f==0)integr=real_number.substr(0,real_number.find('.'));
                else{
                    integr=real_number.substr(f,real_number.find('.')-1);
                }
                fraction=real_number.substr(real_number.find('.')+1,real_number.size()-1);
            }
        }
        else
        {
            integr=real_number.substr(f,real_number.size());
        }
    }else
    {
        real_number="000";
    }
}
ostream & operator <<(ostream& output ,BigReal &bigreal)
{
    output<<bigreal.sign<<" "<<bigreal.integr<<" . "<<bigreal.fraction;
}
//------------------------------------------- operator '+' overloading
string BigReal::operator+(BigReal&bigreal)  // making both numbers the same size
{
    string int_s1=bigreal.integr;
    string int_s2=integr;
    int int_size1=bigreal.integr.size();
    int int_size2=integr.size();
    string frac1=bigreal.fraction;
    string frac2=fraction;
    int frac_siz1=bigreal.fraction.size();
    int frac_siz2=fraction.size();
     if(int_size1>int_size2)
        {
        int dif=int_size1-int_size2;
        string trans;  //garb ?
        for(int i=0;i<dif;i++)
        {
            trans+='0';
        }int_s2=trans+int_s2;    // adding the difference bits with '0'
        }
        else if(int_size1<int_size2)
        {
            int dif=int_size2-int_size1;
            string trans;  // garb ?
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
    if(sign==bigreal.sign)
    {
        string result_frac;
        int pls=0;
        int carry=0;
        for(int i=frac1.size()-1;i>=0;i--)
        {
            int digit1=frac1[i]-'0';  // converting characters into integers
            int digit2=frac2[i]-'0';
            int digit_res=digit1+digit2+carry;
            if(digit_res<10)   // checking if the addition of the 2 digits is bigger than 10 or not
            {
                carry=0;
                char mak_char=digit_res+'0';   // converting to character
                result_frac.push_back(mak_char);
            }else      // positions :  tens   ones
            {          // ex : 8 + 7 =   1     5
                digit_res-=10;   // taking the number in the ones position
                carry=1;    // taking the num in tens position
                char mak_char=digit_res+'0';
                result_frac.push_back(mak_char);
                if(i==0)     // if the number is right before the integer place  or the decimal point
                {
                    if(carry==1)
                    {
                        result_frac='0'+result_frac;  // converting into string
                        pls=1;  // putting the carry into plus to add it then to the real int
                    }
                }
            }
        }
        reverse(result_frac.begin(),result_frac.end());  // because of pushing the edited int every time the
        string result_int;                                        // string will be reversed so we re-reverse it again
        int carry2=0;
        for(int i=int_s1.size()-1;i>=0;i--)
        {
            int digit1=int_s1[i]-'0';
            int digit2=int_s2[i]-'0';
            int digit_res=digit1+digit2+carry2+pls;  //checking if the addition of the digits with the carry will exceed 10
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
                    result_int.push_back('1');  // if you exceeded the integer's size you will add 1 to the beginning
            }
            pls=0;
        }reverse(result_int.begin(),result_int.end());

        string final_res=sign+result_int+'.'+result_frac;
    //    cout<<"\nhere\n";
        return final_res;
    }
    else{    
    //    cout<<int_s1<<endl;
    //    cout<<frac1<<endl;

        string big_int="";
        string big_frac="";
        char big_sign;
        string little_frac="";
        string little_int="";
        int f = 0;
        for (int i = 0; i < int_size1; i++) {  // determining which is bigger
            if (int_s1[i] > int_s2[i]) {
                f = 1;
                big_int = int_s1;
                big_frac = frac1;
                big_sign=bigreal.sign;
                little_int = int_s2;
                little_frac = frac2;
                break;
            } else if (int_s1[i] < int_s2[i]) {
                f = 1;
                big_int = int_s2;
                big_frac = frac2;
                big_sign=sign;
                little_int = int_s1;
                little_frac = frac1;
                break;
            } else {
                continue;
            }
        }
        if (f == 0) {  // two integers are the same
            for (int i = 0; i < frac_siz1; i++) {
                if (frac1[i] > frac2[i]) {
                    f = 1;
                    big_int = int_s1;
                    big_frac = frac1;
                    big_sign=bigreal.sign;
                    little_int = int_s2;
                    little_frac = frac2;
                    break;
                } else if (frac1[i] < frac2[i]) {
                    f = 1;
                    big_int = int_s2;
                    big_frac = frac2;
                    big_sign=sign;
                    little_int = int_s1;
                    little_frac = frac1;
                    break;
                } else {
                    continue;
                }
            }
        }
        if (f == 0) {
            return "0";
        }
        int fff=0;
        string res_mins;
        for(int i=big_frac.size()-1;i>=0;i--)
        {
            int digit1=big_frac[i]-'0';
            int digit2=little_frac[i]-'0';
            if(digit1>=digit2)
            {
                int x=digit1-digit2;
                char chr=x+'0';
                res_mins.push_back(chr);
            }
            else
            {
                digit1+=10;
                big_frac[i-1]-=1;
                int x=digit1-digit2;
                char chr=x+'0';
                res_mins.push_back(chr);
                if(i==0)fff=1;
            }
        }
        reverse(res_mins.begin(),res_mins.end());
        string res2;
        for(int i=big_int.size()-1;i>=0;i--)
        {
            int digit1=(big_int[i]-'0')-fff;
            int digit2=little_int[i]-'0';
            fff=0;
            if(digit1>=digit2)
            {
                int x=digit1-digit2;
                char chr=x+'0';
                res2.push_back(chr);
            }
            else
            {
                digit1+=10;
                big_int[i-1]-=1;
                int x=digit1-digit2;
                char chr=x+'0';
                res2.push_back(chr);
            }
        }reverse(res2.begin(),res2.end());
        string fin=big_sign+res2+'.'+res_mins;
        return fin;
    }

 
};
//-------------------------------------------- operator '-' overloading
string BigReal::operator-(BigReal&bigreal) {
    string int_s2 = bigreal.integr;
    string int_s1 = integr;
    int int_size2 = bigreal.integr.size();
    int int_size1 = integr.size();
    string frac2 = bigreal.fraction;
    string frac1 = fraction;
    int frac_siz2 = bigreal.fraction.size();
    int frac_siz1 = fraction.size();
    if (int_size1 > int_size2) {
    int dif = int_size1 - int_size2;
    string trans;
    for (int i = 0; i < dif; i++) {
        trans += '0';
        }
        int_s2 = trans + int_s2;
        } else if (int_size1 < int_size2) {
        int dif = int_size2 - int_size1;
        string trans;
        for (int i = 0; i < dif; i++) {
            trans += '0';
        }
            int_s1 = trans + int_s1;
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
    if(sign!=bigreal.sign)// iverse operator to +
    {
        string result_frac;
        int pls=0;
        int carry=0;
        for(int i=frac1.size()-1;i>=0;i--)
        {
            int digit1=frac1[i]-'0';  // converting characters into integers
            int digit2=frac2[i]-'0';
            int digit_res=digit1+digit2+carry;
            if(digit_res<10)   // checking if the addition of the 2 digits is bigger than 10 or not
            {
                carry=0;
                char mak_char=digit_res+'0';   // converting to character
                result_frac.push_back(mak_char);
            }else      // positions :  tens   ones
            {          // ex : 8 + 7 =   1     5
                digit_res-=10;   // taking the number in the ones position
                carry=1;    // taking the num in tens position
                char mak_char=digit_res+'0';
                result_frac.push_back(mak_char);
                if(i==0)     // if the number is right before the integer place  or the decimal point
                {
                    if(carry==1)
                    {
                        result_frac='0'+result_frac;  // converting into string
                        pls=1;  // putting the carry into plus to add it then to the real int
                    }
                }
            }
        }
        reverse(result_frac.begin(),result_frac.end());  // because of pushing the edited int every time the
        string result_int;                                        // string will be reversed so we re-reverse it again
        int carry2=0;
        for(int i=int_s1.size()-1;i>=0;i--)
        {
            int digit1=int_s1[i]-'0';
            int digit2=int_s2[i]-'0';
            int digit_res=digit1+digit2+carry2+pls;  //checking if the addition of the digits with the carry will exceed 10
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
                    result_int.push_back('1');  // if you exceeded the integer's size you will add 1 to the beginning
            }
            pls=0;
        }reverse(result_int.begin(),result_int.end());

        string final_res=sign+result_int+'.'+result_frac;
    //    cout<<"\nhere\n";
        return final_res;

    }
    else
    {// -7- -10 =3 -10- -7=-3
        // cout<<int_s1<<endl;
        // cout<<int_s2<<endl;

        string big_int;
        string big_frac;
        char big_sign;
        string little_frac;
        string little_int;
        int f = 0;
        for (int i = 0; i < int_size1; i++) {  // determining which is bigger
            if (int_s1[i] > int_s2[i]) {
                f = 1;
                big_int = int_s1;
                big_frac = frac1;
                if(sign=='-')big_sign='-';
                else big_sign='+';
                little_int = int_s2;
                little_frac = frac2;
                break;
            } else if (int_s1[i] < int_s2[i]) {
                f = 1;
                big_int = int_s2;
                big_frac = frac2;
                if(sign=='-')big_sign='+';
                else big_sign='-';
                little_int = int_s1;
                little_frac = frac1;
                break;
            } else {
                continue;
            }
        }
        if (f == 0) {  // two integers are the same
            for (int i = 0; i < frac_siz1; i++) {
                if (frac1[i] > frac2[i]) {
                    f = 1;
                    big_int = int_s1;
                    big_frac = frac1;
                    big_sign='+';
                    little_int = int_s2;
                    little_frac = frac2;
                    break;
                } else if (frac1[i] < frac2[i]) {
                    f = 1;
                    big_int = int_s2;
                    big_frac = frac2;
                    big_sign='-';
                    little_int = int_s1;
                    little_frac = frac1;
                    break;
                } else {
                    continue;
                }
            }
        }
        if (f == 0) {
            return "0";
        }
        int fff=0;
        string res_mins;
        for(int i=big_frac.size()-1;i>=0;i--)
        {
            int digit1=big_frac[i]-'0';
            int digit2=little_frac[i]-'0';
            if(digit1>=digit2)
            {
                int x=digit1-digit2;
                char chr=x+'0';
                res_mins.push_back(chr);
            }
            else
            {
                digit1+=10;
                big_frac[i-1]-=1;
                int x=digit1-digit2;
                char chr=x+'0';
                res_mins.push_back(chr);
                if(i==0)fff=1;
            }
        }
        reverse(res_mins.begin(),res_mins.end());
        string res2;
        for(int i=big_int.size()-1;i>=0;i--)
        {
            int digit1=(big_int[i]-'0')-fff;
            int digit2=little_int[i]-'0';
            fff=0;
            if(digit1>=digit2)
            {
                int x=digit1-digit2;
                char chr=x+'0';
                res2.push_back(chr);
            }
            else
            {
                digit1+=10;
                big_int[i-1]-=1;
                int x=digit1-digit2;
                char chr=x+'0';
                res2.push_back(chr);
            }
            
        }reverse(res2.begin(),res2.end());
        string fin=big_sign+res2+'.'+res_mins;
        return fin;
    }
}
//------------------------------------- operator '>' overloading
bool BigReal::operator>(BigReal &bigreal)
{
        string int_s2 = bigreal.integr;  // the second object declared in int main
        string int_s1 = integr;  // first object declared in int main
        int int_size2 = bigreal.integr.size();
        int int_size1 = integr.size();
        string frac2 = bigreal.fraction;
        string frac1 = fraction;
        int frac_siz2 = bigreal.fraction.size();
        int frac_siz1 = fraction.size();
        if(bigreal.sign!=sign)
        {
            if(sign=='-')return false;
            return true;
        }

        if (int_size1 > int_size2)
        {
            int dif = int_size1 - int_size2;
            string trans;
            for (int i = 0; i < dif; i++)
            {
                trans += '0';
            }
            int_s2 = trans + int_s2;
        }
        else if (int_size1 < int_size2)
        {
            int dif = int_size2 - int_size1;
            string trans;
            for (int i = 0; i < dif; i++)
            {
                trans += '0';
            }
            int_s1 = trans + int_s1;
        }
        for (int i = 0; i < int_size1; i++)
        {  // determining which is bigger
            if (int_s1[i] > int_s2[i])
            {
                return true;
            }
            else if (int_s1[i] < int_s2[i])
            {
                return false;
            }
            else
            {
                continue;
            }
        }
         // two integers are the same
         for (int i = 0; i < frac_siz1; i++)
         {
            if (frac1[i] > frac2[i])
            {
                return true;
            }
            else if (frac1[i] < frac2[i])
            {
                return false;
            }
            else
            {
                continue;
            }
        }
        return false;
}
//-------------------------------------- operator '==' overloading
bool BigReal::operator==(BigReal &bigreal)
{
        string int_s2 = bigreal.integr;  // the second object declared in int main
        string int_s1 = integr;  // first object declared in int main
        int int_size2 = bigreal.integr.size();
        int int_size1 = integr.size();
        string frac2 = bigreal.fraction;
        string frac1 = fraction;
        int frac_siz2 = bigreal.fraction.size();
        int frac_siz1 = fraction.size();
        if(bigreal.sign!=sign)
        {
            return false;
        }

        if (int_size1 > int_size2)
        {
            int dif = int_size1 - int_size2;
            string trans;
            for (int i = 0; i < dif; i++)
            {
                trans += '0';
            }
            int_s2 = trans + int_s2;
        }
        else if (int_size1 < int_size2)
        {
            int dif = int_size2 - int_size1;
            string trans;
            for (int i = 0; i < dif; i++)
            {
                trans += '0';
            }
            int_s1 = trans + int_s1;
        }
        for (int i = 0; i < int_size1; i++)
        {  // determining if they are equal
            if (int_s1[i] == int_s2[i])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
         // two integers are the same
        for (int i = 0; i < frac_siz1; i++)
        {
            if (frac1[i] == frac2[i])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        return true;
}
//------------------------------------- operator '<' overloading
bool BigReal::operator<(BigReal &bigreal)
{
        string int_s2 = bigreal.integr;  // the second object declared in int main
        string int_s1 = integr;  // first object declared in int main
        int int_size2 = bigreal.integr.size();
        int int_size1 = integr.size();
        string frac2 = bigreal.fraction;
        string frac1 = fraction;
        int frac_siz2 = bigreal.fraction.size();
        int frac_siz1 = fraction.size();
        if(bigreal.sign!=sign)
        {
            if(sign=='-')return true;
            return false;
        }

        if (int_size1 > int_size2)
        {
            int dif = int_size1 - int_size2;
            string trans;
            for (int i = 0; i < dif; i++)
            {
                trans += '0';
            }
            int_s2 = trans + int_s2;
        }
        else if (int_size1 < int_size2)
        {
            int dif = int_size2 - int_size1;
            string trans;
            for (int i = 0; i < dif; i++)
            {
                trans += '0';
            }
            int_s1 = trans + int_s1;
        }
        for (int i = 0; i < int_size1; i++)
        {  // determining which is smaller
            if (int_s1[i] > int_s2[i])
            {
                return false;
            }
            else if (int_s1[i] < int_s2[i])
            {
                return true;
            }
            else
            {
                continue;
            }
        }
         // two integers are the same
         for (int i = 0; i < frac_siz1; i++)
         {
            if (frac1[i] > frac2[i])
            {
                return false;
            }
            else if (frac1[i] < frac2[i])
            {
                return true;
            }
            else
            {
                continue;
            }
        }
        return false;
}
int main()
{
    BigReal b("50");
    BigReal br("100"); 
    br.validation();
    b.validation();
    // cout<<br-b;//+17
    // cout<<endl;
    cout<<b-br;//-17
    // cout<<br<<endl;
    // cout<<b;
    return 0;
}