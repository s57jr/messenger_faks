#include "encryption.h"

Encryption::Encryption()
{

}


std::string Encryption::encryptDecrypt(std::string toEncrypt,std::vector<char> key) {

    std::string output = toEncrypt;

    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

    return output;
}


std::vector<char> Encryption::get_key(std::string receiver){
    return key_for_rcv[std::stoi(receiver)];
}
