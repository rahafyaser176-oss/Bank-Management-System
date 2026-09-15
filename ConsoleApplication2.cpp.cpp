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

stinfo ConvertLineToRecord(string Line)
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
            info = ConvertLineToRecord(line);
            vClients.push_back(info);
        }
        myfile.close();
    }
    return vClients;
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
    cout << "[7] Exit." << endl;
    cout << "=========================================================" << endl;
    cout << "What do you want to do? [1 to 7 ] ?" << endl;

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
    char answer ;
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
    else if(!Found)
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
    char answer ;
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

void   Transactions(vector<stinfo>& vClients)
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
    } while ( number != 4);
}

void StartBankSystem(vector<stinfo>& vClients)
{
    int choice;
    do 
    {
        choice = ShowMainMenu();
        switch (choice)
        {
        case 1:
            ShowAllClients(vClients);
            break;

        case 2:
            AddNewClient(vClients);
            break;

        case 3:
            DeleteClient(vClients);
            break;

        case 4:
            UpdateClientByAccountNumber(vClients);
            break;

        case 5:
            FindClient(vClients);
            break;

        case 6 :
            Transactions(vClients);
            break;

        case 7:
            break;

        default:
            cout << "Invalid choice, please choose from 1 to 7.\n";
            break;
        }
    } while (choice != 7);
}

int main()
{
    vector <stinfo> vClients = LoadClientsDataFromFile("myfile.text");
   
    StartBankSystem(vClients);


    system("pause>0");
}
