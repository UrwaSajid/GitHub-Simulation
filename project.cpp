#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <list>


using namespace std;


unordered_map<string, string> users;


struct User
{
    string username;
    string password;
    list<string> repositories;
    list<string> followers;
    User *left;
    User *right;
    int height;


} *root;


void loadUsers()
{
    ifstream file;
    file.open("login.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string username, password, email;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        users[username] = password;
    }
    file.close();
}


class UserAccount
{
    string username;
    string password;
    string email;


public:
    UserAccount(string username, string password, string email)
    {
        this->username = username;
        this->password = password;
        this->email = email;
    }


    UserAccount()
    {
        this->username = "";
        this->password = "";
        this->email = "";
    }


    void setUser(string username, string password, string email)
    {
        this->username = username;
        this->password = password;
        this->email = email;
    }


    void saveUser()
    {
        users[username] = password;
        ofstream file;
        file.open("login.csv", ios::app);
        file << username << "," << password << "," << email << endl;
        file.close();
        ofstream file2;
        file2.open(username + ".csv");
        file2.close();
    }


    bool checkUser(string username, string password)
    {
        if (users.find(username) != users.end())
        {
            if (users[username] == password)
            {
                return true;
            }
        }
        return false;
    }


    void removeUser(string username)
    {
        users.erase(username);
        remove((username + ".csv").c_str());
        ofstream file;
        file.open("login.csv");
        for (auto it = users.begin(); it != users.end(); it++)
        {
            file << it->first << "," << it->second << endl;
        }
        file.close();
    }
};


class AVL
{
public:
    int height(User *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }


    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }


    User *newNode(string username, string password)
    {
        User *user = new User();
        user->username = username;
        user->password = password;
        user->left = NULL;
        user->right = NULL;
        user->height = 1;
        return (user);
    }


    User *rightRotate(User *y)
    {
        User *x = y->left;
        User *T2 = x->right;


        x->right = y;
        y->left = T2;


        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;


        return x;
    }


    User *leftRotate(User *x)
    {
        User *y = x->right;
        User *T2 = y->left;


        y->left = x;
        x->right = T2;


        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;


        return y;
    }


    int getBalance(User *N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }


    User *insert(User *node, string username, string password)
    {
        if (node == NULL)
            return (newNode(username, password));


        if (username < node->username)
            node->left = insert(node->left, username, password);
        else if (username > node->username)
            node->right = insert(node->right, username, password);
        else
            return node;


        node->height = 1 + max(height(node->left), height(node->right));


        int balance = getBalance(node);


        if (balance > 1 && username < node->left->username)
            return rightRotate(node);


        if (balance < -1 && username > node->right->username)
            return leftRotate(node);


        if (balance > 1 && username > node->left->username)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }


        if (balance < -1 && username < node->right->username)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }


        return node;
    }


    User *deleteUser(User *root, string username)
    {
        if (root == NULL)
            return root;


        if (username < root->username)
            root->left = deleteUser(root->left, username);


        else if (username > root->username)
            root->right = deleteUser(root->right, username);


        else
        {
            if ((root->left == NULL) || (root->right == NULL))
            {
                User *temp = root->left ? root->left : root->right;


                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                free(temp);
            }
            else
            {
                User *temp = root->right;
                while (temp->left != NULL)
                    temp = temp->left;


                root->username = temp->username;
                root->right = deleteUser(root->right, temp->username);
            }
        }


        if (root == NULL)
            return root;


        root->height = 1 + max(height(root->left), height(root->right));


        int balance = getBalance(root);


        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);


        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }


        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);


        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }


        return root;
    }


    User *search(User *root, string username)
    {
        if (root == NULL || root->username == username)
            return root;


        if (root->username < username)
            return search(root->right, username);


        return search(root->left, username);
    }


    void addRepository(User *root, string username, string repository)
    {
        User *user = search(root, username);
        user->repositories.push_back(repository);
        ofstream file;
        file.open(username + ".csv", ios::app);
        file << repository << "," << endl;
    }


    void removeRepository(User *root, string username, string repository)
    {
        User *user = search(root, username);
        user->repositories.remove(repository);
        ofstream file;
        file.open(username + ".csv");
        for (auto it = user->repositories.begin(); it != user->repositories.end(); it++)
        {
            file << *it << "," << endl;
        }
    }


    void viewRepositories(User *root, string username)
    {
        User *user = search(root, username);
        for (auto it = user->repositories.begin(); it != user->repositories.end(); it++)
        {
            cout << *it << endl;
        }
    }


    void viewFollowers(User *root, string username)
    {
        User *user = search(root, username);
        for (auto it = user->followers.begin(); it != user->followers.end(); it++)
        {
            cout << *it << endl;
        }
    }


    void addFollower(User *root, string username, string follower)
    {
        User *user = search(root, username);
        ifstream file;
        bool exists = false;
        file.open("login.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, password, email;
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, email, ',');
            if (username == follower)
            {


                exists = true;
                break;
            }
            else
            {
                exists = false;
                continue;
            }
        }


        if (exists)
        {
            user->followers.push_back(follower);
        }
        else
        {
            cout << "User does not exist" << endl;
            return;
        }
    }


    void removeFollower(User *root, string username, string follower)
    {
        User *user = search(root, username);
        user->followers.remove(follower);
    }


    void veiwUser(User *root, string username)
    {
        User *user = search(root, username);
        cout << "Username: " << user->username << endl;
        cout << "Repositories: " << endl;
        for (auto it = user->repositories.begin(); it != user->repositories.end(); it++)
        {
            cout << *it << endl;
        }
        cout << "Followers: " << endl;
        for (auto it = user->followers.begin(); it != user->followers.end(); it++)
        {
            cout << *it << endl;
        }
    }


    void commit(User *root, string username, string repository, string message)
    {
        User *user = search(root, username);
        ifstream fileIn;
        fileIn.open(username + ".csv");
        string line;
        vector<string> lines;
        bool exists = false;
    
        while (getline(fileIn, line))
        {
            stringstream ss(line);
            string repo, commit;
            getline(ss, repo, ',');
            getline(ss, commit, ',');
    
            if (repo == repository)
            {
                exists = true;
                line = repo + "," + message; 
            }
    
            lines.push_back(line);
        }
    
        fileIn.close();
    
        if (exists)
        {
            ofstream fileOut;
            fileOut.open(username + ".csv");
    
            for (const auto& line : lines) {
                fileOut << line << "\n";
            }
        }
        else
        {
            cout << "Repository does not exist" << endl;
        }
    }


    void forkrepo(User *root, string username, string targetUsername, string repository)
    {
        User *user = search(root, username);
        User *targetUser = search(root, targetUsername);
        ifstream file;
        bool exists = false;
        file.open(username + ".csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string repo, commit;
            getline(ss, repo, ',');
            getline(ss, commit, ',');
            if (repo == repository)
            {
                exists = true;
                break;
            }
            else
            {
                exists = false;
                continue;
            }
        }


        if (exists)
        {
            targetUser->repositories.push_back(repository);
            ofstream file;
            file.open(targetUsername + ".csv", ios::app);
            file << repository << "," << endl;
        }
        else
        {
            cout << "Repository does not exist" << endl;
            return;
        }
    }
};


