#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
struct stinfo
{
    string accountnumber;
    string pincode;
    string name;
    string phone;
    double accountbalance = 0;
};

struct stuserinfo 
{
    string username;
    string password;
    int permissions;
};

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;

    while (S1.length() > 0)
    {
        size_t pos = S1.find(Delim);
        string word = S1.substr(0, pos);
        vString.push_back(word);
        S1.erase(0, pos + Delim.length());

    }
    return vString;
}

stinfo ConvertLineToClientRecord(string Line)
{
    stinfo info;
    vector<string> vString = SplitString(Line, "#//#");

    info.accountnumber = vString[0];
    info.pincode = vString[1];
    info.name = vString[2];
    info.phone = vString[3];
    info.accountbalance = stod(vString[4]);

    return info;
}

stuserinfo ConvertLineToUserRecord(string Line)
{
    stuserinfo userinfo;
    vector<string> vString = SplitString(Line, "#//#");

    userinfo.username = vString[0];
    userinfo.password = vString[1];
    userinfo.permissions = stoi(vString[2]);

    return userinfo;
}

vector<stinfo> LoadClientsDataFromFile(string FileName)
{
    vector<stinfo> vClients;
    fstream myfile;

    myfile.open(FileName, ios::in);

    if (myfile.is_open())
    {
        string line;
        stinfo info;
        while (getline(myfile, line))
        {
            info = ConvertLineToClientRecord(line);
            vClients.push_back(info);
        }
        myfile.close();
    }
    return vClients;
}

vector<stuserinfo> LoadUsersDataFromFile(string FileName)
{
    vector<stuserinfo> vUsers;
    fstream myfile;

    myfile.open(FileName, ios::in);

    if (myfile.is_open())
    {
        string line;
        stuserinfo userinfo;

        while (getline(myfile, line))
        {
            userinfo = ConvertLineToUserRecord(line);
            vUsers.push_back(userinfo);
        }
        myfile.close();
    }
    return vUsers;
}

void SaveClientsDataToFile(string FileName, vector<stinfo> vClients)
{
    fstream myfile;
    myfile.open(FileName, ios::out);

    if (myfile.is_open())
    {
        for (stinfo info : vClients)
        {
            myfile << info.accountnumber << "#//#"
                << info.pincode << "#//#"
                << info.name << "#//#"
                << info.phone << "#//#"
                << info.accountbalance << endl;
        }

        myfile.close();
    }
}

void SaveUsersDataToFile(string FileName, vector<stuserinfo> vUsers)
{
    fstream myfile;
    myfile.open(FileName, ios::out);

    if (myfile.is_open())
    {
        for (stuserinfo userinfo : vUsers)
        {
            myfile << userinfo.username << "#//#"
                << userinfo.password << "#//#"
                << userinfo.permissions << endl;
        }

        myfile.close();
    }
}

bool Login(vector<stuserinfo> vUsers , stuserinfo& LoggedInUser)
{
    string username;
    string password;

    cout << "Enter Username?" << endl;
    cin >> username;

    cout << "Enter Password?" << endl;
    cin >> password;

    for (stuserinfo userinfo : vUsers)
    {
        if (userinfo.username == username &&
            userinfo.password == password)
        {
            LoggedInUser = userinfo;
            return true;
        }
    }

    return false;
}

int ShowMainMenu()
{
    int number;
    cout << "=========================================================" << endl;
    cout << "                     Main Menu                           " << endl;
    cout << "========================================================= \n\n";
    cout << "[1] Show Client List." << endl;
    cout << "[2] Add New Client." << endl;
    cout << "[3] Delete Client." << endl;
    cout << "[4] Update Client Info." << endl;
    cout << "[5] Find Client." << endl;
    cout << "[6] Transactions." << endl;
    cout << "[7] Manage Users." << endl;
    cout << "[8] Logout." << endl;
    cout << "=========================================================" << endl;
    cout << "What do you want to do? [1 to 8 ] ?" << endl;

    cin >> number;
    return  number;
}

void PrintClientintable(stinfo info)
{
    cout << "| " << setw(15) << left << info.accountnumber;
    cout << "| " << setw(10) << left << info.pincode;
    cout << "| " << setw(40) << left << info.name;
    cout << "| " << setw(12) << left << info.phone;
    cout << "| " << setw(12) << left << info.accountbalance;
}

