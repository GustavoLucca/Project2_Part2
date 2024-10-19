#include "DES.h"
#include "permutation.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string encryption(string plaintext, vector<string> keys) {
    string initialPermutatedText = "";
    for (int i = 0; i < 64; i++) {
        initialPermutatedText += plaintext[IP[i] - 1];
    }

    // 32, 32
    string left = initialPermutatedText.substr(0, 32);
    string right = initialPermutatedText.substr(32, 32);

    // 16 rounds
    for (int i = 0; i < 16; i++) {
        string prevLeft = left;
        string expandedRight = expansion(right);
        string XORED = XOR(expandedRight, keys[i], 48);
        string SBOXED = sBox(XORED);
        string PBOXED = pBox(SBOXED);
        
        left = right;
        right = XOR(prevLeft, PBOXED, 32);
    }

    // should be right order here?

    string combined = right + left;
    string ciphertext = "";
    for (int i = 0; i < 64; i++) {
        ciphertext += combined[FP[i] - 1];
    }
    return ciphertext;
}

string decryption(string encrypted, vector<string> keys) {
    string initialPermutatedText = "";
    for (int i = 0; i < 64; i++) {
        initialPermutatedText += encrypted[IP[i] - 1];
    }

    // 32, 32
    string left = initialPermutatedText.substr(0, 32);
    string right = initialPermutatedText.substr(32, 32);

    // 16 rounds (but -- reversed!)
    for (int i = 15; i >= 0; i--) {
        string prevLeft = left;
        string expandedRight = expansion(right);
        string XORED = XOR(expandedRight, keys[i], 48);
        string SBOXED = sBox(XORED);
        string PBOXED = pBox(SBOXED);
        
        left = right;
        right = XOR(prevLeft, PBOXED, 32);
    }

    string combined = right + left;

    string plaintext = "";
    for (int i = 0; i < 64; i++) {
        plaintext += combined[FP[i] - 1];
    }
    return plaintext;
}
