#include <iostream>
#include <vector>
using namespace std;

class BankAccount
{
public:
    int account_num;
    string account_holder;
    double balance;

    BankAccount() : balance(0.0) {}

    void addAccountData()
    {
        cout << "Enter Account Number: ";
        cin >> account_num;
        cout << "Enter Account Holder Name: ";
        cin >> account_holder;
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount()
    {
        cout << "Account holder: " << account_holder << endl;
        cout << "Account Number: " << account_num << endl;
        cout << "Current Balance: " << balance << endl;
    }

    virtual void deposit(double amount)
    {
        balance += amount;
        cout << "Deposit successful. New balance: " << balance << endl;
    }

    virtual void withdraw(double amount)
    {
        if (balance < amount)
        {
            cout << "Insufficient Balance." << endl;
        }
        else
        {
            balance -= amount;
            cout << "Withdrawal Successful. New Balance: " << balance << endl;
        }
    }

    virtual double calculateInterest()
    {
        return 0.0;
    }
};

class SavingsAccount : public BankAccount
{
public:
    void deposit(double amount) override
    {
        BankAccount::deposit(amount);
    }

    void withdraw(double amount) override
    {
        BankAccount::withdraw(amount);
    }

    double calculateInterest() override
    {
        double interest = balance * 0.04;
        balance += interest;
        cout << "Interest added: " << interest << endl;
        return interest;
    }
};

class CheckingAccount : public BankAccount
{
public:
    void withdraw(double amount) override
    {
        if (balance + 1000 < amount)
        {
            cout << "Withdrawal Denied: Exceeds Overdraft Limit." << endl;
        }
        else
        {
            BankAccount::withdraw(amount);
        }
    }
};

class FixedDepositAccount : public BankAccount
{
public:
    int term;
    int months_passed;

    FixedDepositAccount() : term(0), months_passed(0) {}

    void addAccountData()
    {
        BankAccount::addAccountData();
        cout << "Enter term (in months) for the Fixed Deposit: ";
        cin >> term;
    }

    void withdraw(double amount) override
    {
        if (months_passed >= term)
        {
            BankAccount::withdraw(amount);
        }
        else
        {
            cout << "Withdrawals are not allowed from Fixed Deposit Account before maturity." << endl;
        }
    }

    double calculateInterest() override
    {
        double interest = (balance * 0.05 * term) / 12;
        balance += interest;
        cout << "Interest Added for " << term << " Months: " << interest << endl;
        return interest;
    }
};

int main()
{
    vector<BankAccount *> accounts;
    int choice;

    do
    {
        cout << "1. Add New Account" << endl;
        cout << "2. Display Account Details" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Calculate Interest" << endl;
        cout << "6. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int accountType;
            cout << "Select Account Type: " << endl;
            cout << "1. Savings Account" << endl;
            cout << "2. Checking Account" << endl;
            cout << "3. Fixed Deposit Account" << endl;
            cout << endl;
            cout << "Select Account Type: ";
            cin >> accountType;

            BankAccount *account = nullptr;
            if (accountType == 1)
            {
                account = new SavingsAccount();
            }
            else if (accountType == 2)
            {
                account = new CheckingAccount();
            }
            else if (accountType == 3)
            {
                account = new FixedDepositAccount();
            }
            else
            {
                cout << "Invalid account type." << endl;
                break;
            }

            account->addAccountData();
            accounts.push_back(account);
            cout << "Account added successfully!" << endl;
            break;
        }
        case 2:
        {
            int accountNum;
            cout << "Enter Account Number to Display: ";
            cin >> accountNum;

            for (auto &account : accounts)
            {
                if (account->account_num == accountNum)
                {
                    account->displayAccount();
                    break;
                }
            }
            break;
        }
        case 3:
        {
            int accountNum;
            cout << "Enter Account Number to Deposit: ";
            cin >> accountNum;

            for (auto &account : accounts)
            {
                if (account->account_num == accountNum)
                {
                    double amount;
                    cout << "Enter Amount to Deposit: ";
                    cin >> amount;
                    account->deposit(amount);
                    break;
                }
            }
            break;
        }
        case 4:
        {
            int accountNum;
            cout << "Enter Account Number to Withdraw: ";
            cin >> accountNum;

            for (auto &account : accounts)
            {
                if (account->account_num == accountNum)
                {
                    double amount;
                    cout << "Enter Amount to Withdraw: ";
                    cin >> amount;
                    account->withdraw(amount);
                    break;
                }
            }
            break;
        }
        case 5:
        {
            int accountNum;
            cout << "Enter account number to calculate interest: ";
            cin >> accountNum;

            for (auto &account : accounts)
            {
                if (account->account_num == accountNum)
                {
                    account->calculateInterest();
                    cout << "Interest calculated and added to the account. New balance: " << account->balance << endl;
                    break;
                }
            }
            break;
        }
        case 6:
            cout << "Exiting the program." << endl;
            for (auto &account : accounts)
            {
                delete account;
            }
            accounts.clear();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}