void PrintUserintable(stuserinfo userinfo)
{
    cout << "| " << setw(15) << left << userinfo.username;
    cout << "| " << setw(10) << left << userinfo.password;
    cout << "| " << setw(40) << left << userinfo.permissions;
}

void PrintClientRecord(stinfo info)
{
    cout << "The following are the client details:" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Account Number :" << info.accountnumber << endl;
    cout << "Pin Code       :" << info.pincode << endl;
    cout << "Name           :" << info.name << endl;
    cout << "Phone          : " << info.phone << endl;
    cout << "Account Balance:" << info.accountbalance << endl;
    cout << "------------------------------------------------------" << endl;
}

void ShowAllClients(vector <stinfo> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stinfo info : vClients)
    {
        PrintClientintable(info);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

stinfo ReadClientInfo()
{
    stinfo info;

    cout << "Enter Pin Code: ";
    cin >> info.pincode;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, info.name);

    cout << "Enter Phone: ";
    cin >> info.phone;

    cout << "Enter Account Balance: ";
    cin >> info.accountbalance;

    return info;
}

void AddNewClient(vector<stinfo>& vClients)
{
    string accountnumber;
    char choice = 'y';
    while (choice == 'y' || choice == 'Y')
    {
        cout << "------------------------------------------------------" << endl;
        cout << "              Add New Clients Screen                  " << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Enter Account Number? ";
        cin >> accountnumber;

        bool Found = false;

        for (vector<stinfo>::iterator iter = vClients.begin();
            iter != vClients.end(); iter++)
        {
            if (iter->accountnumber == accountnumber)
            {
                Found = true;
                break;
            }
        }
        while (Found)
        {
            cout << "Client with [" << accountnumber
                << "] already exists, Enter another Account Number? ";
            cin >> accountnumber;

            Found = false;

            for (vector<stinfo>::iterator iter = vClients.begin();
                iter != vClients.end(); iter++)
            {
                if (iter->accountnumber == accountnumber)
                {
                    Found = true;
                    break;
                }
            }
        }
        stinfo NewClient = ReadClientInfo();
        NewClient.accountnumber = accountnumber;

        vClients.push_back(NewClient);

        SaveClientsDataToFile("myfile.text", vClients);
        cout << "Client Added Successfully, do you want to add more clients? Y/N? ";
        cin >> choice;
    }
}

void DeleteClient(vector<stinfo>& vClients)
{
    char answer;
    string accountnumber;
    cout << "------------------------------------------------------" << endl;
    cout << "              Delete Client Screen                  " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Please Enter Account Number?" << endl;
    cin >> accountnumber;

    bool Deleted = false;
    bool Found = false;

    for (vector<stinfo>::iterator iter = vClients.begin(); iter != vClients.end(); iter++)
    {
        if (iter->accountnumber == accountnumber)
        {
            Found = true;

            PrintClientRecord(*iter);

            cout << "Are You sure you want delete this client? Y/N?" << endl;
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                vClients.erase(iter);

                SaveClientsDataToFile("myfile.text", vClients);
                Deleted = true;
                break;
            }
            else if (answer == 'n' || answer == 'N')
            {
                cout << "\nPress any key to continue...";
                system("pause>0");
                break;
            }
        }
    }

    if (Deleted)
    {
        cout << "Client Deleted Successfully" << endl;
    }
    else if (!Found)
    {
        cout << "Client with Account Number (" << accountnumber << ") is Not Found!" << endl;

    }
}

