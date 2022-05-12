#include <iostream>
#include <fstream>
#include <string>
#include <cassert>


const int ALPHABET_LENGTH{26};

int number_from_letter(char letter) {
  int offset = letter - (int)'a';
  if (offset < 0 || offset >= ALPHABET_LENGTH) {
    std::cout << "number_from_letter called with invalid argument (" << letter << ").\n";
    assert(false);
  }
  return offset;
}

char letter_from_number(int number) {

  if (number < 0 || number >= ALPHABET_LENGTH) {
    std::cout << "letter_from_number called with an invalid argument (" << number << ").\n";
    assert(false);
  }

  const char alphabet[] = { 'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
    'w',
    'x',
    'y',
    'z'};
  return alphabet[number];
}

int main() {
    int direction{0};
    int shift{0};
    char realLetter;
    int realNum;
    int encrNum;
    char encrLetter;
    bool encrypt;

    encrypt = true;
    realNum = 0;
    encrNum = 0;

    std::ifstream fileInput{ "input.txt" };
    
    char directionInput{'k'};

    if (!(fileInput >> directionInput)) {
        std::cout << "Oops: Could not read the direction from the input file." << std::endl;
        return 1;
    }
    else if (directionInput == 'l') {
        direction = -1;
        encrypt = true;
    }
    else if (directionInput == 'r') {
        direction = 1;
        encrypt = true;
    }
    else {
        std::cout << "Oops: Invalid direction in the input file." << std::endl;
        return 1;
    }

    int shiftInput{ 0 };

    if (!(fileInput >> shiftInput) && encrypt) {
        std::cout << "Oops: Could not read the shift number from the input file." << std::endl;
        return 1;
    }
    else {
        shift = shiftInput;
    }

    while (!std::iscntrl(fileInput.peek()) && !fileInput.eof() && (encrypt)) {
        char realLetter{ 'z' };

        fileInput >> realLetter;
        realNum = number_from_letter(realLetter);
        encrNum = realNum + direction * (shift % 26);

        if (encrNum < 0) {
            encrNum += 26;
        }
        else if (encrNum > 25) {
            encrNum -= 26;
        }

        encrLetter = letter_from_number(encrNum);
        std::cout << encrLetter;
    }
    std::cout << std::endl;
    

 return 0;
}