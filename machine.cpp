#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <iostream>
using namespace std;
class main_memory
{
public:
    vector<pair<string,string>>base_programe;
    main_memory(vector<string>&insrtuction)
    {
        int b=insrtuction.size();
        int z=0;
        base_programe.resize(32);
        char arr[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                string s;
                s.push_back(arr[i]);
                s.push_back(arr[j]);
                if(z<=insrtuction.size()-1)
                    base_programe.push_back({s,insrtuction[z]});
                else
                {
                    base_programe.push_back({s,"00"});
                }z++;
            }
        }
            base_programe.erase(
            remove_if(base_programe.begin(), base_programe.end(),
                [](const pair<string, string>& element) { return element.first.empty(); }),
            base_programe.end());
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
    ALU()
    {
        char arr[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
        registr.resize(16);
        for(int i=0;i<16;i++)
        {
            registr[i].first.push_back('0');
            registr[i].first.push_back(arr[i]);
            registr[i].second="00";
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
class excution
{
    private:
        vector<pair<string ,string>>gistr;
        string inst;
        string counter;
        char op;
        vector<pair<string,string>>hidden_memo;
    public:
        excution(ALU&alu,main_memory&memo)
        {
            hidden_memo=memo.base_programe;
            gistr=alu.registr;
        }
        void run(int);
        void dis()
        {
            for(auto it:gistr){
                cout<<it.first<<" "<<it.second<<endl;
            }
        }
        
};
    void excution::run(int xx)
    {
        counter=hidden_memo[xx].first;
        inst=(hidden_memo[xx].second+hidden_memo[xx+1].second);
        op=inst[0];
        if(op=='1')
        {
            string s;
            string add;
            add.push_back(inst[2]);
            add.push_back(inst[3]);
            for (const auto& it : hidden_memo)//fecth
            {
                if(it.first==add)
                {
                    s=it.second;
                }
            }
            for(auto &i:gistr)
            {
                if(i.first[1]==inst[1])
                {
                    i.second=s;
                }
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
        file.push_back(s1);
        string s2;
        s2.push_back(line[2]);
        s2.push_back(line[3]);
        file.push_back(s2);
    }
    int choise;
    cout<<"ENTER \n1: load all programe and see output if exist"<<endl;
    cout<<"2: display Memory,rigster & counter in any steps"<<endl;
    cout<<"3: display memory after terminate"<<endl;
    cin>>choise; 
    if(choise==1)
    {
        main_memory mn(file);
        ALU al;
        excution ex(al,mn);
        ex.dis();
        ex.run(0);
        // for(int i=0;i<mn.base_programe.size();i++)
        // {
        //     ex.run(i);
        // }
        
    }
}