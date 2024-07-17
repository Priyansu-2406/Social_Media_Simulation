#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Message Class
class Message {
public:
    string sender;
    string receiver;
    string content;

    Message() {}

    Message(string sender, string receiver, string content) {
        this->sender = sender;
        this->receiver = receiver;
        this->content = content;
    }

    void displayMessage() const {
        cout << "From: " << sender << ", To: " << receiver << ", Message: " << content << endl;
    }
};

// Social Media Group Class
class SocialGroup {
public:
    string groupName;
    vector<string> members;
    vector<Message> messages;

    SocialGroup() {}

    SocialGroup(string groupName) {
        this->groupName = groupName;
    }

    void addMember(string userName) {
        if (find(members.begin(), members.end(), userName) == members.end()) {
            members.push_back(userName);
        } else {
            cout << "Member already in the group!" << endl;
        }
    }

    void removeMember(string userName) {
        auto it = find(members.begin(), members.end(), userName);
        if (it != members.end()) {
            members.erase(it);
        } else {
            cout << "Member not found in the group!" << endl;
        }
    }

    void addMessage(string userName, string content) {
        Message msg(userName, groupName, content);
        messages.push_back(msg);
    }

    void displayGroupInfo() const {
        cout << "Group: " << groupName << endl;
        cout << "Members: ";
        for (const string& member : members) {
            cout << member << " ";
        }
        cout << endl;
        cout << "Messages: " << endl;
        for (const Message& msg : messages) {
            msg.displayMessage();
        }
    }
};

// User Class
class User {
public:
    string firstName;
    string lastName;
    int age;
    string gender;

    User() {}

    User(string firstName, string lastName, int age, string gender) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
        this->gender = gender;
    }
};

// Global data structures
map<string, User> mapUserName;                 
map<string, set<string>> friendsMap;           
map<string, SocialGroup> mapGroups;            
map<pair<string, string>, vector<Message>> userMessages; 

// Function to add a user
void addUser(string userName, User user) {
    if (mapUserName.find(userName) == mapUserName.end()) {
        mapUserName[userName] = user;
    } else {
        cout << "Username already taken!" << endl;
    }
}

// Function to make two users friends
void makeThemFriends(string userName1, string userName2) {
    if (mapUserName.find(userName1) != mapUserName.end() && mapUserName.find(userName2) != mapUserName.end()) {
        friendsMap[userName1].insert(userName2);
        friendsMap[userName2].insert(userName1);
    } else {
        cout << "One or both users do not exist!" << endl;
    }
}

// Function to unfriend users
void unfriend(string userName1, string userName2) {
    if (mapUserName.find(userName1) != mapUserName.end() && mapUserName.find(userName2) != mapUserName.end()) {
        friendsMap[userName1].erase(userName2);
        friendsMap[userName2].erase(userName1);
    } else {
        cout << "One or both users do not exist!" << endl;
    }
}

// Function to display all users
void displayAllUsers() {
    for (const auto& i : mapUserName) {
        cout << "Username: " << i.first << ", Name: " << i.second.firstName << " " << i.second.lastName << endl;
    }
}

// Function to display all friendships
void displayAllFriendships() {
    for (const auto& i : friendsMap) {
        cout << i.first << ": ";
        for (const auto& j : i.second) {
            cout << j << " ";
        }
        cout << endl;
    }
}

// Function to send a message between two users
void sendMessage(const string& sender, const string& receiver, const string& content) {
    if (mapUserName.find(sender) != mapUserName.end() && mapUserName.find(receiver) != mapUserName.end()) {
        Message msg(sender, receiver, content);
        userMessages[{sender, receiver}].push_back(msg);
        userMessages[{receiver, sender}].push_back(msg);
        msg.displayMessage();
    } else {
        cout << "One or both users do not exist!" << endl;
    }
}

int main() {
    int choice;
    string userName, firstName, lastName, gender, content, groupName;
    int age;

    while (true) {
        cout << "Menu:\n1. Add User\n2. Make Friends\n3. Unfriend\n4. Send Message\n5. Create Group\n6. Add Member to Group\n7. Send Group Message\n8. Remove Member from Group\n9. Display All Users\n10. Display All Friendships\n11. Display Group Info\n12. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter username: ";
                cin >> userName;
                cout << "Enter first name: ";
                cin >> firstName;
                cout << "Enter last name: ";
                cin >> lastName;
                cout << "Enter age: ";
                cin >> age;
                cout << "Enter gender: ";
                cin >> gender;
                addUser(userName, User(firstName, lastName, age, gender));
                break;
            case 2:
                {
                    string userName1, userName2;
                    cout << "Enter first username: ";
                    cin >> userName1;
                    cout << "Enter second username: ";
                    cin >> userName2;
                    makeThemFriends(userName1, userName2);
                }
                break;
            case 3:
                {
                    string userName1, userName2;
                    cout << "Enter first username: ";
                    cin >> userName1;
                    cout << "Enter second username: ";
                    cin >> userName2;
                    unfriend(userName1, userName2);
                }
                break;
            case 4:
                {
                    string sender, receiver;
                    cout << "Enter sender username: ";
                    cin >> sender;
                    cout << "Enter receiver username: ";
                    cin >> receiver;
                    cout << "Enter message content: ";
                    cin.ignore();
                    getline(cin, content);
                    sendMessage(sender, receiver, content);
                }
                break;
            case 5:
                cout << "Enter group name: ";
                cin >> groupName;
                if (mapGroups.find(groupName) == mapGroups.end()) {
                    mapGroups[groupName] = SocialGroup(groupName);
                } else {
                    cout << "Group already exists!" << endl;
                }
                break;
            case 6:
                cout << "Enter group name: ";
                cin >> groupName;
                if (mapGroups.find(groupName) != mapGroups.end()) {
                    cout << "Enter username to add: ";
                    cin >> userName;
                    mapGroups[groupName].addMember(userName);
                } else {
                    cout << "Group does not exist!" << endl;
                }
                break;
            case 7:
                cout << "Enter group name: ";
                cin >> groupName;
                if (mapGroups.find(groupName) != mapGroups.end()) {
                    cout << "Enter sender username: ";
                    cin >> userName;
                    cout << "Enter message content: ";
                    cin.ignore();
                    getline(cin, content);
                    mapGroups[groupName].addMessage(userName, content);
                } else {
                    cout << "Group does not exist!" << endl;
                }
                break;
            case 8: // Remove Member from Group
                cout << "Enter group name: ";
                cin >> groupName;
                if (mapGroups.find(groupName) != mapGroups.end()) {
                    cout << "Enter username to remove: ";
                    cin >> userName;
                    mapGroups[groupName].removeMember(userName);
                } else {
                    cout << "Group does not exist!" << endl;
                }
                break;
            case 9:
                displayAllUsers();
                break;
            case 10:
                displayAllFriendships();
                break;
            case 11:
                cout << "Enter group name: ";
                cin >> groupName;
                if (mapGroups.find(groupName) != mapGroups.end()) {
                    mapGroups[groupName].displayGroupInfo();
                } else {
                    cout << "Group does not exist!" << endl;
                }
                break;
            case 12:
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
