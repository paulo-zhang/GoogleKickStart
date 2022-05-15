#include <bits/stdc++.h>
using namespace std;

class MilkTea {
    public:
    string options;
    int score = 0;
    MilkTea(const string& opt, const vector<vector<int>> &scores) : options(opt){
        for(int i = 0;i < options.size();i ++){
          score += scores[i][options[i] - '0'];
        }
    }

    void AddOption(char c, const vector<vector<int>> &scores){
        options.push_back(c);
        score += scores[options.size() - 1][c - '0'];
    }
};

int GetMinimumNumberOfComplaints(const vector<string>& friend_orders,
                                 const vector<string>& forbidden_orders, int options) {
  vector<vector<int>> scores(options, vector<int>(2)); // The score for each position vs '0-1' option. This is optimization for performance.
  for(const string& s : friend_orders){
    for(int i = 0; i < s.size(); i ++){
        scores[i][s[i] - '0'] ++;
    }
  }

  vector<MilkTea> milkteas;
  milkteas.reserve(options);
  milkteas.push_back(MilkTea("0", scores));
  milkteas.push_back(MilkTea("1", scores));

  while(milkteas[0].options.size() < options){
      int size = milkteas.size();
      for(int i = 0;i < size; i ++){
        milkteas.push_back(milkteas[i]);
        milkteas[i].AddOption('0', scores);
        milkteas.back().AddOption('1', scores);
      }

      if(milkteas.size() > forbidden_orders.size() + 1){
        sort(milkteas.begin(), milkteas.end(), [](const auto& t1, const auto& t2){ return t1.score > t2.score;});
        while(milkteas.size() > forbidden_orders.size() + 1){ // Only need to save N + 1, at least one will be different with forbidden set.
          milkteas.pop_back(); // Remove the smaller-score milktea to reduce the size of next iteration.
        }
      }
  }

  unordered_set<string> hashSet(forbidden_orders.begin(), forbidden_orders.end());
  for(const auto& t : milkteas){
    if(hashSet.find(t.options) == hashSet.end()){
      return friend_orders.size() * options - t.score;
    }
  }

  return 0;
}

int main() {
  int t;
  // 't' refers to number of test cases.
  cin >> t;
  for (int tc = 1; tc <= t; ++tc) {
    // 'n' refers to preferences of friends.
    // 'm' refers to number of prohibited milk teas.
    // 'p' refers to binary options available at the tea shop.
    int n, m, p;
    cin >> n;
    cin >> m;
    cin >> p;
    vector<string> friend_orders(n);
    vector<string> forbidden_orders(m);
    for (int i = 0; i < n; ++i) {
      cin >> friend_orders[i];
    }
    for (int i = 0; i < m; ++i) {
      cin >> forbidden_orders[i];
    }
    cout << "Case #" << tc << ": "
         << GetMinimumNumberOfComplaints(friend_orders, forbidden_orders, p)
         << endl;
  }
  return 0;
}
