#include <iostream>

int main()
{
    std::string key;
    std::string message;

    std::cout << "Enter the encryption key: ";
    std::cin >> key;

    if (key.length() != 26)
    {
        std::cout << "Error! The encryption key must contain 26 characters." << std::endl;
        return EXIT_FAILURE;
    }

    for (std::string::size_type i = 0; i < key.length(); ++i)
    {
        if ( key.at(i) < 'A' or key.at(i) > 'z')
        {
            std::cout << "Error! The encryption key must contain only lower case characters." << std::endl;
            return EXIT_FAILURE;
        }
    }

    for (char c = 'a'; c <= 'z'; ++c)
    {
        if (key.find(c) == std::string::npos)
        {
            std::cout << "Error! The encryption key must contain all alphabets a-z." << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::cout << "Enter the text to be encrypted: ";
    std::cin >> message;

    std::cout << "Encrypted text: ";
    for (std::string::size_type i = 0; i < message.length(); ++i)
    {
        char plain = message[i];
        char encypted = key[plain - 'a'];
        std::cout << encypted;
    }

    std::cout << std::endl;

    return EXIT_SUCCESS;
}
