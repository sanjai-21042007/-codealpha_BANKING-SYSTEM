#include <bits/stdc++.h>
using namespace std;

class Transaction
{
public:
    string type;
    double amount;
    Transaction(string t, double a) : type(t), amount(a) {}
};

class Account
{
    int accNo;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int num) : accNo(num), balance(0) {}
    void deposit(double amt)
    {
        balance += amt;
        transactions.emplace_back("Deposit", amt);
    }
    bool withdraw(double amt)
    {
        if (amt <= balance)
        {
            balance -= amt;
            transactions.emplace_back("Withdraw", amt);
            return true;
        }
        return false;
    }
    void transfer(Account &to, double amt)
    {
        if (withdraw(amt))
        {
            to.deposit(amt);
            transactions.emplace_back("Transfer to " + to.getAccNoStr(), amt);
        }
    }
    double getBalance() const
    {
        return balance;
    }
    void showTransactions() const
    {
        for (auto &t : transactions)
            cout << t.type << ": " << t.amount << endl;
    }
    int getAccNo() const
    {
        return accNo;
    }
    string getAccNoStr() const
    {
        return to_string(accNo);
    }
};

class Customer
{
    string name;
    int id;
    Account account;

public:
    Customer(string n, int i) : name(n), id(i), account(i) {}
    Account &getAccount()
    {
        return account;
    }
    void showInfo() const
    {
        cout << "Customer: " << name << " | ID: " << id << " | Balance: " << account.getBalance() << endl;
    }
};

int main()
{
    vector<Customer> customers;
    int n;
    cout << "Enter number of customers: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string name;
        int id;
        cout << "Enter name and ID for customer " << i + 1 << ": ";
        cin >> name >> id;
        customers.emplace_back(name, id);
    }

    int choice;
    do
    {
        cout << "\nMenu:\n1. Deposit\n2. Withdraw\n3. Transfer\n4. Show Info\n5. Show Transactions\n0. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id;
            double amt;
            cout << "Enter Customer ID and amount to deposit: ";
            cin >> id >> amt;
            for (auto &c : customers)
            {
                if (c.getAccount().getAccNo() == id)
                {
                    c.getAccount().deposit(amt);
                    break;
                }
            }
        }
        else if (choice == 2)
        {
            int id;
            double amt;
            cout << "Enter Customer ID and amount to withdraw: ";
            cin >> id >> amt;
            for (auto &c : customers)
            {
                if (c.getAccount().getAccNo() == id)
                {
                    if (!c.getAccount().withdraw(amt))
                        cout << "Insufficient balance.\n";
                    break;
                }
            }
        }
        else if (choice == 3)
        {
            int fromID, toID;
            double amt;
            cout << "Enter sender ID, receiver ID, and amount to transfer: ";
            cin >> fromID >> toID >> amt;
            Account *from = nullptr, *to = nullptr;
            for (auto &c : customers)
            {
                if (c.getAccount().getAccNo() == fromID)
                    from = &c.getAccount();
                if (c.getAccount().getAccNo() == toID)
                    to = &c.getAccount();
            }
            if (from && to)
            {
                from->transfer(*to, amt);
            }
            else
            {
                cout << "Invalid account IDs.\n";
            }
        }
        else if (choice == 4)
        {
            for (auto &c : customers)
                c.showInfo();
        }
        else if (choice == 5)
        {
            for (auto &c : customers)
            {
                cout << "Transactions for Customer ID " << c.getAccount().getAccNo() << ":\n";
                c.getAccount().showTransactions();
                cout << endl;
            }
        }
    } while (choice != 0);

    return 0;
}