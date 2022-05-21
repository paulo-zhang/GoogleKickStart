#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int maxSum = 9 * 12 + 1; // The sum ranges from 1 - 1999999999999;
ulong dp[14][2][2][2][maxSum][maxSum + 1]; // Position, greaterA, smallerB, leadingZero, prod, sum;
bool solved[14][2][2][2][maxSum][maxSum + 1];

ulong interestingIntegers(const string& a, const string& b, int position, int greaterA, int smallerB, int leadingZero, int prod, int sum, int targetSum){
    if(position == b.size()){
        return prod == 0 && sum == targetSum; // Finish, check wheter we find the target sum.
    }

    if(sum > targetSum) return 0; // Impossible to find the target sum.

    // Begin memorization
    ulong& count = dp[position][greaterA][smallerB][leadingZero][prod][sum];
    bool& isSolved = solved[position][greaterA][smallerB][leadingZero][prod][sum];
    if(isSolved){
        return count;
    }
    isSolved = true; // Use once for a specific targetSum.
    // End memorization

    for(char ch = '0'; ch <= '9'; ch++){ // Choose one digit at a time for this position, similar to generating permutations.
        if(!greaterA && a[position] > ch) continue; // The previous prefix number is equal to a's prefix, but the current prefix number is smaller than a[indexA], skip this combination.
        if(!smallerB && b[position] < ch) continue; // The previous prefix number is equal to b's prefix, but the current prefix number is bigger than b[indexB], skip this combination.

        int nextGreaterA = greaterA || a[position] < ch; // Whether or not prefix number is greater than a's prefix.
        int nextSmallerB = smallerB || b[position] > ch; // Whether or not prefix number is smaller than b's prefix'.

        int nextProd = (prod * (ch - '0')) % targetSum; // Only care about the mod result.
        int nextSum = sum + ch - '0'; // Sum in the path.

        int nextZero = leadingZero && ch == '0'; // Prefix has leading '0' means a.size() < b.size();
        if(nextZero){
            nextProd = 1; // Reset prod, because the leading '0' makes nextZero = 0.
        }

        count += interestingIntegers(a, b, position + 1, nextGreaterA, nextSmallerB, nextZero, nextProd, nextSum, targetSum);
    }
    
    return count;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        long a, b;
        cin >> a >> b;
        string strB = to_string(b);
        string strA = to_string(a);
        while(strA.size() < strB.size()) strA.insert(strA.begin(), '0'); // pad a with leading '0'.

        ulong count = 0;
        for(int target = 1; target <= maxSum; target ++){ // Try all possible target sum.
            memset(dp, 0, sizeof(dp));
            memset(solved, 0, sizeof(solved));
            count += interestingIntegers(strA, strB, 0, 0, 0, 1, 1, 0, target);
            // cout << "target: " << target << ", count: " << count << "\n";
        }
        
        cout << "Case #" << i + 1 << ": " << count << "\n";
    }
}