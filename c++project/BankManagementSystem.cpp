/*

 It is a user interactive code Program and class to represent a bank account,
 *where following details can be maintained: Depositor name, account
 number type of account, balance amount in the account.
 Also, the following
 set of operations/actions should be provided: assign initial balance, deposit an amount, withdraw amount(make sure
 you check the balance), and display name & balance on demand
 
 Owner : Roshan Prakash
 Date  : 26/10/2021
 
 */

#include <iostream>
#include <cstring>
#include <limits.h>
#include <math.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>
using namespace std;

// Maximum number of Customer Data that can be entered at one time
#define size 40

// Declaration of a Class  Bank Employee

class Bank
{
private:
    // all information
    long int accountNo_;
    char *name_;
    char *accountType_;
    char *address_;
    double bal;
    int password_;

    // For make count Register
    static int counter;
    int registerNo;

    int birth_date_, birth_month_, birth_year_;

public:
    Bank()
    {
        accountNo_ = 0;
        name_ = NULL;
        accountType_ = NULL;
        address_ = NULL;
        bal = 0.0;
        password_ = 0;
        registerNo = counter;
        counter++;
    }

    //  Take data from the user
    void feedData();

    // For depositing the amount and printing net balance
    void deposit();

    // For withdrawal of the amount and printing net balance
    void withdraw();

    // Display Account Number
    void accDisplay();

    // Display the data on console
    void display();

    // Display all customer bank account no and name
    void displayAccName();

    // Delete the existing Customer
    void deleteCustomer();

    // Print record number, account number related to an account holder Emergency only when customer forgot the user name and password)
    friend void displayRecordNo(Bank B[], size_t i);

    // Display the data for Customer in file
    friend void display_Customer(Bank B[], size_t i);

    // Display the data for Employee in file
    friend void display_Employee(Bank B[], size_t i);

    // friend function to find valid customer
    // it is used to  print all customer data
    friend void findCustomer(Bank BCus[], size_t i);
};

// For static variable for register no
int Bank::counter = 1;

void Bank::feedData()
{
    char ch[20], ch2[10], address[50];

    cin.ignore();
    cout << "\nEnter the name of the person : " << endl;
    cin.getline(ch, 20);
    name_ = new char[strlen(ch) + 1];
    strcpy(name_, ch);

    cout << "\nEnter the Account No : ";
    cin >> accountNo_;

    cout << "\n Account Type : "
         << "Savings or "
         << "Current Account" << endl;
    cin.ignore();
    cin.getline(ch2, 10);
    accountType_ = new char[strlen(ch2) + 1];
    strcpy(accountType_, ch);

    cout << "\nEnter the Address of the person : " << name_ << endl;
    cin.getline(address, 50);
    address_ = new char[strlen(address) + 1];
    strcpy(address_, address);

    cout << "\nEnter the Balance : " << endl;
    cin >> bal;

    cout << "\nSet 4 digit pin for the user : " << name_ << endl;
    cin >> password_;
}
// void Dispaly all customer bank account no and name
void Bank::displayAccName()
{
    cout.setf(ios::left, ios::adjustfield);
    cout << "Register No(Sl. No.)\t";
    cout << "Name";
    cout << "\t\t";
    cout << "ACCOUNT NO.";
    cout << "\t\t";
    cout << "Balance";
    cout << endl;

    cout << this->registerNo;
    cout << "\t\t\t";
    cout << this->name_;
    cout << "\t\t";
    cout << this->accountNo_;
    cout << "\t\t";
    cout << this->bal;
    cout << endl;

    return;
}

void Bank::deposit() // depositing an amount
{
    int damt1;
    cout << "\n Enter the Deposit Amount = ";
    cin >> damt1;
    this->bal += damt1;
    return;
}

void Bank::withdraw() // withdrawing an amount
{
    int wamt1;
    cout << "\nEnter Withdraw Amount : " << endl;
    cin >> wamt1;
    if (wamt1 > bal)
        cout << "\nCannot Withdraw Amount" << endl;
    this->bal -= wamt1;
    return;
}

void Bank::display() // displaying the details
{
    cout << "\n\n";
    cout.setf(ios::left, ios::adjustfield);
    cout << "Register No(Sl. No.)\t ";
    cout << "Name";
    cout << "\t ";
    cout << "ACCOUNT NO.";
    cout << "\t ";
    cout << "Account Type";
    cout << "\t";
    cout << "Balance ";
    cout << "\t";
    cout << "Address ";
    cout << endl;

    // Print the required details of the customer
    cout << this->registerNo;
    cout << "\t\t";
    cout << this->name_;
    cout << "\t\t";
    cout << this->accountNo_;
    cout << "\t\t";
    cout << this->accountType_;
    cout << "\t\t";
    cout << this->bal;
    cout << "\t\t";
    cout << this->address_;
    cout << endl;
}

