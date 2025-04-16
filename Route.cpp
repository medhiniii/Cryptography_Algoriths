#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

string route_encrypt(string plain_text, int step_size = 4) {
    int idx = 0;
    string encrypted_text = "";
    vector<vector<char>> matrix_representation;

    int rows = ceil((double)plain_text.length() / step_size);

    for (int i = 0; i < rows; ++i) {
        vector<char> row;
        for (int j = 0; j < step_size; ++j) {
            int index = i * step_size + j;
            if (index < plain_text.length()) {
                row.push_back(plain_text[index]);
            } else {
                row.push_back('-');
            }
        }
        matrix_representation.push_back(row);
    }

    int matrix_width = step_size;
    int matrix_height = matrix_representation.size();
    int allowed_depth = min(matrix_width, matrix_height) / 2;

    for (int i = 0; i < allowed_depth; ++i) {
        for (int j = i; j < matrix_height - i - 1; ++j) {
            encrypted_text += matrix_representation[j][matrix_width - i - 1];
        }
        for (int j = matrix_width - i - 1; j > i; --j) {
            encrypted_text += matrix_representation[matrix_height - i - 1][j];
        }
        for (int j = matrix_height - i - 1; j > i; --j) {
            encrypted_text += matrix_representation[j][i];
        }
        for (int j = i; j < matrix_width - i - 1; ++j) {
            encrypted_text += matrix_representation[i][j];
        }
    }

    return encrypted_text;
}

string route_decrypt(string cipher_text, int step_size = 4) {
    int idx = 0;
    string plain_text = "";

    int matrix_width = step_size;
    int matrix_height = ceil((double)cipher_text.length() / step_size);
    int allowed_depth = min(matrix_width, matrix_height) / 2;

    vector<vector<char>> plain_text_matrix(matrix_height, vector<char>(matrix_width));

    for (int i = 0; i < allowed_depth; ++i) {
        for (int j = i; j < matrix_height - i - 1; ++j) {
            plain_text_matrix[j][matrix_width - i - 1] = cipher_text[idx++];
        }
        for (int j = matrix_width - i - 1; j > i; --j) {
            plain_text_matrix[matrix_height - i - 1][j] = cipher_text[idx++];
        }
        for (int j = matrix_height - i - 1; j > i; --j) {
            plain_text_matrix[j][i] = cipher_text[idx++];
        }
        for (int j = i; j < matrix_width - i - 1; ++j) {
            plain_text_matrix[i][j] = cipher_text[idx++];
        }
    }

    for (int i = 0; i < matrix_height; ++i) {
        for (int j = 0; j < matrix_width; ++j) {
            plain_text += plain_text_matrix[i][j];
        }
    }

    return plain_text;
}

int main() {
    string plain_text = "Hello I am Medhini";
    string cipher = route_encrypt(plain_text, 4);
    cout << "Encrypted: " << cipher << endl;

    string deciphered = route_decrypt(cipher, 4);
    cout << "Decrypted: " << deciphered << endl;

    return 0;
}
