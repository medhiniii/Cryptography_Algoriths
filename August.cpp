#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void augustEncrypt(string& text) {
    for (char& ch : text) {
        if (isalpha(ch)) {
            if (islower(ch)) {
                ch = (ch - 'a' + 1) % 26 + 'a';
            } else {
                ch = (ch - 'A' + 1) % 26 + 'A';
            }
        }
    }
}

void augustDecrypt(string& text) {
    for (char& ch : text) {
        if (isalpha(ch)) {
            if (islower(ch)) {
                ch = (ch - 'a' - 1 + 26) % 26 + 'a';
            } else {
                ch = (ch - 'A' - 1 + 26) % 26 + 'A';
            }
        }
    }
}

int main() {
    string text;
    int choice;

    cout << "August Cipher Implementation (C++)" << endl;
    cout << "----------------------------------" << endl;
    cout << "Enter the text: ";
    getline(cin, text);

    cout << "\nChoose operation:" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        augustEncrypt(text);
        cout << "\nEncrypted text: " << text << endl;
    } else if (choice == 2) {
        augustDecrypt(text);
        cout << "\nDecrypted text: " << text << endl;
    } else {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}