AVL github;
void loadTree()
{
    ifstream file;
    file.open("login.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string username, password, email;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        root = github.insert(root, username, password);
    }
    file.close();
}


void loadrepos()
{
    ifstream file;
    file.open("login.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string username, password, email;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        ifstream file2;
        file2.open(username + ".csv");
        string line2;
        while (getline(file2, line2))
        {
            stringstream ss2(line2);
            string repo, commit;
            getline(ss2, repo, ',');
            getline(ss2, commit, ',');
            github.addRepository(root, username, repo);
        }
        file2.close();
    }
    file.close();
}


void printcommands()
{
    cout << "login" << endl;
    cout << "adduser" << endl;
    cout << "removeuser" << endl;
    cout << "addrepository" << endl;
    cout << "removerepository" << endl;
    cout << "viewrepositories" << endl;
    cout << "viewfollowers" << endl;
    cout << "addfollower" << endl;
    cout << "removefollower" << endl;
    cout << "viewuser" << endl;
    cout << "commit" << endl;
    cout << "forkrepo" << endl;
    cout << "logout" << endl;
    cout << "exit" << endl;
}


int main()
{
    loadUsers();
    loadTree();
    loadrepos();
    cout << "\t\t\t\t\t\t\t\n\n\n\n\nWelcome to Github" << endl;
    cout << "\t\t\t\t\t\t\t\n\n\n\n\nOmima Shah and Urwa Sajid" << endl;
    system("pause");
    printcommands();
    system("pause");
    system("cls");
    UserAccount user;
    string username, password, email;
    string command;
    while (true)
    {
        cout << "Enter command: ";
        cin >> command;
        if (command == "login")
        {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (user.checkUser(username, password))
            {
                cout << "Login successful" << endl;
                while (true)
                {
                    cout << "Enter command: ";
                    cin >> command;
                    if (command == "adduser")
                    {
                        cout << "Enter username: ";
                        cin >> username;
                        cout << "Enter password: ";
                        cin >> password;
                        cout << "Enter email: ";
                        cin >> email;
                        user.setUser(username, password, email);
                        user.saveUser();
                    }
                    else if (command == "removeuser")
                    {
                        cout << "Enter username: ";
                        cin >> username;
                        user.removeUser(username);
                    }
                    else if (command == "addrepository")
                    {
                        cout << "Enter repository name: ";
                        string repository;
                        cin >> repository;
                        github.addRepository(root, username, repository);
                    }
                    else if (command == "removerepository")
                    {
                        cout << "Enter repository name: ";
                        string repository;
                        cin >> repository;
                        github.removeRepository(root, username, repository);
                    }
                    else if (command == "viewrepositories")
                    {
                        github.viewRepositories(root, username);
                    }
                    else if (command == "viewfollowers")
                    {
                        github.viewFollowers(root, username);
                    }
                    else if (command == "addfollower")
                    {
                        cout << "Enter follower username: ";
                        string follower;
                        cin >> follower;
                        github.addFollower(root, username, follower);
                    }
                    else if (command == "removefollower")
                    {
                        cout << "Enter follower username: ";
                        string follower;
                        cin >> follower;
                        github.removeFollower(root, username, follower);
                    }
                    else if (command == "viewuser")
                    {
                        github.veiwUser(root, username);
                    }
                    else if (command == "commit")
                    {
                        cout << "Target username:";
                        string targetUsername;
                        cin >> targetUsername;
                        cout << "Enter repository name: ";
                        string repository;
                        cin >> repository;
                        cout << "Enter commit message: ";
                        string message;
                        cin >> message;
                        github.commit(root, targetUsername, repository, message);
                    }
                    else if (command == "forkrepo")
                    {
                        cout << "Enter target username: ";
                        string targetUsername;
                        cin >> targetUsername;
                        cout << "Enter repository name: ";
                        string repository;
                        cin >> repository;
                        github.forkrepo(root, username, targetUsername, repository);
                    }
                    else if (command == "logout")
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "Login failed" << endl;
            }
        }
        else if (command == "exit")
        {
            break;
        }
    }


    return 0;
}

