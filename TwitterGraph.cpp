#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class TwitterGraph {
private:
    // Outgoing edges: User -> Accounts they are following
    std::unordered_map<std::string, std::vector<std::string>> followingMap;
    
    // Incoming edges: User -> Accounts following them (Fans/Followers)
    std::unordered_map<std::string, std::vector<std::string>> followersMap;

public:
    // Establish a relationship: 'follower' follows 'celeb'
    void follow(const std::string& follower, const std::string& celeb) {
        // 1. Add to follower's "following" list
        followingMap[follower].push_back(celeb);
        
        // 2. Add to celeb's "followers" list
        followersMap[celeb].push_back(follower);

        // Ensure keys exist even if they have empty lists
        if (followingMap.find(celeb) == followingMap.end()) {
            followingMap[celeb] = {};
        }
        if (followersMap.find(follower) == followersMap.end()) {
            followersMap[follower] = {};
        }
    }

    // Print a user's Twitter-like profile stats
    void printUserProfile(const std::string& username) const {
        std::cout << "@" << username << " Profile:\n";
        
        // Print Following
        std::cout << "  Following: ";
        auto it1 = followingMap.find(username);
        if (it1 == followingMap.end() || it1->second.empty()) {
            std::cout << "None\n";
        } else {
            for (size_t i = 0; i < it1->second.size(); ++i) {
                std::cout << "@" << it1->second[i] << (i + 1 < it1->second.size() ? ", " : "");
            }
            std::cout << "\n";
        }

        // Print Followers
        std::cout << "  Followers: ";
        auto it2 = followersMap.find(username);
        if (it2 == followersMap.end() || it2->second.empty()) {
            std::cout << "None\n";
        } else {
            for (size_t i = 0; i < it2->second.size(); ++i) {
                std::cout << "@" << it2->second[i] << (i + 1 < it2->second.size() ? ", " : "");
            }
            std::cout << "\n";
        }
        std::cout << "-----------------------------------\n";
    }
};

int main() {
    TwitterGraph twitter;

    // Building the network based on your flow:
    // User1 -> User2, User2 -> User3, User3 -> User4, User5 -> User2
    twitter.follow("User1", "User2");
    twitter.follow("User2", "User3");
    twitter.follow("User3", "User4");
    twitter.follow("User5", "User2");

    // Inspect profiles to see Twitter-like metrics
    twitter.printUserProfile("User2");
    twitter.printUserProfile("User1");

    return 0;
}
