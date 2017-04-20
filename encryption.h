#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <iostream>
#include <vector>

class Encryption
{
public:
    Encryption();

    std::string encryptDecrypt(std::string toEncrypt, std::vector<char> key);
    std::vector<char> get_key(std::string receiver);

private:

    std::vector<std::vector<char>> key_for_rcv = {{'a','v','g','e'},{'w','a','s','f'},{'s','d','t','t'},{'c','v','j','k'}}; //hardcoded keys for encryption

};
#endif // ENCRYPTION_H
