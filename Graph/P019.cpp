#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string startWord, string targetWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        vector<vector<string>> result;
        if(dict.find(targetWord) == dict.end()) return result;

        unordered_map<string, vector<string>> parents;
        unordered_set<string> visited, currentLevel;
        queue<string> q;
        q.push(startWord);
        visited.insert(startWord);
        bool found = false;

        while(!q.empty() && !found) {
            int sz = q.size();
            currentLevel.clear();
            for(int i = 0; i < sz; i++) {
                string word = q.front(); q.pop();

                string original = word;
                for(int j = 0; j < word.size(); j++) {
                    char old = word[j];
                    for(char ch = 'a'; ch <= 'z'; ch++) {
                        if(ch == old) continue;
                        word[j] = ch;
                        if(dict.find(word) != dict.end()) {
                            if(!visited.count(word)) {
                                if(!currentLevel.count(word)) {
                                    q.push(word);
                                    currentLevel.insert(word);
                                }
                                parents[word].push_back(original);
                            }
                            if(word == targetWord) {
                                found = true;
                                parents[word].push_back(original);
                            }
                        }
                    }
                    word[j] = old;
                }
            }
            for(auto &w : currentLevel) visited.insert(w);
        }

        if(!found) return result;

        vector<string> path = {targetWord};
        backtrack(result, path, parents, targetWord, startWord);
        return result;
    }

    void backtrack(vector<vector<string>>& result, vector<string>& path,
                   unordered_map<string, vector<string>>& parents,
                   string word, string startWord) {
        if(word == startWord) {
            vector<string> temp = path;
            reverse(temp.begin(), temp.end());
            result.push_back(temp);
            return;
        }
        for(string p : parents[word]) {
            path.push_back(p);
            backtrack(result, path, parents, p, startWord);
            path.pop_back();
        }
    }
};

int main() {
    string startWord = "hit";
    string targetWord = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};

    Solution sol;
    vector<vector<string>> ans = sol.findLadders(startWord, targetWord, wordList);

    for(auto &seq : ans) {
        for(auto &w : seq) cout << w << " ";
        cout << "\n";
    }

    return 0;
}
