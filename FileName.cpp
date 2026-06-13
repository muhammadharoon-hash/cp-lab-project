#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;



struct Transaction {

    string type = "";

    double amount = 0.0;

    time_t timestamp = 0;
};

// ================= ACCOUNT STRUCT =================

struct Account {

    int accountNumber = 0;

    string accountHolder = "";

    double balance = 0.0;

    int pin = 0;

    bool isActive = false;

    vector<Transaction> transactionHistory;
};

// ================= GLOBAL VARIABLES =================

vector<Account> accounts;

int currentAccountIndex = -1;
int nextAccountNumber = 1001;

// ================= FUNCTION PROTOTYPES =================

void clearScreen();
void pauseScreen();

void showMainMenu();
void showAccountMenu();

void createAccount();
void login();

void deposit(double amount);
void withdraw(double amount);

void checkBalance();
void viewTransactionHistory();

void transferFunds();
void calculateInterest();

void deleteAccount();

void addTransaction(int accountIndex,
    string type,
    double amount);

int findAccountByNumber(int accNumber);

bool getIntegerInput(int& value);
bool getDoubleInput(double& value);

string formatTime(time_t timestamp);

// ================= MAIN FUNCTION =================

int main() {

    int choice;

    while (true) {

        clearScreen();

        cout << "\n========================================\n";
        cout << "      ADVANCED BANKING SYSTEM\n";
        cout << "========================================\n";

        showMainMenu();

        cout << "Enter your choice: ";

        if (!getIntegerInput(choice)) {

            cout << "Invalid input!\n";
            pauseScreen();
            continue;
        }

        switch (choice) {

        case 1:
            createAccount();
            break;

        case 2:
            login();
            break;

        case 3:

            clearScreen();

            cout << "\n========================================\n";
            cout << "Thank you for using our banking system!\n";
            cout << "========================================\n\n";

            return 0;

        default:

            cout << "Invalid choice!\n";
            pauseScreen();
        }
    }

    return 0;
}

// ================= CLEAR SCREEN =================

void clearScreen() {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

}

// ================= PAUSE SCREEN =================

void pauseScreen() {

    cout << "\nPress Enter to continue...";
    cin.get();
}

// ================= MENUS =================

void showMainMenu() {

    cout << "\n========== MAIN MENU ==========\n";

    cout << "1. Create New Account\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";

    cout << "===============================\n";
}

void showAccountMenu() {

    cout << "\n========== ACCOUNT MENU ==========\n";

    cout << "1. Deposit Money\n";
    cout << "2. Withdraw Money\n";
    cout << "3. Check Balance\n";
    cout << "4. View Transaction History\n";
    cout << "5. Transfer Funds\n";
    cout << "6. Calculate Interest\n";
    cout << "7. Delete Account\n";
    cout << "8. Logout\n";

    cout << "==================================\n";
}

// ================= CREATE ACCOUNT =================

void createAccount() {

    clearScreen();

    string name;
    int pin;
    double initialDeposit;

    cout << "\n========== CREATE ACCOUNT ==========\n";

    cout << "Enter full name: ";
    getline(cin, name);

    if (name.empty()) {

        cout << "Name cannot be empty!\n";
        pauseScreen();
        return;
    }

    cout << "Set a 4-digit PIN: ";

    if (!getIntegerInput(pin)) {

        cout << "Invalid PIN!\n";
        pauseScreen();
        return;
    }

    if (pin < 1000 || pin > 9999) {

        cout << "PIN must be exactly 4 digits!\n";
        pauseScreen();
        return;
    }

    cout << "Enter initial deposit amount: $";

    if (!getDoubleInput(initialDeposit)) {

        cout << "Invalid amount!\n";
        pauseScreen();
        return;
    }

    if (initialDeposit < 0) {

        cout << "Deposit cannot be negative!\n";
        pauseScreen();
        return;
    }

    Account newAccount;

    newAccount.accountNumber = nextAccountNumber++;
    newAccount.accountHolder = name;
    newAccount.balance = initialDeposit;
    newAccount.pin = pin;
    newAccount.isActive = true;

    if (initialDeposit > 0) {

        newAccount.transactionHistory.push_back(
            { "Initial Deposit", initialDeposit, time(0) }
        );
    }

    accounts.push_back(newAccount);

    clearScreen();

    cout << "\n========================================\n";
    cout << "ACCOUNT CREATED SUCCESSFULLY\n";
    cout << "========================================\n";

    cout << "Account Number : "
        << newAccount.accountNumber << endl;

    cout << "Account Holder : "
        << newAccount.accountHolder << endl;

    cout << "Balance        : $"
        << fixed << setprecision(2)
        << newAccount.balance << endl;

    cout << "========================================\n";

    pauseScreen();
}

