#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

vector<int> getHIndex(const vector<int> &citations){
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int hIndex = 0;
    vector<int> answer;
    for(int c : citations){
        if(c > hIndex){ // Possible c for bigger H-Index.
            minHeap.push(c); 
            
            while(!minHeap.empty() && minHeap.top() < hIndex + 1){
                minHeap.pop(); // Remove invalid value for bigger H-Index.
            }
            
            if(minHeap.size() > hIndex){ // The same as minHeap.size() == hIndex + 1
                hIndex ++;
            }
        }
        
        answer.push_back(hIndex);
    }
    
    return answer;
}

int main(){
    int T;
    cin >> T;
    int n = 1;
    while(T -- > 0){
        int N;
        cin >> N;
        vector<int> citations;
        int i = 0;
        cout << "Case #" << n ++ <<":";
        while(N-- > 0){
            int c;
            cin >> c;
            citations.push_back(c);
        }
        
        for(int hIndex : getHIndex(citations)){
            cout << " " << hIndex;
        }
        
        cout << "\n";
    }
}