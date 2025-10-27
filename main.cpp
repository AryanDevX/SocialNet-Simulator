#include <iostream>
#include <sstream>
#include <string>
#include "Graph.hpp"

int main() {
    Graph socialNet;
    std::string line;

    std::cout << "------- SocialNet Simulator -------" << std::endl;
    std::cout << "Enter commands (type EXIT to quit):" << std::endl;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "ADD") {
            std::string type;
            ss >> type;

            if (type == "USER") {
                std::string username;
                ss >> username;

                if (username.empty()) {
                    std::cout << "No username provided." << std::endl;
                    continue;
                }

                socialNet.addUser(username);
                std::cout << "User " << username << " has been added successfully." << std::endl;
            }

            else if (type == "FRIEND") {
                std::string u, v;
                ss >> u >> v;

                if (u.empty() || v.empty()) {
                    std::cout << "Provide both the usernames" << std::endl;
                    continue;
                }

                socialNet.addFriend(u, v);
            }

            else if (type == "POST") {
                std::string username;
                ss >> username;

                if (!socialNet.hasUser(username)) {
                    std::cout << "User " << username << " is not in the network." << std::endl;
                    continue;
                }

                std::string content;
                std::getline(ss, content);
                if (!content.empty() && content[0] == ' ')
                    content.erase(0, 1);

                if (content.empty()) {
                    std::cout << "Provide the content for the post." << std::endl;
                    continue;
                }

                socialNet.getUser(username).addPost(content);
                std::cout << "Post added for user '" << username << "." << std::endl;
            }

            else {
                std::cout << "Invalid ADD command." << std::endl;
            }
        }

        else if (cmd == "LIST") {
            std::string type, username;
            ss >> type >> username;

            if (type == "FRIENDS") {
                if (!socialNet.hasUser(username)) {
                    std::cout << "User '" << username << " is not found." << std::endl;
                    continue;
                }

                std::cout << "Friends of " << username << ": ";
                socialNet.listFriends(username);
            } else {
                std::cout << "Invalid LIST command." << std::endl;
            }
        }

        else if (cmd == "SUGGEST") {
            std::string dummy, username;
            int N;
            ss >> dummy >> username >> N;

            if (dummy != "FRIENDS") {
                std::cout << "Invalid SUGGEST command format." << std::endl;
                continue;
            }

            if (!socialNet.hasUser(username)) {
                std::cout << "User '" << username << " is not found." << std::endl;
                continue;
            }

            std::cout << "Friend suggestions for " << username << ": ";
            socialNet.suggestFriends(username, N);
        }

        else if (cmd == "DEGREES OF SEPARATION") {
            std::string u, v;
            ss >> u >> v;

            if (!socialNet.hasUser(u) || !socialNet.hasUser(v)) {
                std::cout << "One or both usernames not found." << std::endl;
                continue;
            }

            int degree = socialNet.degreesOfSeparation(u, v);
            if (degree == -1)
                std::cout << "No connection found between " << u << " and " << v << "." << std::endl;
            else
                std::cout << "Degrees of separation between " << u << " and " << v << ": " << degree << std::endl;
        }

        else if (cmd == "OUTPUT") {
            std::string type, username;
            int N;
            ss >> type >> username >> N;

            if (type == "POSTS") {
                if (!socialNet.hasUser(username)) {
                    std::cout << "Username '" << username << "' not found." << std::endl;
                    continue;
                }

                std::cout << "Recent " << N << " posts by " << username << ":" << std::endl;
                socialNet.getUser(username).outpost(N);
            } else {
                std::cout << "Invalid OUTPUT command."  << std::endl;
            }
        }
        
        else if (cmd == "EXIT") {
            std::cout << "Exiting SocialNet simulator..." << std::endl;
            break;
        }

        else {
            std::cout << "Invalid command. Try again." << std::endl;
        }
    }

    return 0;
}
