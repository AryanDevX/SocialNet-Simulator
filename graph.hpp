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
                result += (c + ('a' - 'A'));
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
            adj[name] = User(name);
    }

    void addFriend(const std::string &u, const std::string &v)
    {
        std::string a = toLower(u);
        std::string b = toLower(v);

        if (a == b)
        {
            std::cout << "Both " << u << " & " << v << " are the same username.\n";
            return;
        }

        bool missing = false;
        if (!adj.count(a))
        {
            std::cout << "Username " << u << " is not added in the network.\n";
            missing = true;
        }
        if (!adj.count(b))
        {
            std::cout << "Username " << v << " is not added in the network.\n";
            missing = true;
        }
        if (missing)
            std::cout << "Enter the next command" << std::endl;
            return;

        adj[a].addFriend(b);
        adj[b].addFriend(a);
    }

    void listFriends(const std::string &u)
    {
        std::string name = toLower(u);
        if (!adj.count(name))
        {
            std::cout << "Username " << u << " is not added in the network.\n";
            return;
        }

        std::vector<std::string> friends(adj[name].getFriends().begin(), adj[name].getFriends().end());
        std::sort(friends.begin(), friends.end());
        for (auto &f : friends)
            std::cout << f << " ";
        std::cout << std::endl;
    }

    void suggestFriends(const std::string &u, int N)
    {
        std::string name = toLower(u);
        if (!adj.count(name))
        {
            std::cout << "Username " << u << " is not added in the network.\n";
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
        std::sort(candidates.begin(), candidates.end(),
                  [](const auto &a, const auto &b)
                  {
                      if (a.second != b.second)
                          return a.second > b.second;
                      return a.first < b.first;
                  });

        int count = 0;
        for (auto &p : candidates)
        {
            if (p.second == N)
                break;
            std::cout << p.first << " ";
            count++;
        }
        std::cout << "\n";
    }

    int degreesOfSeparation(const std::string &u, const std::string &v)
    {
        std::string a = toLower(u);
        std::string b = toLower(v);

        if (!adj.count(a))
        {
            std::cout << "Username " << u << " is not added in the network.\n";
            return -1;
        }
        if (!adj.count(b))
        {
            std::cout << "Username " << v << " is not added in the network.\n";
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
            std::string curr = q.front();
            q.pop();

            for (auto &ngbr : adj[curr].getFriends())
            {
                if (!dist.count(ngbr))
                {
                    dist[ngbr] = dist[curr] + 1;
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