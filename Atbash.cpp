#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

string atbash(const string& s) {
    string result = "";
    string lower_case = "abcdefghijklmnopqrstuvwxyz";
    string reverse_string = "zyxwvutsrqponmlkjihgfedcba";

    for (char ch : s) {
        if (ch == ' ' || ch == '.' || ch == ',' || isdigit(ch) ||
            ch == '$' || ch == '^' || ch == '!' || ch == '*' || ch == '\'' || ch == '"') {
            result += ch;
        } else {
            for (size_t j = 0; j < lower_case.length(); ++j) {
                if (tolower(ch) == lower_case[j]) {
                    char mirrored = reverse_string[j];
                    result += isupper(ch) ? toupper(mirrored) : mirrored;
                    break;
                }
            }
        }
    }
    return result;
}

void processText(const string& input_text) {
    string decorated_text = "'''" + input_text + "'''";
    string word = "";

    for (size_t i = 0; i < decorated_text.length(); ++i) {
        if (decorated_text[i] == ' ') {
            string cipher_text = atbash(word);
            cipher_text.erase(remove(cipher_text.begin(), cipher_text.end(), '\''), cipher_text.end());
            cout << cipher_text << " ";
            word = "";
        } else {
            word += decorated_text[i];
        }
    }

    if (!word.empty()) {
        string cipher_text = atbash(word);
        cipher_text.erase(remove(cipher_text.begin(), cipher_text.end(), '\''), cipher_text.end());
        cout << cipher_text;
    }
    cout << endl;
}

int main() {
    string choice, text_input;

    cout << "Do you want to encrypt or decrypt? (e/d): ";
    cin >> choice;
    cin.ignore(); 
    cout << "Enter the text: ";
    getline(cin, text_input);

    if (choice == "e" || choice == "E") {
        cout << "Encrypted: ";
        processText(text_input);
    } else if (choice == "d" || choice == "D") {
        cout << "Decrypted: ";
        processText(text_input); 
    } else {
        cout << "Invalid choice. Use 'e' to encrypt or 'd' to decrypt." << endl;
    }

    return 0;
}
