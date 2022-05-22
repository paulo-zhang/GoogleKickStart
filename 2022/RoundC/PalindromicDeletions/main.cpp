#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

const int MOD = 1e9 + 7;
long factorials[401] = {0};
long factorial(int n){
    long& answer = factorials[n];
    if(answer > 0) return answer;

    answer = 1;
    while(n > 1){
        answer *= n;
        n --;
    }

    return answer;
}

bool isPalindromic(const string& s){
    int low = 0, high = s.size() - 1;
    while(low < high){
        if(s[low ++] != s[high --])return false;
    }

    return true;
}

unordered_map<string, long> dp;
long palindromicDeletions(const string& s, long path){
    auto it = dp.find(s);
    if(it != dp.end())return it->second;

    if(s.empty()) return path;

    long count = 0;
    for(int i = 0;i < s.size();i ++){
        string newStr = s.substr(0, i) + s.substr(i + 1, s.size() - i - 1);
        long nextPath = path;
        if(isPalindromic(newStr)){
            nextPath ++;
        }

        count += palindromicDeletions(newStr, nextPath);
    }

    dp[s] = count;
    return count;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        cout << "Case #" << i + 1 << ": " << palindromicDeletions(s, 0) << "\n";
    }
}