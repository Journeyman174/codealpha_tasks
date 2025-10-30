#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Create folder "users" if it doesn't exist
void ensureUserFolder() {
#ifdef _WIN32
    system("if not exist users mkdir users");
#else
    system("mkdir -p users");
#endif
}

// Check if a user already exists
bool userExists(const string& username) {
    ifstream fin("users/" + username + ".txt");
    return fin.good();
}

// Validate username and password rules
bool isValidInput(const string& username, const string& password) {
    if (username.size() < 3) {
        cout << "Username must have at least 3 characters.\n";
        return false;
    }
    if (password.size() < 3) {
        cout << "Password must have at least 3 characters.\n";
        return false;
    }
    if (username.find(' ') != string::npos || password.find(' ') != string::npos) {
        cout << "Username and password cannot contain spaces.\n";
        return false;
    }
    return true;
}

// Register a new user
void registerUser() {
    ensureUserFolder();

    string username, password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    if (!isValidInput(username, password))
        return;

    if (userExists(username)) {
        cout << "Registration failed — username already exists.\n";
        return;
    }

    ofstream fout("users/" + username + ".txt");
    fout << password;
    fout.close();

    cout << "User '" << username << "' registered successfully.\n";
}

// Login an existing user
void loginUser() {
    string username, password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    if (!userExists(username)) {
        cout << "Login failed — user not found.\n";
        return;
    }

    ifstream fin("users/" + username + ".txt");
    string storedPassword;
    getline(fin, storedPassword);
    fin.close();

    if (password == storedPassword)
        cout << "Login successful! Welcome back, " << username << ".\n";
    else
        cout << "Incorrect password. Try again.\n";
}

// Menu
void showMenu() {
    cout << "\n====== LOGIN & REGISTRATION SYSTEM ======\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Choose option: ";
}

int main() {
    ensureUserFolder();

    while (true) {
        showMenu();
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
