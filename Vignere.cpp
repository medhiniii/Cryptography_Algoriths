#include <iostream>
#include <string>

std::string encrypt(const std::string& plaintext, const std::string& key) {
    std::string ciphertext = "";
    int key_length = key.length();

    for (size_t i = 0; i < plaintext.length(); ++i) {
        char p = plaintext[i];
        char k = key[i % key_length];
        int value = (p - 'A' + k - 'A') % 26;
        ciphertext += static_cast<char>(value + 'A');
    }

    return ciphertext;
}

std::string decrypt(const std::string& ciphertext, const std::string& key) {
    std::string plaintext = "";
    int key_length = key.length();

    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char c = ciphertext[i];
        char k = key[i % key_length];
        int value = (c - 'A' - (k - 'A') + 26) % 26;
        plaintext += static_cast<char>(value + 'A');
    }

    return plaintext;
}

int main() {
    std::string text;
    std::string key = "KEY";
    char choice;

    std::cout << "Vigenère Cipher (Uppercase letters only)" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Enter your text: ";
    std::cin >> text;

    std::cout << "Do you want to (E)ncrypt or (D)ecrypt? ";
    std::cin >> choice;

    if (choice == 'E' || choice == 'e') {
        std::string encrypted = encrypt(text, key);
        std::cout << "Encrypted text: " << encrypted << std::endl;
    }
    else if (choice == 'D' || choice == 'd') {
        std::string decrypted = decrypt(text, key);
        std::cout << "Decrypted text: " << decrypted << std::endl;
    }
    else {
        std::cout << "Invalid choice!" << std::endl;
    }

    return 0;
}
 