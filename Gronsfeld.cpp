#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encrypt(const string& text, const string& key) {
    string result = "";
    vector<int> ascii_values;
    for (size_t i = 0; i < text.length(); ++i) {
        ascii_values.push_back(static_cast<int>(text[i]));
    }

    string extended_key = "";
    if (text.length() > key.length()) {
        int repeat_count = (text.length() / key.length()) + 1;
        string long_key = key;
        long_key.resize(repeat_count * key.length());
        
        for (size_t i = 0; i < ascii_values.size(); ++i) {
            extended_key += long_key[i];
            if (ascii_values[i] == 47) { // '/'' character
                extended_key += long_key[i];
            }
        }
    }

    for (size_t i = 0; i < ascii_values.size(); ++i) {
        int symbol = ascii_values[i];
        if (symbol >= 65 && symbol <= 90) {  // uppercase letters A-Z
            if (symbol != 47) {
                int temp = symbol + static_cast<int>(extended_key[i]);
                if (temp > 90) {
                    temp -= 26;
                }
                result += static_cast<char>(temp);
            }
            else {
                result += "/";
            }
        } 
        else {
            result += static_cast<char>(symbol);
        }
    }
    return result;
}

string decrypt(const string& text, const string& key) {
    string result = "";
    vector<int> ascii_values;
    for (size_t i = 0; i < text.length(); ++i) {
        ascii_values.push_back(static_cast<int>(text[i]));
    }

    string extended_key = "";
    if (text.length() > key.length()) {
        int repeat_count = (text.length() / key.length()) + 1;
        string long_key = key;
        long_key.resize(repeat_count * key.length());

        for (size_t i = 0; i < ascii_values.size(); ++i) {
            extended_key += long_key[i];
            if (ascii_values[i] == 47) { // '/'' character
                extended_key += long_key[i];
            }
        }
    }

    for (size_t i = 0; i < ascii_values.size(); ++i) {
        int symbol = ascii_values[i];
        if (symbol >= 65 && symbol <= 90) {
            if (symbol != 47) {
                int temp = symbol - static_cast<int>(extended_key[i]);
                if (temp < 65) {
                    temp += 26;
                }
                result += static_cast<char>(temp);
            }
            else {
                result += "/";
            }
        } 
        else {
            result += static_cast<char>(symbol);
        }
    }
    return result;
}

int main() {
    string text, key, mode;
    
    cout << "Enter the string (only UPPERCASE): ";
    getline(cin, text);
    
    cout << "Enter the key: ";
    getline(cin, key);

    cout << "Enter operation (encrypt/decrypt): ";
    getline(cin, mode);

    
    for (char& c : text) {
        if (c == ' ') {
            c = '/';
        }
    }

    string result;
    if (mode == "encrypt") {
        result = encrypt(text, key);
    } else if (mode == "decrypt") {
        result = decrypt(text, key);
    } else {
        cout << "Invalid operation!" << endl;
        return 0;
    }

        for (char& c : result) {
        if (c == '/') {
            c = ' ';
        }
    }

    cout << "Result: " << result << endl;
    
    return 0;
}
