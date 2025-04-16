#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

class Myszkowski {
private:
    string key;

    vector<int> generate_order(const string& key) {
        string key_u = key;
        transform(key_u.begin(), key_u.end(), key_u.begin(), ::toupper);

        vector<char> sorted_chars(key_u.begin(), key_u.end());
        sort(sorted_chars.begin(), sorted_chars.end());

        vector<int> result(key.length(), 0);
        int cur_index = 1;
        int from_index = 0;

        for (int i = 0; i < sorted_chars.size(); ++i) {
            if (i == 0 || sorted_chars[i] == sorted_chars[i - 1]) {
                int pos = key_u.find(sorted_chars[i], from_index);
                from_index = pos + 1;
                result[pos] = cur_index;
            } else {
                ++cur_index;
                from_index = 0;
                int pos = key_u.find(sorted_chars[i], from_index);
                from_index = pos + 1;
                result[pos] = cur_index;
            }
        }

        return result;
    }

    vector<vector<char>> build_block(const string& plain, int cols) {
        int rows = (plain.size() + cols - 1) / cols;
        vector<vector<char>> block(rows, vector<char>(cols, '\0'));
        int idx = 0;
        for (int i = 0; i < rows && idx < plain.size(); ++i) {
            for (int j = 0; j < cols && idx < plain.size(); ++j) {
                block[i][j] = plain[idx++];
            }
        }
        return block;
    }

    vector<vector<char>> transp_block(const vector<vector<char>>& block, const vector<int>& num) {
        int row = block.size();
        int col = block[0].size();
        vector<vector<char>> result(row + 1, vector<char>(col));

        int cur_num = 1;
        int filled = 0;
        int find_pos = 0;

        while (filled < col) {
            auto it = find(num.begin() + find_pos, num.end(), cur_num);
            if (it == num.end()) {
                ++cur_num;
                find_pos = 0;
                continue;
            } else {
                int pos = distance(num.begin(), it);
                result[0][filled] = '0' + num[pos];
                for (int i = 0; i < row; ++i) {
                    result[i + 1][filled] = block[i][pos];
                }
                ++filled;
                find_pos = pos + 1;
            }
        }
        return result;
    }

    string read_col(const vector<vector<char>>& block, int start_pos, int end_pos) {
        if (start_pos > end_pos) return "";
        stringstream ss;
        for (int i = 1; i < block.size(); ++i) {
            for (int j = start_pos; j <= end_pos; ++j) {
                if (block[i][j] != '\0') {
                    ss << block[i][j];
                }
            }
        }
        return ss.str();
    }

    string read_block(const vector<vector<char>>& trans_block) {
        int start_pos = 0, end_pos = 0;
        int col = trans_block[0].size();
        stringstream ss;

        while (end_pos < col) {
            if (trans_block[0][end_pos] == trans_block[0][start_pos]) {
                ++end_pos;
            } else {
                ss << read_col(trans_block, start_pos, end_pos - 1);
                start_pos = end_pos;
            }
        }
        ss << read_col(trans_block, start_pos, end_pos - 1);
        return ss.str();
    }

public:
    Myszkowski(string k = "BANANA") : key(k) {}

    string encode(const string& plain) {
        vector<int> num_in = generate_order(key);
        auto block = build_block(plain, key.length());
        auto trans_block = transp_block(block, num_in);
        return read_block(trans_block);
    }

    string decode(const string& cipher) {
        vector<int> num_in = generate_order(key);
        int cols = key.length();
        int rows = (cipher.size() + cols - 1) / cols;
        vector<vector<char>> block(rows, vector<char>(cols, '\0'));

        
        vector<int> counts(*max_element(num_in.begin(), num_in.end()) + 1, 0);
        for (int val : num_in) counts[val]++;

        vector<int> order;
        for (int i = 1; i < counts.size(); ++i) {
            for (int j = 0; j < num_in.size(); ++j) {
                if (num_in[j] == i) order.push_back(j);
            }
        }

        int idx = 0;
        for (int i = 1; i < counts.size(); ++i) {
            vector<int> positions;
            for (int j = 0; j < num_in.size(); ++j) {
                if (num_in[j] == i) positions.push_back(j);
            }

            for (int r = 0; r < rows; ++r) {
                for (int pos : positions) {
                    if (idx < cipher.size()) {
                        block[r][pos] = cipher[idx++];
                    }
                }
            }
        }

        stringstream ss;
        for (const auto& row : block) {
            for (char c : row) {
                if (c != '\0') ss << c;
            }
        }
        return ss.str();
    }
};

int main() {
    Myszkowski cipher("BANANA");
    string choice;
    cout << "Do you want to encrypt or decrypt? (e/d): ";
    cin >> choice;

    if (choice == "e" || choice == "E") {
        string plaintext;
        cout << "Enter the Plaintext: ";
        cin >> plaintext;
        string encrypted = cipher.encode(plaintext);
        cout << "Encrypted: " << encrypted << endl;
    } else if (choice == "d" || choice == "D") {
        string ciphertext;
        cout << "Enter the Ciphertext: ";
        cin >> ciphertext;
        string decrypted = cipher.decode(ciphertext);
        cout << "Decrypted: " << decrypted << endl;
    } else {
        cout << "Invalid choice. Please enter 'e' for encryption or 'd' for decryption." << endl;
    }

    return 0;
}
