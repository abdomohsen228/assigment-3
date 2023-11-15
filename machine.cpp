#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <iostream>
using namespace std;
//----------------------
string answ;
    string converter(string& hexInput)
    {
    string hexDigits = "0123456789ABCDEF";
    string binaryDigits[] = {
        "0000", "0001", "0010", "0011",
        "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011",
        "1100","1101","1110","1111"
    };
    string binary;
    string x;
    string y;
    for(int i=0;i<hexDigits.size();i++)
    {
        if(hexDigits[i]==hexInput[0])
        {
            x=binaryDigits[i];
        }
        if(hexDigits[i]==hexInput[1])
        {
            y=binaryDigits[i];
        }
    }
    binary=x+y;
    bool carry = true;
    for (char &bit : binary) {
        bit = (bit == '0') ? '1' : '0';
    }
    for (int i = binary.size() - 1; i >= 0 && carry!=0; --i) {
        if (binary[i] == '0') {
            binary[i] = '1';
            carry = false;
        } else {
            binary[i] = '0';
        }
    }    
    return binary;
    
}
bitset<8> adding(string c,string c2)
{
    bitset<8> num1(converter(c));
    bitset<8> num2(converter(c2));
    bitset<9> sum = num1.to_ulong() + num2.to_ulong();
    if (sum[8]) {
        sum = sum.to_ulong() & 0xFF;
    }
    bitset<8> ading = static_cast<bitset<8>>(sum.to_ulong());
    string s=ading.to_string();
    string x;
    string y;
    for(int i=0;i<4;i++)
    {
        x.push_back(s[i]);
    }
    for(int i=4;i<s.size();i++)
    {
        y.push_back(s[i]);
    }
    string hexDigits = "0123456789ABCDEF";
    string binaryDigits[] = {
        "0000", "0001", "0010", "0011",
        "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011",
        "1100","1101","1110","1111"
    };
    string binary;
    string hex;
    for(int i=0;i<=15;i++)
    {
        if(x==binaryDigits[i])
        {
            hex.push_back(hexDigits[i]);
        }
    }
    for(int i=0;i<=15;i++)
    {
        if(y==binaryDigits[i])
        {
            hex.push_back(hexDigits[i]);
        }
    }
    answ=hex;
}

