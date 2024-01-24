#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>

void readInFile(char *argv[], std::vector<uint8_t> &bytes){
    std::fstream file(argv[1], std::ios::in | std::ios::binary);
    uint8_t byte = 0;
    char chr[1];
    
    while(1) {
        // read in hex digits
        file.read(chr, 1);
        byte = strtol(chr, NULL, 16);
        file.read(chr, 1);

        if( file.eof() ) break;
        byte = byte << 4 | ((uint8_t) strtol(chr, NULL, 16));

        printf("%x ", byte);
        
        bytes.push_back(byte);
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]){
    std::vector<uint8_t> bytes;
    char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char base64_output[1024];
    uint8_t b64[3];

    uint8_t tmp = 0;
    uint8_t cur, left;
    readInFile(argv, bytes);
    int bytes_count = bytes.size();

    // read  24 bits at a time, then use lookup in base64 table
    for(int idx = 0; idx < bytes_count ; idx += 3){    
        if( (idx-3) <= bytes_count) { 
            b64[0] = (bytes[idx] & 0b1111'1100) >> 2;
            b64[1] = ((bytes[idx] & 0b0000'0011) << 4) + ((bytes[idx+1] & 0b1111'0000) >> 4);
            b64[2] = ((bytes[idx+1] & 0b0000'1111) << 2) + ((bytes[idx+2] & 0b1100'0000) >> 6);
            b64[3] = (bytes[idx+2] & 0b0011'1111);

            std::cout << base64_table[b64[0]]
                      << base64_table[b64[1]] 
                      << base64_table[b64[2]]
                      << base64_table[b64[3]];
            continue;
        }
        
        std::cout << std::endl;
        exit(0);
    }

    return 0;
}