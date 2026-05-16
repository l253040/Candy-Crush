//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<ctime>
//#include<fstream>
//using namespace std;
//
//// ================= TIME =================
//string getCurrentTime()
//{
//    time_t now = time(0);
//    char* dt = ctime(&now);
//    return string(dt);
//}
//
//// ================= TRANSACTION =================
//class Transaction
//{
//    string type;
//    double amount;
//    string dateTime;
//
//public:
//    Transaction() {}
//
//    Transaction(string t, double a, string dt)
//    {
//        type = t;
//        amount = a;
//        dateTime = dt;
//    }
//
//    void display()
//    {
//        cout << type << " | " << amount << " | " << dateTime << endl;
//    }
//};
//
//// ================= ACCOUNT =================
//class Account
//{
//protected:
//    int accountNumber;
//    int pin;
//    double balance;
//    bool isLocked;
//    int attempts;
//
//    Transaction* history;
//    int transCount;
//    int capacity;
//
//public:
//    Account(int accNo, int p, double bal)
//    {
//        accountNumber = accNo;
//        pin = p;
//        balance = bal;
//        isLocked = false;
//        attempts = 0;
//
//        capacity = 5;
//        transCount = 0;
//        history = new Transaction[capacity];
//    }
//
//    virtual ~Account()
//    {
//        delete[] history;
//    }
//
//    int getAccNo() { return accountNumber; }
//    int getPin() { return pin; }
//    double getBalance() { return balance; }
//
//    virtual int getType() = 0;
//
//    void resize()
//    {
//        capacity *= 2;
//        Transaction* newArr = new Transaction[capacity];
//
//        for (int i = 0; i < transCount; i++)
//            newArr[i] = history[i];
//
//        delete[] history;
//        history = newArr;
//    }
//
//    void addTransaction(string type, double amount)
//    {
//        if (transCount == capacity)
//            resize();
//
//        history[transCount++] = Transaction(type, amount, getCurrentTime());
//    }
//
//    bool deposit(double amount)
//    {
//        if (isLocked) return false;
//
//        balance += amount;
//        addTransaction("Deposit", amount);
//        return true;
//    }
//
//    virtual bool withdraw(double amount)
//    {
//        if (isLocked) return false;
//
//        if (balance >= amount)
//        {
//            balance -= amount;
//            addTransaction("Withdraw", amount);
//            return true;
//        }
//        return false;
//    }
//
//    bool transfer(Account& target, double amount)
//    {
//        if (withdraw(amount))
//        {
//            target.deposit(amount);
//            addTransaction("Transfer Sent", amount);
//            target.addTransaction("Transfer Received", amount);
//            return true;
//        }
//        return false;
//    }
//
//    bool verifyPin(int enteredPin)
//    {
//        if (isLocked) return false;
//
//        if (enteredPin == pin)
//        {
//            attempts = 0;
//            return true;
//        }
//
//        attempts++;
//        if (attempts >= 3)
//            isLocked = true;
//
//        return false;
//    }
//
//    void showHistory()
//    {
//        for (int i = 0; i < transCount; i++)
//            history[i].display();
//    }
//};
//
//// ================= SAVING =================
//class SavingAccount : public Account
//{
//public:
//    SavingAccount(int accNo, int p, double bal) : Account(accNo, p, bal) {}
//
//    int getType() override { return 1; }
//};
//
//// ================= CURRENT =================
//class CurrentAccount : public Account
//{
//public:
//    CurrentAccount(int accNo, int p, double bal) : Account(accNo, p, bal) {}
//
//    int getType() override { return 2; }
//
//    bool withdraw(double amount) override
//    {
//        if (balance + 1000 >= amount)
//        {
//            balance -= amount;
//            addTransaction("Withdraw(Current)", amount);
//            return true;
//        }
//        return false;
//    }
//};
//
//// ================= ATM =================
//class ATM
//{
//    Account** accounts;
//    int capacity;
//    int count;
//
//    string adminUser = "admin";
//    string adminPass = "1234";
//
//public:
//    ATM()
//    {
//        capacity = 5;
//        count = 0;
//        accounts = new Account * [capacity];
//    }
//
//    ~ATM()
//    {
//        for (int i = 0; i < count; i++)
//            delete accounts[i];
//
//        delete[] accounts;
//    }
//
//    int getCount()
//    {
//        return count;
//    }
//
//    void resize()
//    {
//        capacity *= 2;
//        Account** newArr = new Account * [capacity];
//
//        for (int i = 0; i < count; i++)
//            newArr[i] = accounts[i];
//
//        delete[] accounts;
//        accounts = newArr;
//    }
//
//    void addAccount(Account* acc)
//    {
//        if (count == capacity)
//            resize();
//
//        accounts[count++] = acc;
//    }
//
//    void createAccount(int type, int accNo, int pin, double bal)
//    {
//        if (type == 1)
//            addAccount(new SavingAccount(accNo, pin, bal));
//        else
//            addAccount(new CurrentAccount(accNo, pin, bal));
//    }
//
//    Account* findAccount(int accNo)
//    {
//        for (int i = 0; i < count; i++)
//            if (accounts[i]->getAccNo() == accNo)
//                return accounts[i];
//
//        return nullptr;
//    }
//
//    Account* userLogin(int accNo, int pin)
//    {
//        Account* user = findAccount(accNo);
//
//        if (user && user->verifyPin(pin))
//            return user;
//
//        return nullptr;
//    }
//
//    bool adminLogin(string u, string p)
//    {
//        return (u == adminUser && p == adminPass);
//    }
//
//    void saveToFile()
//    {
//        ofstream file("accounts.txt");
//
//        for (int i = 0; i < count; i++)
//        {
//            file << accounts[i]->getType() << " "
//                << accounts[i]->getAccNo() << " "
//                << accounts[i]->getPin() << " "
//                << accounts[i]->getBalance() << endl;
//        }
//
//        file.close();
//    }
//
//    void loadFromFile()
//    {
//        ifstream file("accounts.txt");
//
//        int type, accNo, pin;
//        double bal;
//
//        while (file >> type >> accNo >> pin >> bal)
//        {
//            if (type == 1)
//                addAccount(new SavingAccount(accNo, pin, bal));
//            else
//                addAccount(new CurrentAccount(accNo, pin, bal));
//        }
//
//        file.close();
//    }
//};
//
//// ================= MAIN =================
//int main()
//{
//    ATM atm;
//    atm.loadFromFile();
//
//    // ? FIRST RUN FIXED HERE
//    if (atm.getCount() == 0)
//    {
//        cout << "\n=== FIRST TIME SETUP ===\n";
//
//        int type, accNo, pin;
//        double bal;
//
//        cout << "Enter Type (1=Saving, 2=Current): ";
//        cin >> type;
//        cout << "Enter Account Number: ";
//        cin >> accNo;
//        cout << "Enter PIN: ";
//        cin >> pin;
//        cout << "Enter Initial Balance: ";
//        cin >> bal;
//
//        atm.createAccount(type, accNo, pin, bal);
//
//        cout << "\nAccount Created Successfully!\n";
//        cout << "Use these credentials to login:\n";
//        cout << "Account No: " << accNo << "\nPIN: " << pin << endl;
//
//        atm.saveToFile();
//    }
//
//    int choice;
//
//    while (true)
//    {
//        cout << "\n===== ATM SYSTEM =====\n";
//        cout << "1. Admin Login\n";
//        cout << "2. User Login\n";
//        cout << "3. Exit\n";
//        cout << "Enter choice: ";
//        cin >> choice;
//
//        if (choice == 1)
//        {
//            string user, pass;
//            cout << "Enter Admin Username: ";
//            cin >> user;
//            cout << "Enter Admin Password: ";
//            cin >> pass;
//
//            if (atm.adminLogin(user, pass))
//            {
//                int adminChoice;
//                do
//                {
//                    cout << "\n--- ADMIN MENU ---\n";
//                    cout << "1. Create Account\n";
//                    cout << "2. Back\n";
//                    cout << "Choice: ";
//                    cin >> adminChoice;
//
//                    if (adminChoice == 1)
//                    {
//                        int type, accNo, pin;
//                        double bal;
//
//                        cout << "Enter Type (1=Saving, 2=Current): ";
//                        cin >> type;
//                        cout << "Enter Account Number: ";
//                        cin >> accNo;
//                        cout << "Enter PIN: ";
//                        cin >> pin;
//                        cout << "Enter Initial Balance: ";
//                        cin >> bal;
//
//                        atm.createAccount(type, accNo, pin, bal);
//                        cout << "Account Created Successfully!\n";
//                    }
//
//                } while (adminChoice != 2);
//            }
//            else
//            {
//                cout << "Invalid Admin Credentials!\n";
//            }
//        }
//
//        else if (choice == 2)
//        {
//            int accNo, pin;
//            cout << "Enter Account Number: ";
//            cin >> accNo;
//            cout << "Enter PIN: ";
//            cin >> pin;
//
//            Account* user = atm.userLogin(accNo, pin);
//
//            if (user)
//            {
//                int userChoice;
//                do
//                {
//                    cout << "\n--- USER MENU ---\n";
//                    cout << "1. Check Balance\n";
//                    cout << "2. Deposit\n";
//                    cout << "3. Withdraw\n";
//                    cout << "4. Transfer\n";
//                    cout << "5. Transaction History\n";
//                    cout << "6. Logout\n";
//                    cout << "Choice: ";
//                    cin >> userChoice;
//
//                    if (userChoice == 1)
//                        cout << "Balance: " << user->getBalance() << endl;
//
//                    else if (userChoice == 2)
//                    {
//                        double amount;
//                        cin >> amount;
//                        cout << (user->deposit(amount) ? "Deposit Successful\n" : "Deposit Failed\n");
//                    }
//
//                    else if (userChoice == 3)
//                    {
//                        double amount;
//                        cin >> amount;
//                        cout << (user->withdraw(amount) ? "Withdrawal Successful\n" : "Failed\n");
//                    }
//
//                    else if (userChoice == 4)
//                    {
//                        int targetAcc;
//                        double amount;
//
//                        cin >> targetAcc;
//                        Account* target = atm.findAccount(targetAcc);
//
//                        if (target)
//                        {
//                            cin >> amount;
//                            cout << (user->transfer(*target, amount) ? "Transfer Successful\n" : "Failed\n");
//                        }
//                        else
//                            cout << "Target Not Found\n";
//                    }
//
//                    else if (userChoice == 5)
//                        user->showHistory();
//
//                } while (userChoice != 6);
//            }
//            else
//            {
//                cout << "Invalid Credentials or Account Locked\n";
//            }
//        }
//
//        else if (choice == 3)
//        {
//            atm.saveToFile();
//            cout << "Data Saved. Exiting...\n";
//            break;
//        }
//
//        else
//        {
//            cout << "Invalid Choice\n";
//        }
//    }
//
//    return 0;
//}