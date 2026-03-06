#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#ifdef _WIN32 // Check if the code is being compiled on a Windows platform to include windows.h for console code page settings
#include <windows.h>
#endif
#include <algorithm> // For std::all_of
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
#include <cctype> // For std::isdigit

=======
#include <cctype>    // For std::isdigit
#include <fstream>   // For file handling
>>>>>>> Stashed changes
=======
#include <cctype>    // For std::isdigit
#include <fstream>   // For file handling
>>>>>>> Stashed changes
=======
#include <cctype>    // For std::isdigit
#include <fstream>   // For file handling
>>>>>>> Stashed changes
using namespace std;

// ========================
//       USER CLASS
// ========================
class User
{
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

public:
    User()
    {
        this->username = "";
        this->password = "";
        this->phoneNumber = "";
        this->status = "Available";
        updateLastSeen();
    }

    User(string uname, string pwd, string phone)
    {
        this->username = uname;
        this->status = "Available";
        setPhoneNumber(phone);
        changePassword(pwd);
        updateLastSeen();
    }

    string getUsername() const
    {
        return this->username;
    }

    string getPhoneNumber() const
    {
        return this->phoneNumber;
    }

    string getStatus() const
    {
        return status;
    }

    string getLastSeen() const
    {
        return lastSeen;
    }

    void setStatus(string newStatus)
    {
        status = newStatus;
    }

    void updateLastSeen()
    {
        time_t now = time(nullptr);
        lastSeen = ctime(&now);
        if (!lastSeen.empty() && lastSeen.back() == '\n')
        {
            lastSeen.pop_back();
        }
    }

    void setPhoneNumber(string phone)
    {
        if (phone.empty())
        {
            return;
        }
        // Exit early if the phone number is '+' only or empty
        int start = (phone[0] == '+') ? 1 : 0;
        if (start == static_cast<int>(phone.size()))
        {
            return;
        }
        // Check if all characters after the optional '+' are digits
        // uses a lambda function to check if each character is a digit using the isdigit function from <cctype>
        bool isValid = all_of(phone.begin() + start, phone.end(), [](unsigned char ch)
                              { return isdigit(ch); });

        if (isValid)
        {
            this->phoneNumber = phone;
        }
    }

    bool checkPassword(string pwd) const
    {
        return this->password == pwd;
    }

