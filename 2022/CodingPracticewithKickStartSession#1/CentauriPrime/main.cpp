#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

string getRuler(const string &kingdom, const unordered_set<char>& vowels){
    if(kingdom.back() == 'y' || kingdom.back() == 'Y'){
        return "nobody";
    }
    else if(vowels.find(kingdom.back()) != vowels.end()){
        return "Alice";
    }
    
    return "Bob";
}

int main(){
    unordered_set<char> vowels({'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'});
    
    int T;
    cin >> T;
    int n = 1;
    while(T -- > 0){
        string kingdom;
        cin >> kingdom;
        
        cout << "Case #" << n ++ <<": " << kingdom << " is ruled by " << getRuler(kingdom, vowels) << ".\n";
    }
}