void UpdateClientByAccountNumber(vector<stinfo>& vClients)
{
    bool updated = false;
    bool Found = false;
    string accountnumber;
    char answer;

    cout << "------------------------------------------------------" << endl;
    cout << "             Update Client Info Screen                " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Please enter Account Number? " << endl;
    cin >> accountnumber;

    for (vector<stinfo>::iterator iter = vClients.begin(); iter != vClients.end(); iter++)
    {
        if (iter->accountnumber == accountnumber)
        {
            PrintClientRecord(*iter);
            Found = true;

            cout << "Are You sure you want to update this client? Y/N?" << endl;
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                stinfo NewClient = ReadClientInfo();
                iter->pincode = NewClient.pincode;
                iter->name = NewClient.name;
                iter->phone = NewClient.phone;
                iter->accountbalance = NewClient.accountbalance;

                updated = true;
                SaveClientsDataToFile("myfile.text", vClients);
                break;
            }
            else if (answer == 'n' || answer == 'N')
            {
                updated = false;

                cout << "\nPress any key to continue...";
                system("pause>0");
                break;
            }
        }
    }
    if (updated)
    {
        cout << "Client Updated Successfully" << endl;
    }
    else if (!Found)
    {
        cout << "Client with Account Number (" << accountnumber
            << ") is Not Found!" << endl;
    }
}

void FindClient(vector<stinfo>& vClients)
{
    string accountnumber;
    bool Found = false;
    cout << "------------------------------------------------------" << endl;
    cout << "                Find Client Screen               " << endl;
    cout << "------------------------------------------------------" << endl;

    cout << "Please enter Account Number? " << endl;
    cin >> accountnumber;

    for (vector<stinfo>::iterator iter = vClients.begin(); iter != vClients.end(); iter++)
    {
        if (iter->accountnumber == accountnumber)
        {
            PrintClientRecord(*iter);
            Found = true;
            break;
        }
    }
    if (!Found)
    {
        cout << "Client with Account Number (" << accountnumber
            << ") is Not Found!" << endl;
    }
}

void Deposit(vector<stinfo>& vClients)
{
    string accountnumber;
    bool Found = false;
    double amount;
    double NewBalance;
    char answer;

    cout << "------------------------------------------------------" << endl;
    cout << "                 Deposit Screen                       " << endl;
    cout << "------------------------------------------------------" << endl;

    cout << "Please Enter AccountNumber?" << endl;
    cin >> accountnumber;

    for (vector<stinfo>::iterator iter = vClients.begin(); iter != vClients.end(); iter++)
    {
        if (iter->accountnumber == accountnumber)
        {
            PrintClientRecord(*iter);
            Found = true;

            cout << "Please enter deposit amount?" << endl;
            cin >> amount;

            cout << "Are you sure you want to deposit? Y/N? " << endl;
            cin >> answer;

            if (answer == 'y' || answer == 'Y')
            {

                NewBalance = iter->accountbalance + amount;
                iter->accountbalance = NewBalance;
                cout << "Deposit Done Successfully" << endl;
                SaveClientsDataToFile("myfile.text", vClients);

                break;
            }
        }
    }
    if (!Found)
    {
        cout << "Client with Account Number (" << accountnumber
            << ") is Not Found!" << endl;
    }
}

void Withdraw(vector<stinfo>& vClients)
{
    string accountnumber;
    double amount;
    bool Found = false;
    char answer;
    double NewBalance;
    cout << "------------------------------------------------------" << endl;
    cout << "                Withdraw Screen                       " << endl;
    cout << "------------------------------------------------------" << endl;

    cout << "Please Enter AccountNumber?" << endl;
    cin >> accountnumber;

    for (vector<stinfo>::iterator iter = vClients.begin(); iter != vClients.end(); iter++)
    {
        if (iter->accountnumber == accountnumber)
        {
            PrintClientRecord(*iter);
            Found = true;

            do {
                cout << "Please enter withdraw amount?" << endl;
                cin >> amount;

                if (amount > iter->accountbalance)
                {

                    cout << "Amount Exceeds the balance , you can withdraw up to : " <<
                        iter->accountbalance << endl;
                }

            } while (amount > iter->accountbalance);

            cout << "Are you sure you want to Withdraw? Y/N? " << endl;
            cin >> answer;

            if (answer == 'y' || answer == 'Y')
            {

                NewBalance = iter->accountbalance - amount;
                iter->accountbalance = NewBalance;
                cout << "Withdraw Done Successfully" << endl;
                SaveClientsDataToFile("myfile.text", vClients);

                break;
            }
        }
    }
    if (!Found)
    {
        cout << "Client with Account Number (" << accountnumber
            << ") is Not Found!" << endl;
    }
}

