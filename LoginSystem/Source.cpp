#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

const string DBUSERS = "registeredUsers.txt";

ifstream loginFile;
ofstream updatedData;

struct login
{
    string username;
    string password;
    double balance;
};

void readFromFile(ofstream &newData, ifstream &file, vector<login> &x);
void menuScreen(ofstream &newData, ifstream &file, vector<login> &x, bool loggedIn);
void updateUserInfo(ofstream &newData, vector<login>& x, int userNumber);
void registerScreen(ofstream &newData, ifstream &file, vector<login>& x, bool loggedIn);
void loginScreen(vector<login> x, bool &loggedIn, int &userNumber);
void loggedInMenu(ofstream &newData, ifstream &file, vector<login>& x, int userNumber);
int deposit(vector<login>& x, int userNumber, double userAmount);

int main()
{
    bool loggedIn = false;

    vector<login> loginData;
    readFromFile(updatedData, loginFile, loginData);
    menuScreen(updatedData, loginFile, loginData, loggedIn);


    return 0;
}


//Reads and opens same file. This allows program to update the same file by adding new registered users without creating a new file.
void readFromFile(ofstream &newData, ifstream &file, vector<login> &x)
{
    istringstream iss;
    login temp;
    string username;
    string password;
    string tempBalance;
    double balance;

    file.open(DBUSERS);
    newData.open("registeredUsers.txt", fstream::app);
    while (!file.eof())
    {
        getline(file, username, ' ');
        getline(file, password, ' ');
        getline(file, tempBalance);
        iss.clear();
        iss.str(tempBalance);
        iss >> balance;

        temp.username = username;
        temp.password = password;
        temp.balance = balance;

        x.push_back(temp);
    }


}

//Menu screen displaying 3 options
void menuScreen(ofstream &newData, ifstream &file, vector<login> &x, bool loggedIn)
{
    int choice;
    int userNumber;
    do
    {
        cout << "1.) Register" << endl;
        cout << "2.) Login" << endl;
        cout << "3.) Exit" << endl;
        cin >> choice;



        switch (choice)
        {
        case 1:
            registerScreen(newData, file, x, loggedIn);
            break;
        case 2:
            loginScreen(x, loggedIn, userNumber);
            loggedInMenu(newData, file, x, userNumber);
            break;
        case 3:
            cout << "Thank you for using the program, Goodbye!" << endl;
            file.close();
            newData.close();
            break;
        default:
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Try using numbers 1-3" << endl;
            }

            break;

        }
    } while (choice != 3);



}

//Allows users to register for a new username and password that they desired (Only thing that needs to be added would be "Username is already taken")
void registerScreen(ofstream &newData, ifstream &file, vector<login>& x, bool loggedIn)
{

    int choice;
    string newUser, newPass;
    login temp;
    bool userTaken = true;



    do
    {
        cout << "Enter a new username: ";
        cin >> newUser;


        cout << "Enter a new password: ";
        cin >> newPass;

        for (int i = 0; i < x.size(); i++)
        {
            if (newUser == x[i].username)
            {
                cout << "Username has already been taken" << endl;
            } else {
                userTaken = false;
            }
        }
    } while (userTaken == true);



    temp.username = newUser;
    temp.password = newPass;
    temp.balance = 0;


    if (newData.is_open())
        newData << newUser << " " << newPass << " " << temp.balance << endl;

    x.push_back(temp);

    cout << "Account registered." << endl;



}

void updateUserInfo(ofstream &newData, vector<login>& x, int userNumber)
{
    if (newData.is_open())
    {
        newData << x[userNumber].username << " " << x[userNumber].password << " " << x[userNumber].balance << endl;
    }
}
//If user has successfully registered, this function allows them to login even if they have exited the program.
void loginScreen(vector<login> x, bool &loggedIn, int &userNumber)
{
    string username;
    string password;


    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    loggedIn = true;



    while (loggedIn)
    {
        for (int i = 0; i < x.size(); i++)
        {
            if (username == x[i].username && password == x[i].password)
            {
                cout << "Welcome, " << username << "!" << endl;
                loggedIn = false;
                userNumber = i;
                break;
            }



        }
        if (loggedIn == true)
        {
            cout << "Invalid username or password, try again..." << endl;
            loginScreen(x, loggedIn, userNumber);
        }



    }




}


void loggedInMenu(ofstream &newData, ifstream &file, vector<login>& x, int userNumber)
{
    int choice;
    double userAmount;


    do
    {
        cout << "Account balance: " << x[userNumber].balance << endl;
        cout << "1.) Deposit" << endl;
        cout << "2.) Withdraw" << endl;
        cout << "3.) sign out of " << x[userNumber].username << endl;

        cin >> choice;


        switch (choice)
        {
        case 1:
            cout << "Enter the amount of money you want to deposit on your account: ";
            cin >> userAmount;
            x[userNumber].balance = deposit(x, userNumber, userAmount);
            updateUserInfo(newData, x, userNumber);
            break;
        case 2:
            break;
        case 3:
            cout << "You've succesfully been signed out of " << x[userNumber].username << endl;
        default:
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Try using numbers 1-3" << endl;
            }
        }
    } while (choice != 3);





}


int deposit(vector<login>& x, int userNumber, double userAmount)
{

    double newBalance;


    newBalance = x[userNumber].balance + userAmount;

    return newBalance;

}
