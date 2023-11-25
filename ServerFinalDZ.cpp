#include <iostream>
#include <vector>
#include <string>

struct Message {
    std::string username;
    std::string content;
    bool isPrivate;
};

class Chat {
private:
    std::vector<Message> messages;
    std::vector<std::string> users;
    std::vector<std::string> bannedUsers;
public:
    void sendMessage(const std::string& username, const std::string& content, bool isPrivate = false) {
        if (isUserBanned(username)) {
            std::cout << "You are banned and cannot send messages." << std::endl;
            return;
        }

        Message message;
        message.username = username;
        message.content = content;
        message.isPrivate = isPrivate;

        messages.push_back(message);
    }

    void viewAllMessages() const {
        for (const auto& message : messages) {
            std::cout << "[" << message.username << "]: " << message.content << std::endl;
        }
    }

    void viewPrivateMessages(const std::string& username) const {
        for (const auto& message : messages) {
            if (message.isPrivate && (message.username == username || message.content.find("@" + username) != std::string::npos)) {
                std::cout << "[" << message.username << " to " << username << "]: " << message.content << std::endl;
            }
        }
    }

    void viewUsers() const {
        std::cout << "Users: ";
        for (const auto& user : users) {
            std::cout << user << " ";
        }
        std::cout << std::endl;
    }

    void banUser(const std::string& username) {
        bannedUsers.push_back(username);
        std::cout << username << " has been banned." << std::endl;
    }

    void disconnectUser(const std::string& username) {
        auto it = std::find(users.begin(), users.end(), username);
        if (it != users.end()) {
            users.erase(it);
            std::cout << username << " has been disconnected." << std::endl;
        }
        else {
            std::cout << username << " is not online." << std::endl;
        }
    }

    void addUser(const std::string& username) {
        users.push_back(username);
        std::cout << username << " has joined the chat." << std::endl;
    }

    bool isUserBanned(const std::string& username) const {
        return std::find(bannedUsers.begin(), bannedUsers.end(), username) != bannedUsers.end();
    }
};

int main() {
    Chat chat;
    chat.addUser("User1");
    chat.addUser("User2");
    chat.addUser("User3");

    chat.sendMessage("User1", "Hello everyone!");

    chat.viewAllMessages();
    chat.viewPrivateMessages("User2");
    chat.viewPrivateMessages("User3");

    chat.banUser("User2");
    chat.disconnectUser("User1");

    chat.viewUsers();

    return 0;
}