void display_Customer(Bank B[], size_t i)
{

    ofstream fwrite("CustomerDataFile", ios::out);

    for (int customerCount = 0; customerCount < i; customerCount++)
    {
        fwrite.write((char *)&B[customerCount], sizeof(B[customerCount])); // write the object in binary format
    }
    fwrite.close();

    return;
}

void displayRecordNo(Bank B[], size_t i)
{
    long int acc = 0;
    cout << "\nPlease Enter the Accout No. " << endl;
    cin >> acc;
    ifstream fread("CustomerDataFile");

    while (fread)
    {
        Bank s;                            // the default object is created
        fread.read((char *)&s, sizeof(s)); // the information is being red from the file object wise
                                           // after reading from file the member function of the object is being called.
        cout << endl;
        if (s.accountNo_ == acc)
        {
            s.display();
            break;
        }
    }
    fread.close();
}

void Bank::accDisplay()
{
    cout.setf(ios::left, ios::adjustfield);
    cout.width(20);
    cout << "ACCOUNT NO.";
    cout.width(20);
    cout << endl;
    cout.width(20);
    cout << this->accountNo_;
    cout << endl;
    cout.width(20);
}
// Delete the existing Customer
void Bank::deleteCustomer()
{
    delete this->name_;
    accountNo_ = 0;
    name_ = NULL;
    accountType_ = NULL;
    address_ = NULL;
    bal = 0.0;
    password_ = 0;
    return;
}
// Customer Specific
void findCustomer(Bank BCus[], size_t i)
{
    if (i > 0)
    {
        int pass{0}, l_temp{0};
        cout << "\nPlease Enter Details: \n";
        cout << endl;

        char ch4[20], ch3[10];
        cin.ignore();
        cout << "Enter the UserName : " << endl;
        cin.getline(ch4, 20);

        size_t choice{0}, i{0}, prev{0};
        cout << "Please enter your 4 digit Password : " << endl;
        cin >> pass;

        ifstream fread("CustomerDataFile");

        while (fread)
        {
            Bank s;
            fread.read((char *)&s, sizeof(s));
            cout << endl;
            if ((strcmp(s.name_, ch4) == 0) && (s.password_ == pass))
            {
                l_temp = s.registerNo - 1;

                while (1)
                {
                    cout     << endl;
                    cout     << s.name_ << endl;
                    cout     << "\n1. View the Balance of the account\n";
                    cout     << "\n2. Deposit an amount\n";
                    cout     << "\n3. Withdraw an amount\n";
                    cout     << "\n4. View account summary\n";
                    cout     << "\n5. Delete data of the current customer\n";
                    cout     << "\n6. EXIT From this page \n";
                    cout     << "\n Please enter your choice" << endl;
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                        cout << "Your Balance is: " << BCus[l_temp].bal << endl;
                        display_Customer(BCus, i);
                        break;
                    case 2:
                        BCus[l_temp].deposit();
                        display_Customer(BCus, i);
                        break;
                    case 3:
                        BCus[l_temp].withdraw();
                        display_Customer(BCus, i);
                        break;
                    case 4:
                        BCus[l_temp].display();
                        display_Customer(BCus, i);
                        break;
                    case 5:
                        BCus[l_temp].deleteCustomer();
                        // display_Customer(BCus, i);
                        cout << "\nThank you and visit again " << endl;
                        exit(0);
                    case 6:
                        cout << "\nThank you and visit again " << endl;
                        exit(0);
                        break;
                    default:
                        cout << "\nError : Invalid Choice " << endl;
                        break;
                    }
                }
            }
        }
        fread.close();
    }

    else
    {
        cout << "No Entry in Bank Data, Please tell Bank Employee to make a entry" << endl;
        return;
    }

    return;
}

int main()
{
    size_t choice{0}, i{0}, prev{0};

    Bank B[size];

    while (1)
    {

        cout << endl;
        cout << "\n\t\tMENU\n";
        cout << "\n1. Open a new bank account for the customer\n";
        cout << "\n2. Display the account number of the last entry\n";
        cout << "\n3. See/Edit/Delete Information For an Exiting Customer\n";
        cout << "\n4. Display the details of all account holders\n";
        cout << "\n5. Print record no. from account number  related to an account holder\n";
        cout << "\n6. EXIT";
        cout << "\n Please enter your choice : " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            B[i].feedData();
            prev = i;
            i++;
            display_Customer(B, i);
            break;
        case 2:
            B[prev].accDisplay();
            break;
        case 3:
            findCustomer(B, i);
            break;
        case 4:
            for (size_t t = 0; t < i; t++)
            {
                B[t].displayAccName();
            }
            break;
        case 5:
            displayRecordNo(B, i);
            break;
        case 6:
            cout << "\nThank you and visit again " << endl;
            exit(0);

        default:
            cout << "\nError : Invalid Choice" << endl;
            break;
        }
    }

    return 0;
}