#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

void pintAnts(set<int>& leftAnts, set<int>& rightAnts, map<int, int>& ants){
    while(!leftAnts.empty() && !rightAnts.empty()){
        if(*leftAnts.begin() == *rightAnts.begin()){
            if(ants.begin()->second <= ants.rbegin()->second){
                cout << ants.begin()->second << " ";
                ants.erase(ants.begin());
                leftAnts.erase(leftAnts.begin());
            }
            else{
                cout << ants.rbegin()->second << " ";
                ants.erase(--ants.end());
                rightAnts.erase(rightAnts.begin());
            }
        }
        else if(*leftAnts.begin() < *rightAnts.begin()){
            cout << ants.begin()->second << " ";
            leftAnts.erase(leftAnts.begin());
            ants.erase(ants.begin());
        }
        else {
            cout << ants.rbegin()->second << " ";
            rightAnts.erase(rightAnts.begin());
            ants.erase(--ants.end());
        }
    }

    while(!leftAnts.empty()){
        cout << ants.begin()->second ++ << " ";
            leftAnts.erase(leftAnts.begin());
            ants.erase(ants.begin());
    }

    while(!rightAnts.empty()){
        cout << ants.rbegin()->second << " ";
        rightAnts.erase(rightAnts.begin());
        ants.erase(--ants.end());
    }
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n, l;
        cin >> n >> l;

        set<int> leftAnts, rightAnts;
        map<int, int> ants;
        for(int j = 0;j < n; j ++){
            int p, d;
            cin >> p >> d;
            if(d == 0){
                leftAnts.insert(p);
            }
            else {
                rightAnts.insert(l - p);
            }
            ants[p] = j + 1;
        }

        cout << "Case #" << i + 1 << ": ";
        pintAnts(leftAnts, rightAnts, ants);
        cout <<"\n";
    }
}