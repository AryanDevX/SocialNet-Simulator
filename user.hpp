#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <unordered_set>
#include "AVLTree.hpp"

class User
{
private:
    std::string username;
    std::unordered_set<std::string> friends;
    AVLTree posts;

public:
    User() {}
    User(std::string name) : username(name) {};
    std::string getname()
    {
        return username;
    }

    void addFriends(std::string f)
    {
        friends.insert(f);
    }

    bool isFriend(std::string f)
    {
        return friends.count(f) > 0;
    }

    std::unordered_set<std::string> getFriends()
    {   
        return friends;
    }

    void addPost(std::string &content)
    {
        posts.insert(content);
    }
    void outpost(int N)
    {
        posts.outputN(N);
    }

    int getSize(){
        return friends.size();
    }
};

#endif