// ================= LOGIN =================

void login() {

    clearScreen();

    int accNumber;
    int pin;

    cout << "\n========== LOGIN ==========\n";

    cout << "Enter account number: ";

    if (!getIntegerInput(accNumber)) {

        cout << "Invalid account number!\n";
        pauseScreen();
        return;
    }

    int accIndex = findAccountByNumber(accNumber);

    if (accIndex == -1) {

        cout << "Account not found!\n";
        pauseScreen();
        return;
    }

    if (!accounts[accIndex].isActive) {

        cout << "Account is inactive!\n";
        pauseScreen();
        return;
    }

    cout << "Enter PIN: ";

    if (!getIntegerInput(pin)) {

        cout << "Invalid PIN!\n";
        pauseScreen();
        return;
    }

    if (accounts[accIndex].pin != pin) {

        cout << "Incorrect PIN!\n";
        pauseScreen();
        return;
    }

    currentAccountIndex = accIndex;

    int choice;

    while (true) {

        clearScreen();

        cout << "\nWelcome, "
            << accounts[currentAccountIndex].accountHolder
            << endl;

        showAccountMenu();

        cout << "Enter your choice: ";

        if (!getIntegerInput(choice)) {

            cout << "Invalid input!\n";
            pauseScreen();
            continue;
        }

        switch (choice) {

        case 1: {

            double amount;

            cout << "Enter deposit amount: $";

            if (!getDoubleInput(amount)) {

                cout << "Invalid amount!\n";
                pauseScreen();
                break;
            }

            deposit(amount);

            pauseScreen();

            break;
        }

        case 2: {

            double amount;

            cout << "Enter withdrawal amount: $";

            if (!getDoubleInput(amount)) {

                cout << "Invalid amount!\n";
                pauseScreen();
                break;
            }

            withdraw(amount);

            pauseScreen();

            break;
        }

        case 3:

            checkBalance();

            pauseScreen();

            break;

        case 4:

            viewTransactionHistory();

            pauseScreen();

            break;

        case 5:

            transferFunds();

            pauseScreen();

            break;

        case 6:

            calculateInterest();

            pauseScreen();

            break;

        case 7:

            deleteAccount();

            currentAccountIndex = -1;

            pauseScreen();

            return;

        case 8:

            cout << "\nLogging out...\n";

            currentAccountIndex = -1;

            pauseScreen();

            return;

        default:

            cout << "Invalid choice!\n";

            pauseScreen();
        }
    }
}

// ================= DEPOSIT =================

void deposit(double amount) {

    if (amount <= 0) {

        cout << "Amount must be positive!\n";
        return;
    }

    accounts[currentAccountIndex].balance += amount;

    addTransaction(currentAccountIndex,
        "Deposit",
        amount);

    cout << "\nDeposit successful.\n";

    cout << "New Balance: $"
        << fixed << setprecision(2)
        << accounts[currentAccountIndex].balance
        << endl;
}

// ================= WITHDRAW =================

void withdraw(double amount) {

    if (amount <= 0) {

        cout << "Amount must be positive!\n";
        return;
    }

    if (amount > accounts[currentAccountIndex].balance) {

        cout << "Insufficient balance!\n";

        return;
    }

    accounts[currentAccountIndex].balance -= amount;

    addTransaction(currentAccountIndex,
        "Withdrawal",
        amount);

    cout << "\nWithdrawal successful.\n";

    cout << "Remaining Balance: $"
        << fixed << setprecision(2)
        << accounts[currentAccountIndex].balance
        << endl;
}

// ================= CHECK BALANCE =================

void checkBalance() {

    Account& acc = accounts[currentAccountIndex];

    cout << "\n========== ACCOUNT DETAILS ==========\n";

    cout << "Account Holder : "
        << acc.accountHolder << endl;

    cout << "Account Number : "
        << acc.accountNumber << endl;

    cout << "Balance        : $"
        << fixed << setprecision(2)
        << acc.balance << endl;

    cout << "=====================================\n";
}

// ================= TRANSACTION HISTORY =================

