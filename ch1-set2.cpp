#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>

int64_t readByte(std::fstream &file) {
    uint8_t byte = 0;
    char chr[1];

    file.read(chr, 1);
    byte = strtol(chr, NULL, 16);
    file.read(chr, 1);

    if( file.eof() ) return -1;
    byte = byte << 4 | ((uint8_t) strtol(chr, NULL, 16));

    return byte;
}

void readInFile(char *argv[]){
    std::fstream cipher(argv[1], std::ios::in | std::ios::binary);
    std::fstream key(argv[2], std::ios::in | std::ios::binary);
    int64_t byte_cipher = 0;
    int64_t byte_key = 0;
    uint64_t decode = 0;
    char chr[1];
    
    while(1) {
        byte_cipher = readByte(cipher);
        byte_key = readByte(key);

        // read in hex digits
        if(byte_cipher == -1 || byte_key == -1) {
            break;
        }
        decode = byte_cipher ^ byte_key;

        printf("%lx ", decode);
        
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]){

    readInFile(argv);

    std::cout << std::endl;
    return 0;
}