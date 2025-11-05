#include <bits/stdc++.h>
using namespace std;

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_map<string, list<string>> adj;
    int n = wordList.size();
    int size = wordList[0].size();

    for(int j=0; j<n; j++){
        bool d1 = false;
        bool d2 = false;
        for(int k=0; k<size; k++){
            if(beginWord[k]!=wordList[j][k]){
                if(!d1){
                    d1 = 1;
                }
                else{
                    d2 = 1;
                    break;
                }
            }
        }
        if(!d2){
            adj[beginWord].push_back(wordList[j]);
            // cout << beginWord << wordList[j] << endl;
        }
    }

    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            bool d1 = false;
            bool d2 = false;
            for(int k=0; k<size; k++){
                if(wordList[i][k]!=wordList[j][k]){
                    if(!d1){
                        d1 = 1;
                    }
                    else{
                        d2 = 1;
                        break;
                    }
                }
            }
            if(!d2){
                adj[wordList[i]].push_back(wordList[j]);
                adj[wordList[j]].push_back(wordList[i]);
                // cout << wordList[i] << wordList[j] << endl;
            }
        }
    }
    unordered_map<string, bool> visited;
    queue<string> q;
    q.push(beginWord);
    visited[beginWord] = 1;
    int dist = 1;
    vector<string> vec;
    while(!q.empty()){
        while(!q.empty()){
            vec.push_back(q.front());
            q.pop();
        }
        dist++;
        for(auto i: vec){
            for(auto& ngbr: adj[i]){
                if(ngbr==endWord){
                    return dist;
                }
                if(!visited[ngbr]){
                    q.push(ngbr);
                    visited[ngbr]=1;
                }
            }
        }
        
    }
    return 0;
}

int main(){
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    cout << ladderLength("hit", "cog", wordList) << endl;
}