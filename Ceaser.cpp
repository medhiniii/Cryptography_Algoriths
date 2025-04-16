#include <iostream>
#include <string>
using namespace std;

string encrypt(string text, int s) {
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        char charAt = text[i];
        if (isupper(charAt)) {
            result += char((charAt + s - 'A') % 26 + 'A');
        }
        else if (islower(charAt)) {
            result += char((charAt + s - 'a') % 26 + 'a');
        }
        else {
            result += charAt;
        }
    }

    return result;
}

string decrypt(string text, int s) {
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        char charAt = text[i];
        if (isupper(charAt)) {
            result += char((charAt - s - 'A' + 26) % 26 + 'A');
        }
        else if (islower(charAt)) {
            result += char((charAt - s - 'a' + 26) % 26 + 'a');
        }
        else {
            result += charAt;
        }
    }

    return result;
}

int main() {
    string text, choice;
    int s = 4;

    cout << "Do you want to encrypt or decrypt? (e/d): ";
    cin >> choice;

    cout << "Enter the text: ";
    cin.ignore();
    getline(cin, text);

    if (choice == "e" || choice == "E") {
        cout << "Plain Text : " << text << endl;
        cout << "Cipher     : " << encrypt(text, s) << endl;
    } else if (choice == "d" || choice == "D") {
        cout << "Cipher Text: " << text << endl;
        cout << "Decrypted  : " << decrypt(text, s) << endl;
    } else {
        cout << "Invalid choice. Please enter 'e' for encryption or 'd' for decryption." << endl;
    }

    return 0;
}
