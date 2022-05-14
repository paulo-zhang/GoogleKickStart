#include <iostream>
#include <vector>

using namespace std;

int remainCandies(const vector<int>& bags, int kids){
    int sum = 0;
    for(int n : bags){
        sum += n;
    }
    
    return sum % kids;
}

int main(){
    int T;
    cin >> T;
    int n = 1;
    while(T -- > 0){
        int N, M;
        cin >> N >> M;
        
        vector<int> bags(N);
        int i = 0;
        while(N-- > 0){
            cin >> bags[i ++];
        }
        
        cout << "Case #" << n ++ <<": " << remainCandies(bags, M) << "\n";
    }
}