//-----------------------
class main_memory
{
public:
    vector<pair<string,string>>base_programe;  // {(address , op ) , (address , address)}
    main_memory(vector<string>&insrtuction)
    {
        int b=insrtuction.size();
        int z=0;
        base_programe.resize(32);
        char arr[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; // creating address
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)  // 16 for HEXA limit
            {
                string s;
                s.push_back(arr[i]);
                s.push_back(arr[j]);
                if(z<=insrtuction.size()-1)
                    base_programe.push_back(make_pair(s,insrtuction[z]));  // 00 14  , 01 A3
                else
                {
                    base_programe.push_back({s,"00"});  // 03 00 ....... FF 00
                }
                z++;
            }
        }
        base_programe.erase(
                remove_if(base_programe.begin(), base_programe.end(),
                          [](const pair<string, string>& element) { return element.first.empty(); }),
                base_programe.end());  // deletes any element in vector that has an empty .first in its pair
    }
    void get_res();

};
void main_memory::get_res()
{

    for(auto it :base_programe)
    {
        cout<<it.first<<" "<<it.second<<endl;;
    }
}
class ALU
{
public:
    vector<pair<string ,string>>registr;
    vector<string>count;
    vector<pair<int,string>>move;
    ALU()
    {
        int o=0;
        move.resize(256);
        char arr[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
        registr.resize(16);  // assigning registers with an initial value of 00
        for(int i=0;i<16;i++)
        {
            registr[i].first.push_back('0');
            registr[i].first.push_back(arr[i]);
            registr[i].second="00";
            for (int j = 0; j < 16; ++j) 
            {
                move[o].second.push_back(arr[i]);
                move[o].second.push_back(arr[j]);
                move[o].first=o;
                o++;
            }
        }
    }
    void st_re()
    {
        for(int i=0;i<16;i++)
        {
            cout<<registr[i].first<<" "<<registr[i].second<<endl;
        }
    }
};
class excution :public ALU
{
private:
    vector<pair<string ,string>>gistr;
    string inst;
    string counter;
    char op;
    int xm;
    vector<pair<string,string>>hidden_memo;
public:
    excution(ALU&alu,main_memory&memo)
    {
        hidden_memo=memo.base_programe;  // -> {(address , op & register) , ( address , address)}
        gistr=alu.registr; // 00 00 , 01 00 ...... FF 00
    }
    void run(int&,int);
    void dis()  // displaying the register
    {
        cout<<"     *RIGISTER*       "<<endl;
        for(auto it:gistr){
            cout<<it.first<<" "<<it.second<<endl;
        }
        cout<<"     *MAIN MEMORY*      "<<endl;
        for(auto it:hidden_memo){
            cout<<it.first<<" "<<it.second<<endl;
        }
    }

};
void excution::run(int& xx, int b)
{
    xm=xx;
//    counter=hidden_memo[xx].first;
    inst=(hidden_memo[xx].second+hidden_memo[xx+1].second);  // the address
    op=inst[0];
    // for (auto &it:move)  // 
    // {
    //     if (it.second==hidden_memo[xx+1].second)   // counter , address
    //     {
    //         it.first=xx;
    //     }
    // }
    if(op=='1')  // load the given register with the value of the given address
    {
        string s;
        string add;
        add.push_back(inst[2]);
        add.push_back(inst[3]);
        for (const auto& it : hidden_memo)//fecth
        {
            if(it.first==add)
            {
                s=it.second;  // getting the value of the address
            }
        }
        for(auto &i:gistr)
        {
            if(i.first[1]==inst[1])  // loading the value of the chosen register
            {
                i.second=s;
            }
        }
    }
    else if (op=='2')  // load the given register with the address bit pattern
    {
        string add;
        add.push_back(inst[2]);
        add.push_back(inst[3]);
        for ( auto &it : gistr)
        {
            if (it.first[1]==inst[1])
            {
                it.second=add;
            }
        }
    }
    else if (op=='3')  // store the value of the given register in the given address
    {

        string add;
        add.push_back(inst[2]);
        add.push_back(inst[3]);
        string content;
        for (auto it :gistr)
        {
            if (it.first[1]==inst[1])
            {
                content=it.second;
            }
        }
        if (add=="00" && b==0)
        {
            cout<<"OUTPUT: "<< content<<"\n";
        }
        else
        {
            for (auto &it: hidden_memo) {
                if (it.first == add) {
                    it.second = content;
                }
            }
        }
    }
    else if (op=='4')  // copy the content of the first register in the second register
    {
        if (inst[1]!='0')
        {
            cout<<"The given instruction: "<<inst<<" is invalid!";
        }
        else
        {
            string content;
            string chosen;
            chosen.push_back(inst[2]);
            for (auto it :gistr)
            {
                if (it.first[1]==chosen[0])
                {
                    content=it.second;
                }
            }
            chosen.pop_back();
            chosen.push_back(inst[3]);
            for (auto &it: gistr)
            {
                if (it.first[1]==chosen[0])
                {
                    it.second=content;
                }
            }
        }
    }
    else if (op=='5')  // take to registers and add their values then store them in the given register
    {
        string fir,sec,ans,thrd;
        string c1,c2,c3,bin1,bin2;
        thrd.push_back(inst[1]);
        fir.push_back(inst[2]);
        sec.push_back(inst[3]);
        for (auto it : gistr)
        {
            if (it.first==fir)
            {
                c1=it.second;  // hex address
            }
            if (it.first==sec)
            {
                c2=it.second;  // hex address
            }
        }
        adding(c1,c2);
        for (auto &it :gistr)
        {
            if(it.first==thrd)
            {
                it.second=answ;
            }
        }
    }
    else if (op=='B')  // if the given register has the same value as in register zero you jump to the given address inst
    {
        string p;
        p.push_back(inst[1]);
        if (gistr[stoi(p)]==gistr[0])
        {
            string add;
            add.push_back(inst[2]);
            add.push_back(inst[3]);
//            counter=add;
            // expected endless loop!!
//            if (gistr[stoi(p)].second=="00" && gistr[0].second=="00")
//            {
//                if (add<)
//                cout<<"error! \nThis instruction: ";
//            }
            for (auto it : move)
            {
                // cout<<it.second<<"\n";
                if (it.second==add)
                {
                    xx= it.first;
                    // cout<<xx<<"\n";
                }
            }
            
        }
    }
    else if (op=='C')
    {
        if (inst[1]=='0' && inst[2]=='0' && inst[3]=='0')
        {
            // return 0;
            exit;
        }
        else
        {
            cout<< "the given instruction: "<<inst<<" is invalid!";
        }
    }
}

int main()
{
    ifstream insrtuction;
    insrtuction.open("instruction.txt");
    vector<string>file;
    string line;
    while (getline(insrtuction,line))
    {
        string s1;
        s1.push_back(line[0]);
        s1.push_back(line[1]);
        file.push_back(s1); // -> op , register  ( even idx )
        string s2;
        s2.push_back(line[2]);
        s2.push_back(line[3]);
        file.push_back(s2);  // -> address  ( odd idx )
    }
    int choise;
    cout<<"ENTER \n1:see output if exist"<<endl;
    cout<<"2: display Memory,Register & counter in any steps"<<endl;
    cout<<"3: display Memory & Register after terminate"<<endl;
    cin>>choise;
    if(choise==1)
    {
        main_memory mn(file);
        ALU al;
        excution ex(al,mn);
        for(int i=0;i<mn.base_programe.size();i++)
        {
            ex.run(i,0);
            if(i==mn.base_programe.size()-2)break;
        }
    }
    else if(choise==2)
    {
        cout<<"Enter the step number "<<endl;
        int stp;
        cin>>stp;
        main_memory mn(file);
        ALU al;
        excution ex(al,mn);
        int x=0;
        for(int i=0;i<mn.base_programe.size();i++)
        {
            ex.run(i,1);
            if(i==stp)
            {
                x=i;
                break;
            }
        }cout<<"      *COUNTER*      "<<ex.move[5].second<<endl;
        ex.dis();
        
    }
    else if(choise==3)
    {
        main_memory mn(file);
        ALU al;
        excution ex(al,mn);
        for(int i=0;i<mn.base_programe.size();i++)
        {
            ex.run(i,1);
            if(i==mn.base_programe.size()-2)break;
        }
        ex.dis();
    }
}