    void changePassword(string newPwd)
    {
        if (newPwd.length() > 6)
        {
            this->password = newPwd;
        }
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message
{
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message *replyTo;

public:
    Message()
    {
        // TODO: Implement default constructor
        // all value are empty
        sender = "";
        content = "";
        timestamp = "";
        status = "";
        replyTo = nullptr;
    }

    Message(string sndr, string cntnt)
    {
        // TODO: Implement parameterized constructor
        sender = sndr;
        content = cntnt;
        time_t curr_now = time(nullptr); // get current time from c time library and put it in time_t variable
        timestamp = ctime(&curr_now);    // convert that number variable into a string and update the current timestamp to that timestmp
        status = "sent";                 // current status is sent
        replyTo = nullptr;               // reply to null
    }

    string getContent() const
    {
        // TODO: Implement getter

        return content;
    }

    string getSender() const
    {
        // TODO: Implement getter
        return sender;
    }

    string getTimestamp() const
    {
        // TODO: Implement getter
        return timestamp;
    }

    string getStatus() const
    {
        return this->status;
    }

    Message *getReplyTo() const
    {
        return this->replyTo;
    }

    void setStatus(string newStatus)
    {
        this->status = newStatus;
    }

    void setReplyTo(Message *msg)
    {
        this->replyTo = msg;
    }

    void updateTimestamp()
    {
        // timestamp update
        time_t curr_now = time(nullptr); // get current time from c time library and put it in time_t variable
        timestamp = ctime(&curr_now);    // convert that number variable into a string and update the current timestamp to that timestmp
    }

    void display() const
    {
        // message display
        cout << "From: " << sender << endl;
        cout << "Time: " << timestamp << endl;
        cout << "Status: " << status << endl;
        if (replyTo != nullptr)
        {
            cout << "Replying to: " << endl;
            cout << "\t" << replyTo->getSender() << ": \"" << replyTo->getContent() << "\"" << endl;
        }
        cout << "Message:\t\"" << content << "\"" << endl;
    }

    void addEmoji(string emojiCode)
    {
        // emoji support
        for (int i = 0; i < content.size(); i++)
        {
            if (i + 10 <= content.size() && content.compare(i, 10, ":thumbsup:") == 0 && emojiCode == ":thumbsup:")
            {
                content.replace(i, 10, "👍");
                i++;
            }
            else if (i + 2 <= content.size())
            {
                string sub = content.substr(i, 2);
                if (sub == ":)" && emojiCode == ":)")
                {
                    content.replace(i, 2, "😊");
                    i++;
                }
                else if (sub == ":(" && emojiCode == ":(")
                {
                    content.replace(i, 2, "😢");
                    i++;
                }
                else if (sub == ":D" && emojiCode == ":D")
                {
                    content.replace(i, 2, "😃");
                    i++;
                }
                else if (sub == "<3" && emojiCode == "<3")
                {
                    content.replace(i, 2, "❤️");
                    i++;
                }
            }
        }
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat
{
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat()
    {
        participants.clear();
        messages.clear();
        chatName = "";
    }

    Chat(vector<string> users, string name)
    {
        participants = users;
        messages.clear();
        chatName = name;
    }

    void addMessage(const Message &msg)
    {
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string &username)
    {
        if (index < 0 || index >= static_cast<int>(messages.size())) // Check if index is out of bounds
        {
            return false;
        }

        if (messages[index].getSender() != username) // Check if the user is the sender of the message
        {
            return false;
        }

        messages.erase(messages.begin() + index);
        return true;
    }

    virtual void displayChat() const
    {
        // TODO: Implement chat display
    }

    vector<Message> searchMessages(string keyword) const
    {
<<<<<<< Updated upstream
        // TODO: Implement message search
        return {};
=======
        vector<Message> results;
        for (const auto &msg : messages)
        {
            if (msg.getContent().find(keyword) != string::npos)
            {
                results.push_back(msg);
            }
        }
        return results;
>>>>>>> Stashed changes
    }

    void exportToFile(const string &filename) const
    {
<<<<<<< Updated upstream
        // TODO: Implement export to file
=======
        string filename = filename + ".txt";
        ofstream outFile(filename);
        for (const auto &msg : messages)
        {
            outFile << msg.getContent() << endl;
        }
        outFile.close();
>>>>>>> Stashed changes
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat
{
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2)
    {
        // TODO: Implement constructor
    }

    void displayChat() const override
    {
        // TODO: Implement private chat display
    }

    void showTypingIndicator(const string &username) const
    {
        // TODO: Implement typing indicator
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat
{
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator)
    {
        // TODO: Implement constructor
    }

    void addAdmin(string newAdmin)
    {
        // TODO: Implement add admin
    }

    bool removeParticipant(const string &admin, const string &userToRemove)
    {
        // TODO: Implement remove participant
        return false;
    }

    bool isAdmin(string username) const
    {
        // TODO: Implement admin check
        return false;
    }

    bool isParticipant(string username) const
    {
        // TODO: Implement participant check
        return false;
    }

    void setDescription(string desc)
    {
        // TODO: Implement set description
    }

    void displayChat() const override
    {
        // TODO: Implement group chat display
    }

    void sendJoinRequest(const string &username)
    {
        // TODO: Implement join request
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp
{
private:
    vector<User> users;
    vector<Chat *> chats;
    int currentUserIndex;

    int findUserIndex(string username) const
    {
        // TODO: Implement user search
        return -1;
    }

    bool isLoggedIn() const
    {
        // TODO: Implement login check
        return false;
    }

    string getCurrentUsername() const
    {
        // TODO: Implement get current user
        return "";
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp()
    {
        // TODO: Implement user registration
    }

    void login()
    {
        // TODO: Implement user login
    }

    void startPrivateChat()
    {
        // TODO: Implement private chat creation
    }

    void createGroup()
    {
        // TODO: Implement group creation
    }

    void viewChats() const
    {
        // TODO: Implement chat viewing
    }

    void logout()
    {
        // TODO: Implement logout
    }

    void run()
    {
        while (true)
        {
            if (!isLoggedIn())
            {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    login();
                else if (choice == 2)
                    signUp();
                else if (choice == 3)
                    break;
            }
            else
            {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    startPrivateChat();
                else if (choice == 2)
                    createGroup();
                else if (choice == 3)
                    viewChats();
                else if (choice == 4)
                    logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main()
{
#ifdef _WIN32 // Check if the code is being compiled on a Windows platform to set the console code page to UTF-8 for proper emoji display
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
