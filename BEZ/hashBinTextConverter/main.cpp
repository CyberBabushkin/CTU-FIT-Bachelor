//
//  main.cpp
//  cv3
//
//  Created by Andrey Babushkin on 09/03/17.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

string textToBinary(string & text) {
    string res = "";
    
    for (const char &c : text) {
        res += std::bitset<8>(c).to_string();
    }
    
    return res;
}

string textToHex(string & text) {
    std::stringstream stream;
    
    for (const char &c : text) {
        stream << std::hex << setfill('0') << setw(2) << (int) c;
    }
    return stream.str();
}

string hexToText(string & hex) {
    string hexBytes = "";
    string res;
    
    for (int i = 0; i < hex.size(); i++)
    {
        hexBytes += hex[i];
        if (i > 0 && i % 2 == 1) {
            unsigned long x = std::stoul(hexBytes, nullptr, 16);
            res += (char) x;
            hexBytes = "";
        }
    }
    
    return res;
}

string hexToBinary(string & hex) {
    string hexBytes;
    string res;
    
    for (int i = 0; i < hex.size(); i++)
    {
        hexBytes += hex[i];
        if (i > 0 && i % 2 == 1) {
            unsigned long x = std::stoul(hexBytes, nullptr, 16);
            bitset<8> bs(x);
            res += bs.to_string();
            hexBytes = "";
        }
    }
    
    return res;
}

string binaryToHex(string & binary) {
    if (binary.size() % 8 != 0)
        return "error!";
    
    string res;
    bitset<8> bs;
    stringstream ss;
    
    for (int i = 0; i < binary.size(); i++) {
        bs[7 - (i % 8)] = binary[i] - '0';
        
        if (i % 8 == 7) {
            unsigned long n = bs.to_ulong();
            ss << hex << n;
        }
    }
    
    return ss.str();
}

string binaryToText(string & binary) {
    if (binary.size() % 8 != 0)
        return "error!";
    
    string res;
    bitset<8> bs;
    
    for (int i = 0; i < binary.size(); i++) {
        bs[7 - (i % 8)] = binary[i] - '0';
        
        if (i % 8 == 7) {
            unsigned long n = bs.to_ulong();
            res += (char)n;
        }
    }
    
    return res;
}

inline unsigned int value(char c)
{
    if (c >= '0' && c <= '9') { return c - '0';      }
    if (c >= 'a' && c <= 'f') { return c - 'a' + 10; }
    if (c >= 'A' && c <= 'F') { return c - 'A' + 10; }
    return -1;
}

string XOR(string hex1, string hex2) {
    if (hex1.size() < hex2.size()) {
        string zeros;
        for (int i = 0; i < hex2.size() - hex1.size(); i++)
            zeros += '0';
        
        hex1 = zeros + hex1;
    }
    
    if (hex1.size() > hex2.size()) {
        string zeros;
        for (int i = 0; i < hex1.size() - hex2.size(); i++)
            zeros += '0';
        
        hex2 = zeros + hex2;
    }
    
    static char const alphabet[] = "0123456789abcdef";
    
    std::string result;
    result.reserve(hex1.length());
    
    for (std::size_t i = 0; i != hex1.length(); ++i)
    {
        unsigned int v = value(hex1[i]) ^ value(hex2[i]);
        result.push_back(alphabet[v]);
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
    if (argc < 3 || argc > 4) {
        cerr << "Usage: \nconverter 1 text\nconverter 2 hexString\nconverter 3 bitSequence" << endl;
        cerr << "converter 4 hex1 hex2" << endl;
        return 1;
    }
    
    string str = string(argv[2]);
    
    switch (argv[1][0]) {
        case '1':
            cout << "Text mode!" << endl;
            cout << "Binary representation: " << textToBinary(str) << endl;;
            cout << "Hex representation: " << textToHex(str) << endl;
            break;
        case '2':
            cout << "Hex mode!" << endl;
            cout << "Text representation: " << hexToText(str) << endl;;
            cout << "Binary representation: " << hexToBinary(str) << endl;
            break;
        case '3':
            cout << "Binary mode!" << endl;
            cout << "Text representation: " << binaryToText(str) << endl;;
            cout << "Hex representation: " << binaryToHex(str) << endl;
            break;
        case '4':
            cout << "Hex XOR mode!" << endl;
            cout << "XOR result: " << XOR(str, string(argv[3])) << endl;
            break;
        default:
            cerr << "Wrong argument!" << endl;
            return 1;
    }
}
