#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
vector<pair<int,vector<string>>>first_file;
vector<pair<int,vector<string>>>second_file;
vector<pair<int,string>>result;
vector<pair<int,string>>compare_char1;
vector<pair<int,string>>compare_char2;
vector<pair<int,string>>result2;
void compare_word()
{
    for(int i=0;i<first_file.size();i++)
    {
        int x=first_file[i].first;
        for(int j=0;j<first_file[i].second.size();j++)
        {
            if(first_file[i].second[j]!=second_file[i].second[j])
            {
                result.push_back({x,first_file[i].second[j]});
            }
        }
    }
}
void compare_char()
{
     for(int i=0;i<compare_char1.size();i++)
     {
        int x=compare_char1[i].first;
        for(int j=0;j<compare_char1[i].second.size();j++)
        {
            if(compare_char1[i].second[j]!=compare_char2[i].second[j])
            {
                result2.push_back({x,compare_char1[i].second});
                break;
            }
        }
     }
}
int main() {
    ifstream outputFile1; 
    ifstream outputFile2;
    outputFile1.open("file1.txt");
    outputFile2.open("file2.txt");
    if (outputFile1.is_open()) 
    {
        cout<<" enter (a) to compare by char or enter b to compare by word : ";
        char chose;
        cin>>chose;
        string lin1;
        string lin2;
        int linenumber1=0;
        int linenumber2=0;
        while(getline(outputFile1,lin1))
        {
            linenumber1++;
            string s;
            vector<string>v;
            compare_char1.push_back({linenumber1,lin1});
            for(int i=0;i<lin1.size();i++)
            {
                if(lin1[i]==' ')
                {
                    if( !s.empty())
                    {
                        v.push_back(s);
                        s.clear();
                    }
                }
                else if(i==lin1.size()-1)
                {
                    s+=lin1[i];
                    v.push_back(s);
                    s.clear();
                }
                else
                {
                    s+=lin1[i];
                }
            }first_file.push_back({linenumber1,v});
        }
        while(getline(outputFile2,lin2))
        {
            linenumber2++;
            string s;
            vector<string>v;
            compare_char2.push_back({linenumber2,lin2});
            for(int i=0;i<lin2.size();i++)
            {
                if(lin2[i]==' '  )
                {
                    if(!s.empty())
                    {
                        v.push_back(s);
                        s.clear();
                    }
                }
                else if(i==lin2.size()-1)
                {
                    s+=lin2[i];
                    v.push_back(s);
                    s.clear();
                }
                else
                {
                    s+=lin2[i];
                }
            }second_file.push_back({linenumber2,v});
        }
        outputFile1.close();
        outputFile2.close();
        if(chose=='b')
        {
            compare_word();
            if (result.size()==0)
            {
                cout<<"The result is identical"<<endl;
            }
            else
            {
                for(int i=0;i<result.size();i++)
                {
                    cout<<"the diffrent word is : "<<result[i].second<<" in the line : "<<result[i].first<<endl;
                }
            }
        }
        else if(chose=='a')
        {
            compare_char();
            if (result2.size()==0)
            {
                cout<<"The result is identical"<<endl;
            }
            else {
                for(int i=0;i<result2.size();i++)
                {
                    cout<<"the diffrent content is : "<<result2[i].second<<" in the line : "<<result2[i].first<<endl;
                }
            }


        }

    }
    else
    {
        cout << "Error: Unable to open the file." << endl;
    }

    return 0;
}
