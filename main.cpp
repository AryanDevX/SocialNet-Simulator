#include <iostream>
#include <sstream>
#include <string>
#include "Graph.hpp"

int main()
{
    Graph socialNet;
    std::string line;

    std::cout << "---------SocialNet Simulator-------- " << std::endl;
    std::cout << "Enter commands (type EXIT to quit):" << std::endl;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "ADD")
        {
            std::string type;
            ss >> type;

            if (type == "USER")
            {
                std::string username, temp;
                ss >> username;
                std::getline(ss, temp);
                temp.erase(0, temp.find_first_not_of(' '));
                if (username.empty())
                {
                    std::cout << "No username provided." << std::endl;
                    continue;
                }
                if(!temp.empty()){
                    std::cout << "Username has spaces" << std::endl;
                    continue;
                }
                if(!socialNet.hasUser(username)){
                    socialNet.addUser(username);
                    std::cout << "User " << username << " has been added successfully." << std::endl;
                }
                else{
                    std::cout << "User " << username << " has been already added." << std::endl;
                }

            }

            else if (type == "FRIEND")
            {
                std::string u, v, temp;
                ss >> u >> v;
                std::getline(ss, temp);
                temp.erase(0, temp.find_first_not_of(' '));
                if (u.empty() || v.empty())
                {
                    std::cout << "Provide both the usernames." << std::endl;
                    continue;
                }
                if(!temp.empty()){
                    std::cout << "Username has spaces." << std::endl;
                    continue;
                }

                socialNet.addFriend(u, v);
            }

            else if (type == "POST")
            {
                std::string u;
                ss >> u;

                if (!socialNet.hasUser(u))
                {
                    std::cout << "User " << u << " is not in the network." << std::endl;
                    continue;
                }

                std::string content;
                std::getline(ss, content);
                if (!content.empty() && content[0] == ' ')
                    content.erase(0, 1);

                if (content.empty())
                {
                    std::cout << "Provide the content for the post." << std::endl;
                    continue;
                }

                socialNet.getUser(u).addPost(content);
                std::cout << "Post added for user " << u << "." << std::endl;
            }

            else
            {
                std::cout << "Invalid ADD command." << std::endl;
            }
        }

        else if (cmd == "LIST")
        {
            std::string type, u;
            ss >> type >> u;

            if (type == "FRIENDS")
            {
                if (!socialNet.hasUser(u))
                {
                    std::cout << "User '" << u << " is not found." << std::endl;
                    continue;
                }

                std::cout << "Friends of " << u << ": ";
                socialNet.listFriends(u);
            }
            else
            {
                std::cout << "Invalid LIST command." << std::endl;
            }
        }

        else if (cmd == "SUGGEST")
        {
            std::string type, u;
            int N;
            if (ss >> type >> u >> N)
            {
            }
            else
            {
                std::cout << "Wrong command format!" << std::endl;
                continue;
            }
            if (type != "FRIENDS" || N <-1)
            {
                std::cout << "Invalid SUGGEST command format." << std::endl;
                continue;
            }

            if (!socialNet.hasUser(u))
            {
                std::cout << "User '" << u << " is not found." << std::endl;
                continue;
            }
            std::cout << "Friend suggestions for " << u << ": ";
            socialNet.suggestFriends(u, N);
        }

        else if (cmd == "DEGREES")
        {
            std::string w1, w2, u, v;
            ss >> w1 >> w2 >> u >> v;
            if (w1 == "OF" && w2 == "SEPARATION")
            {
            }
            else
            {
                std::cout << "Invalid command. Try again." << std::endl;
                continue;
            }
            if (!socialNet.hasUser(u) || !socialNet.hasUser(v))
            {
                std::cout << "One or both usernames not found." << std::endl;
                continue;
            }

            int degree = socialNet.degreesOfSeparation(u, v);
            if (degree == -1)
                std::cout << "No connection found between " << u << " and " << v << "." << std::endl;
            else
                std::cout << "Degrees of separation between " << u << " and " << v << ": " << degree << std::endl;
        }

        else if (cmd == "OUTPUT")
        {
            std::string type, u;
            int N;
            ss >> type >> u;

            if (type == "POSTS")
            {
                if (!socialNet.hasUser(u))
                {
                    std::cout << "Username '" << u << "' not found." << std::endl;
                    continue;
                }
                if (!(ss >> N))
                {
                    std::cout << "Provide the number of posts to output." << std::endl;
                    continue;
                }
                if(N<=0){
                    std::cout << "Invalid number." << std::endl;
                    continue;
                }
                std::cout << "Recent posts by " << u << ":" << std::endl;
                socialNet.getUser(u).outpost(N);
            }
            else
            {
                std::cout << "Invalid OUTPUT command." << std::endl;
            }
        }

        else if (cmd == "EXIT")
        {
            std::cout << "Exiting SocialNet simulator..." << std::endl;
            break;
        }

        else
        {
            std::cout << "Invalid command. Try again." << std::endl;
        }
    }

    return 0;
}