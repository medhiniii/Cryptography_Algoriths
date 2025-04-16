#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class Beaufort {
public:
    Beaufort() = default;

    std::string encrypt(const std::string& text, const std::string& key, const std::string& alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ") {
        return crypt(alphabet, key, text);
    }

    std::string decrypt(const std::string& text, const std::string& key, const std::string& alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ") {
        return crypt(alphabet, key, text);
    }

private:
    std::string crypt(const std::string& alphabet, const std::string& key, const std::string& text) {
        std::unordered_map<char, int> indexes;
        for (int i = 0; i < alphabet.size(); ++i) {
            indexes[alphabet[i]] = i;
        }

        std::vector<int> key_indexes;
        for (char k : key) {
            key_indexes.push_back(indexes[k]);
        }

        std::string result;
        size_t key_index = 0;
        for (char t : text) {
            if (indexes.find(t) != indexes.end()) {
                int k = key_indexes[key_index % key.length()];
                int i = k - indexes[t];
                if (i < 0) {
                    i += alphabet.size();
                }
                result += alphabet[i];
                ++key_index;
            } else {
                throw std::runtime_error("Can't find char '" + std::string(1, t) + "' of text in alphabet!");
            }
        }
        return result;
    }
};

int main() {
    std::string text, key, action;
    std::cout << "Enter the text: ";
    std::getline(std::cin, text);
    std::cout << "Enter the key: ";
    std::getline(std::cin, key);
    std::cout << "Encrypt or Decrypt (e/d): ";
    std::getline(std::cin, action);

    Beaufort cipher;
    std::string result;

    if (action == "e" || action == "encrypt") {
        result = cipher.encrypt(text, key);
    } else if (action == "d" || action == "decrypt") {
        result = cipher.decrypt(text, key);
    } else {
        std::cerr << "Invalid action!" << std::endl;
        return 1;
    }

    std::cout << "Result: " << result << std::endl;
    return 0;
}
