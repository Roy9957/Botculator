#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

void showTermuxLoading() {
    string spinner = "|/-\\";
    for (int i = 0; i < 20; i++) {  // 20 বার স্পিন করবে
        cout << "\r\033[1;32mLoading " << spinner[i % 4] << "\033[0m" << flush;
        this_thread::sleep_for(chrono::milliseconds(200));  // প্রতি 200 মিলিসেকেন্ড পর স্পিন হবে
    }
    cout << endl;
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";  // কনসোল ক্লিয়ার করার জন্য ANSI কোড
}

void addToHistory(vector<string>& history, const string& operation) {
    history.push_back(operation);
}

void showHistory(const vector<string>& history) {
    cout << "\033[1;34mHistory:\033[0m" << endl;
    if (history.empty()) {
        cout << "\033[1;31mNo history available.\033[0m" << endl;
    } else {
        for (const auto& entry : history) {
            cout << "\033[1;33m" << entry << "\033[0m" << endl;
        }
    }
}

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        cout << "\033[1;31mError! Division by zero is not allowed.\033[0m" << endl;
        return -1;  // Error code for division by zero
    }
    return a / b;
}

void displayTitle() {
    cout << "\033[1;35m==============================\033[0m" << endl;
    cout << "\033[1;36mWelcome to Stylish Calculator!\033[0m" << endl;
    cout << "\033[1;35m==============================\033[0m" << endl;
}

void displayError(const string& errorMsg) {
    cout << "\033[1;31m" << errorMsg << "\033[0m" << endl;
}

int main() {
    double num1, num2;
    char operation;
    int choice;
    vector<string> history;  // অপারেশন হিস্টোরি স্টোর করার জন্য

    while (true) {
        clearScreen();  // কনসোল ক্লিয়ার
        displayTitle();  // ক্যালকুলেটরের টাইটেল

        // ইউজার থেকে অপশন নির্বাচন
        cout << "\033[1;33mSelect operation:\n1. Perform Calculation\n2. View History\n3. Exit\033[0m" << endl;
        cout << "\033[1;35mYour choice: \033[0m";
        cin >> choice;

        if (choice == 3) {
            cout << "\033[1;31mExiting... Thank you for using the calculator.\033[0m" << endl;
            break;
        }

        if (choice == 2) {
            showHistory(history);  // হিস্টোরি দেখান
            cout << "\033[1;33mPress any key to go back...\033[0m";
            cin.ignore();
            cin.get();  // wait for user input
            continue;
        }

        // ইউজার থেকে ইনপুট নিন
        cout << "\033[1;33mEnter first number: \033[0m";
        cin >> num1;
        cout << "\033[1;33mEnter second number: \033[0m";
        cin >> num2;

        // অপারেশন সিলেক্ট করুন
        cout << "\033[1;35mEnter operation (+, -, *, /): \033[0m";
        cin >> operation;

        // লোডিং স্পিনার চালান
        showTermuxLoading();  // Termux-এ স্পিনার দেখানোর জন্য

        string result;
        double calcResult;
        switch (operation) {
            case '+':
                calcResult = add(num1, num2);
                result = to_string(calcResult);
                addToHistory(history, to_string(num1) + " + " + to_string(num2) + " = " + result);
                cout << "\033[1;36mResult: \033[0m" << result << endl;
                break;
            case '-':
                calcResult = subtract(num1, num2);
                result = to_string(calcResult);
                addToHistory(history, to_string(num1) + " - " + to_string(num2) + " = " + result);
                cout << "\033[1;36mResult: \033[0m" << result << endl;
                break;
            case '*':
                calcResult = multiply(num1, num2);
                result = to_string(calcResult);
                addToHistory(history, to_string(num1) + " * " + to_string(num2) + " = " + result);
                cout << "\033[1;36mResult: \033[0m" << result << endl;
                break;
            case '/':
                calcResult = divide(num1, num2);
                if (calcResult != -1) {
                    result = to_string(calcResult);
                    addToHistory(history, to_string(num1) + " / " + to_string(num2) + " = " + result);
                    cout << "\033[1;36mResult: \033[0m" << result << endl;
                }
                break;
            default:
                displayError("Invalid operation!");
        }

        // 5 সেকেন্ড পর ক্যালকুলেটর রিফ্রেশ হবে
        this_thread::sleep_for(chrono::seconds(5));
    }

    return 0;
}
