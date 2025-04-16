

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <numeric> 

using namespace std;

const int M = 26; 


char indexToLetter(int index) {
    return 'A' + index;
}

int letterToIndex(char letter) {
    return toupper(letter) - 'A';
}


string encryptAffine(const string& plaintext, int alpha, int beta) {
    string ciphertext = "";

    for (char ch : plaintext) {
        if (isalpha(ch)) {
            int x = letterToIndex(ch);
            int encryptedIndex = (alpha * x + beta) % M;
            ciphertext += indexToLetter(encryptedIndex);
        }
    }
    return ciphertext;
}


string decryptAffine(const string& ciphertext, int alpha, int beta) {
    string plaintext = "";
    int a_inv = -1;

    // Find modular inverse of alpha
    for (int i = 1; i < M; ++i) {
        if ((alpha * i) % M == 1) {
            a_inv = i;
            break;
        }
    }

    if (a_inv == -1) {
        return "Modular inverse for alpha doesn't exist. Decryption failed.";
    }

    for (char ch : ciphertext) {
        if (isalpha(ch)) {
            int y = letterToIndex(ch);
            int decryptedIndex = (a_inv * (y - beta + M)) % M;
            plaintext += indexToLetter(decryptedIndex);
        }
    }
    return plaintext;
}

int main() {
    char mode;
    int alpha, beta;
    string text;

    cout << "Affine Cipher (E/D)\n";
    cout << "Choose mode: 'e' for encryption or 'd' for decryption: ";
    cin >> mode;

    cout << "Enter alpha (1 to 25): ";
    cin >> alpha;
    cout << "Enter beta (0 to 25): ";
    cin >> beta;
    cin.ignore(); 

    if (alpha < 1 || alpha >= M || beta < 0 || beta >= M || gcd(alpha, M) != 1) {
        cout << "Invalid alpha/beta or GCD(alpha, 26) != 1.\n";
        return 1;
    }

    cout << "Enter the text: ";
    getline(cin, text);

    if (mode == 'e') {
        string encrypted = encryptAffine(text, alpha, beta);
        cout << "\nEncrypted: " << encrypted << endl;
    } else if (mode == 'd') {
        string decrypted = decryptAffine(text, alpha, beta);
        cout << "\nDecrypted: " << decrypted << endl;
    } else {
        cout << "Invalid mode selected.\n";
    }

    return 0;
}
