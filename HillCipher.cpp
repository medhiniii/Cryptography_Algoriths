#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

const int MOD = 26;

int letterToNumber(char letter) {
    return toupper(letter) - 'A';
}

char numberToLetter(int number) {
    return (char)(number + 'A');
}

int determinant(const vector<vector<int>>& matrix) {
    return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; ++x)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

vector<vector<int>> inverseMatrix(const vector<vector<int>>& matrix) {
    int det = determinant(matrix);
    det = (det % MOD + MOD) % MOD;
    int invDet = modInverse(det, MOD);
    
    vector<vector<int>> inverse(2, vector<int>(2));
    inverse[0][0] = (matrix[1][1] * invDet) % MOD;
    inverse[0][1] = ((-matrix[0][1] + MOD) * invDet) % MOD;
    inverse[1][0] = ((-matrix[1][0] + MOD) * invDet) % MOD;
    inverse[1][1] = (matrix[0][0] * invDet) % MOD;

    return inverse;
}

vector<int> multiplyMatrix(const vector<vector<int>>& matrix, const vector<int>& vec) {
    vector<int> result(2);
    for (int i = 0; i < 2; ++i) {
        result[i] = 0;
        for (int j = 0; j < 2; ++j) {
            result[i] += matrix[i][j] * vec[j];
        }
        result[i] %= MOD;
    }
    return result;
}

string encrypt(const string& word, const vector<vector<int>>& keyMatrix) {
    string encrypted;
    for (size_t i = 0; i < word.size(); i += 2) {
        vector<int> vec = { letterToNumber(word[i]), letterToNumber(word[i + 1]) };
        vector<int> encryptedVec = multiplyMatrix(keyMatrix, vec);
        encrypted += numberToLetter(encryptedVec[0]);
        encrypted += numberToLetter(encryptedVec[1]);
    }
    return encrypted;
}

string decrypt(const string& word, const vector<vector<int>>& keyMatrix) {
    string decrypted;
    vector<vector<int>> inverseKey = inverseMatrix(keyMatrix);
    for (size_t i = 0; i < word.size(); i += 2) {
        vector<int> vec = { letterToNumber(word[i]), letterToNumber(word[i + 1]) };
        vector<int> decryptedVec = multiplyMatrix(inverseKey, vec);
        decrypted += numberToLetter(decryptedVec[0]);
        decrypted += numberToLetter(decryptedVec[1]);
    }
    return decrypted;
}

int main() {
    vector<vector<int>> keyMatrix = {{3, 3}, {2, 5}};
    string word;

    cout << "Enter a 4-letter word (only letters): ";
    cin >> word;

    if (word.length() != 4 || !isalpha(word[0]) || !isalpha(word[1]) || !isalpha(word[2]) || !isalpha(word[3])) {
        cout << "Invalid input. Please enter a 4-letter word with only alphabetic characters.\n";
        return 1;
    }

    for (char& c : word) c = toupper(c);

    string encrypted = encrypt(word, keyMatrix);
    string decrypted = decrypt(encrypted, keyMatrix);

    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}