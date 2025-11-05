#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include "user.hpp"

bool pairComparator(std::pair<std::string, int> &a, std::pair<std::string, int> &b)
{
    if (a.second != b.second)
    {
        return a.second > b.second;
    }
    return a.first < b.first;
}

class Graph
{
private:
    std::unordered_map<std::string, User> adj;

    std::string toLower(std::string s)
    {
        std::string result = "";
        for (char c : s)
        {
            if (c >= 'A' && c <= 'Z')
                result += (('a' - 'A') + c);
            else
                result += c;
        }
        return result;
    }

public:
    void addUser(const std::string &u)
    {
        std::string name = toLower(u);
        if (!adj.count(name))
        {
            adj[name] = User(name);
        }
    }

    void addFriend(const std::string &u, const std::string &v)
    {
        std::string a = toLower(u);
        std::string b = toLower(v);

        if (a == b)
        {
            std::cout << "Both " << u << " & " << v << " are the same username." << std::endl;
            return;
        }

        bool missing = false;
        if (!adj.count(a))
        {
            std::cout << "Username " << u << " is not added in the network." << std::endl;
            missing = true;
        }
        if (!adj.count(b))
        {
            std::cout << "Username " << v << " is not added in the network." << std::endl;
            missing = true;
        }
        if (missing)
        {
            std::cout << "Enter the next command: " << std::endl;
            return;
        }
        if(adj[a].isFriend(b)){
            std::cout << "Users: " << u << " & " << v << " are friends already." << std::endl;
            return;
        }
        adj[a].addFriends(b);
        adj[b].addFriends(a);
        std::cout << "Users: " << u << " & " << v << " has become friends." << std::endl;
    }

    void listFriends(const std::string &u)
    {
        std::string name = toLower(u);
        if (!adj.count(name))
        {
            std::cout << "Username " << u << " is not added in the network." << std::endl;
            return;
        }
        std::vector<std::string> friends;
        for (auto &f : adj[name].getFriends())
        {
            friends.push_back(f);
        }
        int t = friends.size();
        std::sort(friends.begin(), friends.end());
        for (int i = 0; i < t; i++)
        {
            std::cout << friends[i] << " ";
        }
        std::cout << std::endl;
    }

    void suggestFriends(const std::string &u, int N)
    {
        std::string name = toLower(u);
        if (!adj.count(name))
        {
            std::cout << "Username " << u << " is not added in the network." << std::endl;
            return;
        }
        if (N == 0)
            return;

        std::unordered_map<std::string, int> mutualCount;

        for (auto &f1 : adj[name].getFriends())
        {
            for (auto &f2 : adj[f1].getFriends())
            {
                if (f2 == name)
                    continue;
                if (adj[name].isFriend(f2))
                    continue;
                mutualCount[f2]++;
            }
        }

        std::vector<std::pair<std::string, int>> candidates(mutualCount.begin(), mutualCount.end());
        std::sort(candidates.begin(), candidates.end(), pairComparator);

        int count = 0;
        if (candidates.size() == 0)
        {
            std::cout << "Sorry, User " << u << " has no mutual friends." << std::endl;
        }

        int t = candidates.size();
        if (N > t)
        {
            N = t;
        }
        for (int i = 0; i < t; i++)
        {
            if (count == N - 1)
            {
                std::cout << candidates[i].first << ".";
                break;
            }
            std::cout << candidates[i].first << ", ";
            count++;
        }
        std::cout << std::endl;
    }

    int degreesOfSeparation(const std::string &u, const std::string &v)
    {
        std::string a = toLower(u);
        std::string b = toLower(v);

        bool missing = false;
        if (!adj.count(a))
        {
            std::cout << "Username " << u << " is not added in the network." << std::endl;
            missing = true;
        }
        if (!adj.count(b))
        {
            std::cout << "Username " << v << " is not added in the network." << std::endl;
            missing = true;
        }
        if (missing)
        {
            return -1;
        }
        if (a == b)
            return 0;

        std::queue<std::string> q;
        std::unordered_map<std::string, int> dist;
        q.push(a);
        dist[a] = 0;
        while (!q.empty())
        {
            std::string front = q.front();
            q.pop();

            for (auto &ngbr : adj[front].getFriends())
            {
                if (!dist.count(ngbr))
                {
                    dist[ngbr] = dist[front] + 1;
                    if (ngbr == b)
                        return dist[ngbr];
                    q.push(ngbr);
                }
            }
        }
        return -1;
    }

    bool hasUser(std::string &name)
    {
        return adj.count(toLower(name)) > 0;
    }

    User &getUser(std::string &name)
    {
        return adj[toLower(name)];
    }
};

#endif