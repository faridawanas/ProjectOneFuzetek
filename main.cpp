#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#endif
#include <algorithm>
#include <cctype>
#include <fstream>

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
        bool isValid = all_of(phone.begin() + start, phone.end(), [](unsigned char ch)
        {
            return isdigit(ch);
        });

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
        cout << "\nFrom: " << sender << endl;
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


    bool isParticipant(string username) const
    {
        // TODO: Implement participant check
        for (string p : participants)
        {
            if (p == username) return true;
        }
        return false;
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
        for(int i = 0 ; i < messages.size() ; i++)
        {
            cout << "\nMessage #" << i << endl;
            messages[i].display();
        }
    }

    vector<Message> searchMessages(string keyword) const
    {
        vector<Message> results;

        for (const auto &msg : messages)

        {
            if (msg.getContent().find(keyword) != string::npos)
            {
                results.push_back(msg);
            }
        }
        return results;
    }

    void exportToFile(const string &filename) const
    {
        string name = filename + ".txt";
        ofstream outFile(name);
        for (const auto &msg : messages)

        {
            outFile << msg.getContent() << endl;
        }
        outFile.close();
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
        user1 = u1;
        user2 = u2;
        chatName = u1 + " & " + u2;
        participants.push_back(u1);
        participants.push_back(u2);
    }

    void displayChat() const override
    {
        // TODO: Implement private chat display
        cout << "-------------Private Chat between " << user1 << " and " << user2 <<"-------------"<< endl;
        Chat::displayChat();
    }

    void showTypingIndicator(const string &username) const
    {
        cout << username << " is typing..." << endl;
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
    vector<string> joinRequests; // a waitlist for users that needs admins aproving to join the chat


public:
    GroupChat(vector<string> users, string name, string creator)
    {
        // TODO: Implement constructor
        participants = users;
        chatName = name;
        admins.push_back(creator);
        description = ";";
    }

    void addAdmin(string newAdmin)
    {
        // TODO: Implement add admin
        if (!isAdmin(newAdmin))
        {
            //prevent duplicates
            admins.push_back(newAdmin);
        }
    }

    bool removeParticipant(const string &admin, const string &userToRemove)
    {

        // TODO: Implement remove participant
        if (isAdmin(admin) && isParticipant(userToRemove))  // use the isAdmin methods to check if an admin is in the admins list
        {

            participants.erase(std::remove(participants.begin(), participants.end(), userToRemove), participants.end());
            return true;
        }
        return false;
    }

    bool isAdmin(string username) const
    {
        // TODO: Implement admin check
        for (int i = 0 ; i<admins.size() ; i++)
        {
            if(username == admins[i]) return true;
        }
        return false;
    }



    void setDescription(string desc)
    {
        // TODO: Implement set description
        description = desc;
    }

    void displayChat() const override
    {
        // TODO: Implement group chat display
        cout << "------------Group Chat: " << chatName <<"-----------------"<< endl;
        cout << "Participants: " ;
        for (int i = 0 ; i<participants.size() ; i++)
        {
            cout << participants[i] << " ";
        }
        cout << endl;
        Chat::displayChat();
    }

    void sendJoinRequest(const string &username)
    {
        // TODO: Implement join request
        // check if the username is not in participants list
        if (!isParticipant(username))
        {
            joinRequests.push_back(username); // add the username to the participants vector
        }
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
        for (int i = 0 ; i < users.size(); i++)
        {

            if (users[i].getUsername() == username)
            {
                return i;
            }
        }

        return -1;
    }

    bool isLoggedIn() const
    {
        // TODO: Implement login check
        return currentUserIndex != -1;
    }

    string getCurrentUsername() const
    {
        // TODO: Implement get current user
        // saftey check
        if (currentUserIndex == -1)
        {
            return "";
        }
        return users[currentUserIndex].getUsername();
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp()
    {
        // TODO: Implement user registration
        string name, phone, password="";
        int flag = 0;
        while(flag == 0)
        {
            cout << "Enter your username: ";
            cin >> name;
            flag = 1;
            for(User u : users)
            {
                if(name == u.getUsername())
                {
                    cout << "Username already exists"<<endl;
                    flag = 0;
                }

            }
        }
        cout << "Enter your phone number: ";
        cin >> phone;
        while (password.size() <= 6)
        {
            cout << "Enter a password(length > 6): ";
            cin >> password;
        }
        User u(name, password, phone);
        users.push_back(u);
        cout << " User created, can login with credentials";
    }

    void login()
    {
        string log_username;
        string log_pass;
        int log_indx;
        // TODO: Implement user login
        // Get user credntials  username and password
        cout << "please enter username:"<<endl;
        cin >> log_username;
        cout << "please enter password:"<<endl;
        cin >> log_pass;
        // search for index of user trying to log in the users databse
        log_indx =  findUserIndex(log_username);
        // check these credintials against the database if not print error you need to register again
        // not found the user
        if (log_indx ==-1)
        {
            cout << "username does not exist";
        }
        // found the user
        else
        {
            // check password against the user password
            // if the password do not exist
            if (!users[log_indx].checkPassword(log_pass))
            {
                cout << "password is not correct"<<endl;
            }
            else
            {
                // if yes  set current index to that logged in user index

                currentUserIndex = log_indx;
                cout << "user logged in succesfully"<<endl ;

            }
        }

    }

    void startPrivateChat()
    {
        // TODO: Implement private chat creation
        string OTHERUSER;
        cout << "Enter the name of the other user: ";
        cin >> OTHERUSER;
        int flag = 0;
        for(User u : users)
        {
            if(u.getUsername() == OTHERUSER)
            {
                flag = 1;
                PrivateChat *newChat = new PrivateChat(getCurrentUsername(),OTHERUSER);
                chats.push_back(newChat);
                cin.ignore();
                string m;
                cout << "Chat with " << OTHERUSER << endl;
                cout << "\nEnter your message(enter \"exit\" to close the chat): ";
                getline(cin, m);
                while(m != "exit")
                {
                    Message mes(getCurrentUsername(), m);
                    mes.addEmoji(":)");
                    mes.addEmoji(":(");
                    mes.addEmoji("<3");
                    mes.addEmoji(":thumbsup:");
                    mes.addEmoji(":D");
                    newChat->addMessage(mes);
                    mes.display();
                    cout << "\nEnter your message(enter \"exit\" to close the chat): ";
                    getline(cin, m);

                }
                break;
            }
        }
        if (flag ==0 )
        {
            cout << "User not found";
        }
    }

    void createGroup()
    {
        // TODO: Implement group creation
        string GroupName;
        cout << "Enter a name for the group: ";
        cin >> GroupName;
        vector <string> participants;
        string x;
        int z, n=0;
        while(n < 2)
        {
            cout << "Enter number of participants(must be > 1): ";
            cin >> n;
        }
        participants.push_back(getCurrentUsername());
        for(int i = 0; i< n ;)
        {
            cout << "Enter participant username: ";
            cin >> x;
            z = 0;
            int alreadyIn = 0;
            for(string p : participants)
            {
                if (p == x)
                {
                    cout << "Already in group\n";
                    alreadyIn = 1;

                }
            }
            if(!alreadyIn)
            {
                for(User u : users)
                {
                    if(u.getUsername() == x)
                    {
                        z = 1;
                        cout << "Added " << u.getUsername() << endl;
                        participants.push_back(u.getUsername());
                        i++;
                    }
                }
                if(z == 0)
                {
                    cout << "No user with this username" << endl;
                }
            }
        }
        GroupChat *newChat = new GroupChat(participants,GroupName,getCurrentUsername());
        chats.push_back(newChat);

        cin.ignore();
        string m;
        cout << "\nEnter your message(enter \"exit\" to close the chat): ";
        getline(cin, m);
        while(m != "exit")
        {
            Message mes(getCurrentUsername(), m);
            mes.addEmoji(":)");
            mes.addEmoji(":(");
            mes.addEmoji("<3");
            mes.addEmoji(":thumbsup:");
            mes.addEmoji(":D");
            newChat->addMessage(mes);
            mes.display();
            cout << "\nEnter your message(enter \"exit\" to close the chat): ";
            getline(cin, m);
        }

    }

    void viewChats()
    {
        string currentUser = getCurrentUsername();
        vector<int> visibleChats;

        cout << "\nYour Chats:\n";

        for (int i = 0; i < chats.size(); i++)
        {
            if (chats[i]->isParticipant(currentUser))
            {
                cout << visibleChats.size() + 1 << ". Chat " << i + 1 << endl;
                visibleChats.push_back(i);
            }
        }

        if (visibleChats.empty())
        {
            cout << "You are not part of any chats.\n";
            return;
        }

        cout << "Select chat number to view (0 to cancel): ";
        int choice;
        cin >> choice;

        if (choice == 0) return;

        if (choice < 1 || choice > visibleChats.size())
        {
            cout << "Invalid choice.\n";
            return;
        }

        Chat* selectedChat = chats[visibleChats[choice - 1]];
        cout << "\n------------- CHAT -------------\n";
        selectedChat->displayChat();

        while(true)
        {

            cout << "\n1. Send Message\n";
            cout << "2. Search Messages\n";
            cout << "3. Delete Message\n";
            cout << "4. Export Chat\n";

            GroupChat* gChat = dynamic_cast<GroupChat*>(selectedChat);

            if(gChat && gChat->isAdmin(currentUser))
            {
                cout << "5. Add Admin\n";
                cout << "6. Remove Participant\n";
                cout << "7. Exit Chat\n";
            }
            else
            {
                cout << "5. Exit Chat\n";
            }

            int option;
            cin >> option;
            cin.ignore();

            if(option == 1)
            {
                string m;
                cout << "Enter message: ";
                getline(cin, m);

                Message mes(currentUser, m);

                mes.addEmoji(":)");
                mes.addEmoji(":(");
                mes.addEmoji("<3");
                mes.addEmoji(":thumbsup:");
                mes.addEmoji(":D");

                selectedChat->addMessage(mes);
                mes.display();
            }

            else if(option == 2)
            {
                string keyword;
                cout << "Enter keyword: ";
                getline(cin, keyword);

                vector<Message> results = selectedChat->searchMessages(keyword);

                if(results.empty())
                    cout << "No messages found.\n";
                else
                {
                    for(const Message &m : results)
                        m.display();
                }
            }

            else if(option == 3)
            {
                int index;
                cout << "Enter message index to delete: ";
                cin >> index;

                if(selectedChat->deleteMessage(index, currentUser))
                    cout << "Message deleted.\n";
                else
                    cout << "Cannot delete this message.\n";
            }

            else if(option == 4)
            {
                string file;
                cout << "Enter filename: ";
                cin >> file;

                selectedChat->exportToFile(file);
                cout << "Chat exported.\n";
            }


            else if(gChat && gChat->isAdmin(currentUser) && option == 5)
            {
                string newAdmin;
                cout << "Enter username to make admin: ";
                cin >> newAdmin;

                if(gChat->isParticipant(newAdmin))
                {
                    gChat->addAdmin(newAdmin);
                    cout << newAdmin << " is now an admin.\n";
                }
                else
                {
                    cout << "User is not in the group.\n";
                }
            }

            else if(gChat && gChat->isAdmin(currentUser) && option == 6)
            {
                string userRemove;
                cout << "Enter username to remove: ";
                cin >> userRemove;

                if(gChat->removeParticipant(currentUser, userRemove))
                    cout << userRemove << " removed from group.\n";
                else
                    cout << "Cannot remove user.\n";
            }

            else if((gChat && gChat->isAdmin(currentUser) && option == 7) ||
                    (!gChat && option == 5) ||
                    (gChat && !gChat->isAdmin(currentUser) && option == 5))
            {
                break;
            }

            else
            {
                cout << "Invalid option.\n";
            }
        }
    }

    void logout()
    {
        // TODO: Implement logout
        currentUserIndex = -1;
        cout << "Logged out successfull." << endl;
    }

    void run()
    {
        while (true)
        {
            if (!isLoggedIn())
            {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                while(!(cin >> choice))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Enter a number: ";
                }

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
                while(!(cin >> choice))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Enter a number: ";
                }

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
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
