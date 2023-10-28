#include <iostream>
#include <vector>
#include <map>
using namespace std;
struct domino
{
    int leftDots;
    int rightDots;
};
vector<domino> solve;
map<int, domino> vis;
bool fn(domino d, int size, vector<domino> v)
{
    if (size == 0) //base case
    {
        return true;
    }
    for (int i = 0; i < size; i++)
    {
        if (d.rightDots == v[i].leftDots)//compare every card
        {
            solve.push_back(v[i]);//add it
            vector<domino> temp = v;
            temp.erase(temp.begin() + i);// erase this elemnt to safe it for dublicate
            if (fn(solve.back(), size - 1, temp))// back tracing part
            {
                return true;
            }
            else
            {
                solve.pop_back();// erase this elemnt it didnot match for this tree
            }
        }
    }
    return false; //no sultions
}
int main()
{
    int size;
    cin >> size;
    vector<domino> v(size);
    for (int i = 0; i < size; i++)//acess  domoino card
    {
        cin >> v[i].leftDots;
        cin >> v[i].rightDots;
    }
    int f = 0;
    for (int i = 0; i < size; i++)
    {
        solve.push_back(v[i]); // push first card to solve
        vector<domino> temp = v; // testing vector
        temp.erase(temp.begin() + i); // erase first elemnt to safe it for dublicate
        if (fn(solve.back(), size - 1, temp))//true or fale
        {
            f = 1;
            break;
        }
        else
        {
            solve.clear();
        }
    }

    if (f)
    {
        cout << "true" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << solve[i].leftDots << '|';
            cout << solve[i].rightDots;
            if (i != size - 1)
                cout << " - ";
        }
    }
    else
    {
        cout << "false";
    }
    return 0;
}