void viewTransactionHistory() {

    vector<Transaction>& history =
        accounts[currentAccountIndex].transactionHistory;

    if (history.empty()) {

        cout << "No transactions found!\n";
        return;
    }

    cout << "\n================ TRANSACTION HISTORY ================\n";

    cout << left
        << setw(20) << "TYPE"
        << setw(15) << "AMOUNT"
        << "DATE & TIME\n";

    cout << string(60, '-') << endl;

    for (const auto& trans : history) {

        cout << left
            << setw(20) << trans.type

            << "$"
            << setw(14)
            << fixed
            << setprecision(2)
            << trans.amount

            << formatTime(trans.timestamp)
            << endl;
    }

    cout << "=====================================================\n";
}

// ================= TRANSFER FUNDS =================

void transferFunds() {

    int recipientAcc;
    double amount;

    cout << "\n========== TRANSFER FUNDS ==========\n";

    cout << "Enter recipient account number: ";

    if (!getIntegerInput(recipientAcc)) {

        cout << "Invalid account number!\n";
        return;
    }

    int recipientIndex =
        findAccountByNumber(recipientAcc);

    if (recipientIndex == -1) {

        cout << "Recipient account not found!\n";
        return;
    }

    if (!accounts[recipientIndex].isActive) {

        cout << "Recipient account is inactive!\n";
        return;
    }

    if (recipientIndex == currentAccountIndex) {

        cout << "Cannot transfer to your own account!\n";
        return;
    }

    cout << "Enter amount to transfer: $";

    if (!getDoubleInput(amount)) {

        cout << "Invalid amount!\n";
        return;
    }

    if (amount <= 0) {

        cout << "Amount must be positive!\n";
        return;
    }

    if (amount > accounts[currentAccountIndex].balance) {

        cout << "Insufficient balance!\n";
        return;
    }

    accounts[currentAccountIndex].balance -= amount;

    accounts[recipientIndex].balance += amount;

    addTransaction(currentAccountIndex,
        "Transfer Out",
        amount);

    addTransaction(recipientIndex,
        "Transfer In",
        amount);

    cout << "\nTransfer successful.\n";

    cout << "Updated Balance: $"
        << fixed << setprecision(2)
        << accounts[currentAccountIndex].balance
        << endl;
}

// ================= INTEREST =================

void calculateInterest() {

    double annualRate = 0.05;

    double monthlyInterest =
        (accounts[currentAccountIndex].balance
            * annualRate) / 12;

    accounts[currentAccountIndex].balance += monthlyInterest;

    addTransaction(currentAccountIndex,
        "Interest",
        monthlyInterest);

    cout << "\nInterest added successfully.\n";

    cout << "Interest Amount: $"
        << fixed << setprecision(2)
        << monthlyInterest << endl;

    cout << "Updated Balance: $"
        << accounts[currentAccountIndex].balance
        << endl;
}

// ================= DELETE ACCOUNT =================

void deleteAccount() {

    string confirm;

    cout << "\n========== DELETE ACCOUNT ==========\n";

    cout << "Type YES to confirm deletion: ";

    getline(cin, confirm);

    if (confirm == "YES") {

        accounts[currentAccountIndex].isActive = false;

        cout << "Account deleted successfully.\n";
    }
    else {

        cout << "Deletion cancelled.\n";
    }
}

// ================= ADD TRANSACTION =================

void addTransaction(int accountIndex,
    string type,
    double amount) {

    Transaction trans;

    trans.type = type;
    trans.amount = amount;
    trans.timestamp = time(0);

    accounts[accountIndex]
        .transactionHistory
        .push_back(trans);
}

// ================= FORMAT TIME =================

string formatTime(time_t timestamp) {

    char buffer[80];
    tm timeInfo;

    localtime_s(&timeInfo, &timestamp);

    strftime(buffer,
        sizeof(buffer),
        "%d-%m-%Y %H:%M:%S",
        &timeInfo);

    return string(buffer);
}

// ================= FIND ACCOUNT =================

int findAccountByNumber(int accNumber) {

    for (size_t i = 0; i < accounts.size(); i++) {

        if (accounts[i].accountNumber == accNumber) {

            return i;
        }
    }

    return -1;
}

// ================= INPUT VALIDATION =================

bool getIntegerInput(int& value) {

    cin >> value;

    if (cin.fail()) {

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        return false;
    }

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    return true;
}

bool getDoubleInput(double& value) {

    cin >> value;

    if (cin.fail()) {

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        return false;
    }

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    return true;
}
