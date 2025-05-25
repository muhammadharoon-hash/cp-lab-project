#include <iostream>
using namespace std;

double balance = 0.0;

// Function prototypes
void showMenu();
void deposit(double amount);
void withdraw(double amount);
void checkBalance();

int main() {
    int choice;
    double amount;
    char again;

    do {
        showMenu();
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            deposit(amount);
            break;
        case 2:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            withdraw(amount);
            break;
        case 3:
            checkBalance();
            break;
        case 4:
            cout << "Exiting program. Thank you!" << endl;
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }

        cout << "\nDo you want another transaction? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    cout << "Goodbye!" << endl;
    return 0;
}

// Function definitions
void showMenu() {
    cout << "\n==== MINI BANKING SYSTEM ====\n";
    cout << "1. Deposit Money\n";
    cout << "2. Withdraw Money\n";
    cout << "3. Check Balance\n";
    cout << "4. Exit\n";
    cout << "=============================\n";
}

void deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "Deposited: $" << amount << endl;
    }
    else {
        cout << "Invalid amount. Please enter a positive value." << endl;
    }
}

void withdraw(double amount) {
    if (amount <= 0) {
        cout << "Invalid amount. Please enter a positive value." << endl;
    }
    else if (amount > balance) {
        cout << "Insufficient funds! Current balance: $" << balance << endl;
    }
    else {
        balance -= amount;
        cout << "Withdrawn: $" << amount << endl;
    }
}

void checkBalance() {
    cout << "Your current balance is: $" << balance << endl;
}