#include <iostream>
#include <vector>
#include <string>

using namespace std;

string encrypt(const string& clearText, int key) {
    vector<vector<char>> matrix(key, vector<char>(clearText.length(), '\n'));

    int row = 0, col = 0;
    bool down = true;

    for (char c : clearText) {
        matrix[row][col++] = c;

        if (down) {
            row++;
            if (row == key) {
                row = key - 2;
                down = false;
            }
        } else {
            row--;
            if (row < 0) {
                row = 1;
                down = true;
            }
        }
    }

    string result = "";
    for (int i = 0; i < key; ++i) {
        for (int j = 0; j < clearText.length(); ++j) {
            if (matrix[i][j] != '\n') {
                result += matrix[i][j];
            }
        }
    }

    return result;
}

string decrypt(const string& cipherText, int key) {
    vector<vector<char>> matrix(key, vector<char>(cipherText.length(), '\n'));

    int row = 0, col = 0;
    bool down = true;

    for (int i = 0; i < cipherText.length(); ++i) {
        matrix[row][col++] = '*';

        if (down) {
            row++;
            if (row == key) {
                row = key - 2;
                down = false;
            }
        } else {
            row--;
            if (row < 0) {
                row = 1;
                down = true;
            }
        }
    }

       int index = 0;
    for (int i = 0; i < key; ++i) {
        for (int j = 0; j < cipherText.length(); ++j) {
            if (matrix[i][j] == '*' && index < cipherText.length()) {
                matrix[i][j] = cipherText[index++];
            }
        }
    }

        string result = "";
    row = 0;
    col = 0;
    down = true;

    for (int i = 0; i < cipherText.length(); ++i) {
        result += matrix[row][col++];

        if (down) {
            row++;
            if (row == key) {
                row = key - 2;
                down = false;
            }
        } else {
            row--;
            if (row < 0) {
                row = 1;
                down = true;
            }
        }
    }

    return result;
}

int main() {
    int choice;
    cout << "Railfence Cipher:\n";

    do {
        cout << "1. Encrypt a text\n";
        cout << "2. Decrypt a text\n";
        cout << "3. Exit\n";
        cin >> choice;

        if (choice == 1) {
            string text;
            int key;
            cout << "Encryption\nEnter the text and the key: ";
            cin >> text >> key;
            cout << "Encrypted text: " << encrypt(text, key) << endl;

        } else if (choice == 2) {
            string text;
            int key;
            cout << "Decryption\nEnter the text and the key: ";
            cin >> text >> key;
            cout << "Decrypted text: " << decrypt(text, key) << endl;

        } else if (choice != 3) {
            cout << "Invalid choice.\n";
        }

    } while (choice != 3);

    cout << "End of the program\n";
    return 0;
}
