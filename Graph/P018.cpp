#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int ladderLength(string startWord, string targetWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if(dict.find(targetWord) == dict.end()) return 0; // target not in dict
        
        queue<pair<string, int>> q;
        q.push({startWord, 1});
        
        while(!q.empty()) {
            auto [word, steps] = q.front();
            q.pop();
            
            if(word == targetWord) return steps;
            
            for(int i = 0; i < word.size(); i++) {
                char original = word[i];
                for(char ch = 'a'; ch <= 'z'; ch++) {
                    if(ch == original) continue;
                    word[i] = ch;
                    if(dict.find(word) != dict.end()) {
                        q.push({word, steps + 1});
                        dict.erase(word); // mark visited
                    }
                }
                word[i] = original; // restore
            }
        }
        
        return 0;
    }
};

int main() {
    string startWord = "hit";
    string targetWord = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    
    Solution sol;
    cout << sol.ladderLength(startWord, targetWord, wordList) << endl; 
    // Output: 5  (hit -> hot -> dot -> dog -> cog)
    
    return 0;
}