void TotalBalances(vector<stinfo>& vClients)
{
    double TotalBalance = 0;

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stinfo info : vClients)
    {
        PrintClientintable(info);
        cout << endl;

        TotalBalance += info.accountbalance;
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "\t\t\t\t\tTotal Balances = " << TotalBalance << endl;

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void  Transactions(vector<stinfo>& vClients)
{
    int number;
    cout << "------------------------------------------------------" << endl;
    cout << "                 Transactions Screen                  " << endl;
    cout << "------------------------------------------------------" << endl;

    cout << "[1] Deposit." << endl;
    cout << "[2] Withdraw." << endl;
    cout << "[3] Total Balances." << endl;
    cout << "[4] Main Menu." << endl;

    do {

        cout << "Choose What do you want to do? [1 to 4]? " << endl;
        cin >> number;
        switch (number)
        {
        case 1:
            Deposit(vClients);
            break;

        case 2:
            Withdraw(vClients);
            break;

        case 3:
            TotalBalances(vClients);
            break;

        case 4:
            break;

        default:
            cout << "Invalid choice, please choose from 1 to 4.\n";
            break;
        }
    } while (number != 4);
}

stuserinfo ReadUserInfo()
{
    stuserinfo userinfo;

    cout << "Enter Username? ";
    cin >> userinfo.username;

    cout << "Enter Password? ";
    cin >> userinfo.password;

    cout << "Do you want to give full access? y/n? ";
    char FullAccess;
    cin >> FullAccess;

    if (FullAccess == 'Y' || FullAccess == 'y')
    {
        userinfo.permissions = -1;
    }
    else
    {
        userinfo.permissions = 0;

        char Choice;

        cout << "Do you want to give access to Show Client List? y/n? ";
        cin >> Choice;
        if (Choice == 'Y' || Choice == 'y')
            userinfo.permissions += 1;

        cout << "Do you want to give access to Add New Client? y/n? ";
        cin >> Choice;
        if (Choice == 'Y' || Choice == 'y')
            userinfo.permissions += 2;

        cout << "Do you want to give access to Delete Client? y/n? ";
        cin >> Choice;
        if (Choice == 'Y' || Choice == 'y')
            userinfo.permissions += 4;

        cout << "Do you want to give access to Update Client? y/n? ";
        cin >> Choice;
        if (Choice == 'Y' || Choice == 'y')
            userinfo.permissions += 8;

        cout << "Do you want to give access to Find Client? y/n? ";
        cin >> Choice;
        if (Choice == 'Y' || Choice == 'y')
            userinfo.permissions += 16;

        cout << "Do you want to give access to Transactions? y/n? ";
        cin >> Choice;
        if (Choice == 'Y' || Choice == 'y')
            userinfo.permissions += 32;

        cout << "Do you want to give access to Manage Users? y/n? ";
        cin >> Choice;
        if (Choice == 'Y' || Choice == 'y')
            userinfo.permissions += 64;
    }

    return userinfo;
}

void Loginloop(vector <stuserinfo> vUsers, stuserinfo& LoggedInUser)
{
    cout << "----------------------------------------------------  " << endl;
    cout << "                  Login Screen                        " << endl;
    cout << "----------------------------------------------------  " << endl;


    while (!Login(vUsers , LoggedInUser))
    {
        cout << "Invalid Username / Password\n";
    }
}

void ShowAllUsers(vector <stuserinfo> vUsers)
{
    cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ")User(s).";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "UserName";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stuserinfo userinfo : vUsers)
    {
        PrintUserintable(userinfo);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

bool IsUserExist(string Username, vector<stuserinfo> vUsers)
{
    for (vector<stuserinfo>::iterator iter = vUsers.begin();
        iter != vUsers.end(); iter++)
    {
        if (Username == iter->username)
        {
            return true;
        }
    }
    return false;
}

void AddNewUser(vector<stuserinfo>& vUsers)
{
    string Username;
    string Password;
    char FullAccess;
    char AddAnother;
    char Choice;
    stuserinfo userinfo;

    do
    {
        cout << "\nAdding New User:\n\n";

        cout << "Enter Username? ";
        cin >> Username;

        while (IsUserExist(Username, vUsers))
        {
            cout << "\nUser with [" << Username
                << "] already exists, Enter another Username? ";
            cin >> Username;
        }

        cout << "Enter Password? ";
        cin >> Password;

        cout << "\nDo you want to give this User full access? y/n? ";
        cin >> FullAccess;

        if (FullAccess == 'Y' || FullAccess == 'y')
        {
            userinfo.permissions = -1;
        }
        else
        {
            userinfo.permissions = 0;

            cout << "\nDo you want to give access to :\n";

            cout << "\nShow Client List? y/n? ";
            cin >> Choice;

            if (Choice == 'Y' || Choice == 'y')
                userinfo.permissions += 1;

            cout << "\nAdd New Client? y/n? ";
            cin >> Choice;

            if (Choice == 'Y' || Choice == 'y')
                userinfo.permissions += 2;

            cout << "\nDelete Client? y/n? ";
            cin >> Choice;

            if (Choice == 'Y' || Choice == 'y')
                userinfo.permissions += 4;

            cout << "\nUpdate Client? y/n? ";
            cin >> Choice;

            if (Choice == 'Y' || Choice == 'y')
                userinfo.permissions += 8;

            cout << "\nFind Client? y/n? ";
            cin >> Choice;

            if (Choice == 'Y' || Choice == 'y')
                userinfo.permissions += 16;

            cout << "\nTransactions? y/n? ";
            cin >> Choice;

            if (Choice == 'Y' || Choice == 'y')
                userinfo.permissions += 32;

            cout << "\nManage Users? y/n? ";
            cin >> Choice;

            if (Choice == 'Y' || Choice == 'y')
                userinfo.permissions += 64;
        }

        userinfo.username = Username;
        userinfo.password = Password;

        vUsers.push_back(userinfo);

        SaveUsersDataToFile("Users.text", vUsers);

        cout << "\nUser Added Successfully, "
            << "do you want to add more Users? Y/N? ";
        cin >> AddAnother;

    } while (AddAnother == 'Y' || AddAnother == 'y');
}

void DeleteUser(vector <stuserinfo>& vUsers)
{
    char answer;
    string username;
    cout << "------------------------------------------------------" << endl;
    cout << "              Delete User Screen                  " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Please Enter Username?" << endl;
    cin >> username;

    bool Deleted = false;
    bool Found = false;

    for (vector<stuserinfo>::iterator iter = vUsers.begin(); iter != vUsers.end(); iter++)
    {
        if (iter->username == username)
        {
            Found = true;

            PrintUserintable(*iter);

            cout << "Are You sure you want delete this User? Y/N?" << endl;
            cin >> answer;

            if (answer == 'y' || answer == 'Y')
            {
                vUsers.erase(iter);

                SaveUsersDataToFile("Users.text", vUsers);
                Deleted = true;
                break;
            }
            else if (answer == 'n' || answer == 'N')
            {
                cout << "\nPress any key to continue...";
                system("pause>0");
                break;
            }
        }
    }
    if (Deleted)
    {
        cout << "User Deleted Successfully" << endl;
    }
    else if (!Found)
    {
        cout << "User with Username (" << username
            << ") is Not Found!" << endl;
    }
}

void UpdateUser(vector <stuserinfo>& vUsers)
{
    bool updated = false;
    bool Found = false;
    string username;
    char answer;

    cout << "------------------------------------------------------" << endl;
    cout << "             Update User Info Screen                " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "Please enter Username? " << endl;
    cin >> username;

    for (vector<stuserinfo>::iterator iter = vUsers.begin(); iter != vUsers.end(); iter++)
    {
        if (iter->username == username)
        {
            PrintUserintable(*iter);
            Found = true;

            cout << "Are You sure you want to update this User? Y/N?" << endl;
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                stuserinfo NewUser = ReadUserInfo();
                iter->username = NewUser.username;
                iter->password = NewUser.password;
                iter->permissions = NewUser.permissions;

                updated = true;
                SaveUsersDataToFile("Users.text", vUsers);
                break;
            }
            else if (answer == 'n' || answer == 'N')
            {
                updated = false;

                cout << "\nPress any key to continue...";
                system("pause>0");
                break;
            }
        }
    }
    if (updated)
    {
        cout << "User Updated Successfully" << endl;
    }
    else if (!Found)
    {
        cout << "User with Username (" << username
            << ") is Not Found!" << endl;
    }
}

void FindUser(vector <stuserinfo>& vUsers)
{
        string username;
        bool Found = false;
        cout << "------------------------------------------------------" << endl;
        cout << "                Find User Screen               " << endl;
        cout << "------------------------------------------------------" << endl;

        cout << "Please enter Username? " << endl;
        cin >> username;

        for (vector<stuserinfo>::iterator iter = vUsers.begin(); iter != vUsers.end(); iter++)
        {
            if (iter->username == username)
            {
                PrintUserintable(*iter);
                Found = true;
                break;
            }
        }
        if (!Found)
        {
            cout << "User with Username (" << username
                << ") is Not Found!" << endl;
        }
}

void ManageUsers(vector <stuserinfo>& vUsers)
{
    cout << "=========================================================" << endl;
    cout << "                     Manage Users Menue Screen                           " << endl;
    cout << "========================================================= \n\n";

    cout << "      [1] List Users  .\n";
    cout << "      [2] Add New User.\n";
    cout << "      [3] Delete User .\n";
    cout << "      [4] Update User .\n";
    cout << "      [5] Find User   .\n";
    cout << "      [6] Main Menue  .\n";

    cout << "========================================================= \n\n";
    int number;
    do {
        cout << "Choose What do you want to do? [1 to 6]? " << endl;
        cin >> number;
        switch (number)
        {
        case 1:
            ShowAllUsers(vUsers);
            break;

        case 2:
            AddNewUser(vUsers);
            break;

        case 3:
            DeleteUser(vUsers);
            break;

        case 4:
            UpdateUser(vUsers);
            break;

        case 5:
            FindUser(vUsers);
            break;

        case 6:
            break;

        default:
            cout << "Invalid choice, please choose from 1 to 6.\n";
            break;
        }
    } while (number != 6);
}

bool CheckAccessPermission(int UserPermissions, int Permission)
{
    if (UserPermissions == -1)
        return true;

    return (UserPermissions & Permission) == Permission;
}

void StartBankSystem(vector<stinfo>& vClients , vector<stuserinfo> vUsers)
{

    while (true)
    {
        stuserinfo LoggedInUser;
        Loginloop(vUsers, LoggedInUser);

        int choice;
        do
        {
            choice = ShowMainMenu();
            switch (choice)
            {
            case 1:
                if (CheckAccessPermission(LoggedInUser.permissions, 1))
                {
                    ShowAllClients(vClients);
                }
                else
                {
                    cout << "You don't have permission to do this.\n";
                }
                break;

            case 2:
                if (CheckAccessPermission(LoggedInUser.permissions, 2))
                {
                    AddNewClient(vClients);
                }
                else
                {
                    cout << "You don't have permission to do this.\n";
                }
                break;

            case 3:
                if (CheckAccessPermission(LoggedInUser.permissions, 4))
                {
                    DeleteClient(vClients);
                }
                else
                {
                    cout << "You don't have permission to do this.\n";
                }
                break;
          
            case 4:
                if (CheckAccessPermission(LoggedInUser.permissions, 8))
                {
                    UpdateClientByAccountNumber(vClients);
                }
                else
                {
                    cout << "You don't have permission to do this.\n";
                }
                break;

            case 5:
                if (CheckAccessPermission(LoggedInUser.permissions, 16))
                {
                    FindClient(vClients);
                }
                else
                {
                    cout << "You don't have permission to do this.\n";
                }
                break;

            case 6:
                if (CheckAccessPermission(LoggedInUser.permissions, 32))
                {
                    Transactions(vClients);
                }
                else
                {
                    cout << "You don't have permission to do this.\n";
                }
                break;

            case 7:
                if (CheckAccessPermission(LoggedInUser.permissions, 64))
                {
                    ManageUsers(vUsers);
                }
                else
                {
                    cout << "You don't have permission to do this.\n";
                }
                break;

            case 8:
                system("cls");
                break;

            default:
                cout << "Invalid choice, please choose from 1 to 8.\n";
                break;
            }
        } while (choice != 8);
    }
}

int main()
{


    vector <stinfo> vClients = LoadClientsDataFromFile("myfile.text");
    vector <stuserinfo> vUsers = LoadUsersDataFromFile("Users.text");

    StartBankSystem(vClients , vUsers);

   
    system("pause>0");
}