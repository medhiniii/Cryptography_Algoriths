#include <iostream>  
#include <cctype>  
#include <string>  
#include <algorithm>  

using namespace std;  

void encrypt(string&, string&, string&); 
void decrypt(string&, string&, string&); 
char getCipher(char p, char k); 
char getPlain(char c, char k);

int main()  
{  
    string plaintext, key, ciphertext, decryptedText;
    int choice;

    cout << "Enter the text: ";  
    getline(cin, plaintext);  
    cout << "Enter the key (should be longer than text): ";  
    getline(cin, key);  
    key.erase(remove(key.begin(), key.end(), ' '), key.end()); 
    if (key.length() < plaintext.length()) {
        cout << "Error: Key must be at least as long as the text!" << endl;
        return 1;
    }

    cout << "Choose operation: 1. Encrypt  2. Decrypt\nEnter choice: ";
    cin >> choice;
    cin.ignore(); 

    if (choice == 1) {
        encrypt(plaintext, key, ciphertext);  
        cout << "\nEncrypted Text is:\n" << ciphertext << endl;  
    } else if (choice == 2) {
        decrypt(plaintext, key, decryptedText);
        cout << "\nDecrypted Text is:\n" << decryptedText << endl;
    } else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    return 0;  
}  

void encrypt(string &plaintext, string &key, string &cipher)  
{  
    string::iterator it1, it2;  
    cipher = "";  
    for (it1 = key.begin(), it2 = plaintext.begin(); it2 < plaintext.end();) {  
        if (!isalpha(*it2)) {  
            it2++;  
            continue;  
        }  
        cipher += getCipher(tolower(*it2), tolower(*it1));  
        it1++;  
        it2++;  
    }  
}  

void decrypt(string &ciphertext, string &key, string &plain)  
{  
    string::iterator it1, it2;  
    plain = "";  
    for (it1 = key.begin(), it2 = ciphertext.begin(); it2 < ciphertext.end();) {  
        if (!isalpha(*it2)) {  
            it2++;  
            continue;  
        }  
        plain += getPlain(tolower(*it2), tolower(*it1));  
        it1++;  
        it2++;  
    }  
}  

char getCipher(char p, char k)  
{  
    int cipher = p + k;  
    if (cipher >= 219) return (char)(cipher - 123);  
    return (char)(cipher - 97);  
}  

char getPlain(char c, char k)  
{  
    int plain = c - k;  
    if (plain < 0) plain += 26;
    return (char)(plain + 'a');  
}
