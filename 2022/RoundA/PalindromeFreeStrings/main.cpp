#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool isPalindrome(const string &s, int low, int high)
{
    while (low < high)
    {
        if (s[low++] != s[high--])
            return false;
    }

    return true;
}

bool palindromeFreeString(string &input, int i)
{
    for (int j = i; j < input.size(); j++)
    {
        if (input[j] == '?')
        {
            input[j] = '0';
            if (palindromeFreeString(input, j))
                return true;

            input[j] = '1';
            if (palindromeFreeString(input, j))
                return true;

            input[j] = '?'; // backtrack
            return false;   // Either '0' or '1' is not working.
        }

        // Observation: If a string contains a palindromic substring P of length |P|>6, then it must also contain a palindromic substring of length 5 or 6.
        if (j >= 4 && isPalindrome(input, j - 4, j))
        {
            return false;
        }
        if (j >= 5 && isPalindrome(input, j - 5, j))
        {
            return false;
        }
    }

    return true;
}

int main()
{
    ifstream fin("ts1_input.txt");
    ofstream fout("output.txt");

    int t;
    fin >> t;
    for (int i = 0; i < t; i++)
    {
        int n;
        fin >> n;
        string input;
        fin >> input;
        bool possible = palindromeFreeString(input, 0);
        fout << "Case #" << i + 1 << ": " << (possible ? "POSSIBLE" : "IMPOSSIBLE") << "\n";
    }
}