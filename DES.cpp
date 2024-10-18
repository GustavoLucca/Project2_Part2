#include "DES.h"
#include "permutation.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string encryption(string plaintext, vector<string> keys) {
    //Initial permutation here
    string left = plaintext.substr(0,32);
    string right = plaintext.substr(32,32);
    //16 rounds below
    for (int i = 0; i < 16; i++){
        string ogRight = right;
        right = expansion(right);
        // right = XOR(right, subkey[i]);
        right = sBox(right);
        right = pBox(right);
        // left = XOR(left, right);
        string ogLeft = left;
        left = ogRight;
        right = ogLeft;
    }
    string ciphertext = left + right;
    //Final permutation here
    return ciphertext;
}

string decryption(string encrypted, vector<string> keys) {
    string plaintext;
    return plaintext;
}
