#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

const int ALPHABET_LENGTH{26};
const char SHIFT_LEFT{'l'};
const char SHIFT_RIGHT{'r'};

int number_from_letter(char letter) {
  int offset = letter - (int)'a';
  if (offset < 0 || offset >= ALPHABET_LENGTH) {
    std::cout << "number_from_letter called with invalid argument (" << letter
              << ").\n";
    assert(false);
  }
  return offset;
}

char letter_from_number(int number) {

  if (number < 0 || number >= ALPHABET_LENGTH) {
    std::cout << "letter_from_number called with an invalid argument ("
              << number << ").\n";
    assert(false);
  }

  const char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                           'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                           's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  return alphabet[number];
}

int main() {
  const std::string filename{"input.txt"};
  std::ifstream input_file{filename};
  char direction{SHIFT_LEFT}, plaintext{'0'};
  int shift_number{0};

  if (!input_file.is_open()) {
    std::cerr << "Oops: Could not open " << filename << "\n";
    return EXIT_FAILURE;
  }

  if (!(input_file >> direction)) {
    std::cout << "Oops: Could not read the direction from the input file.\n";
    return EXIT_FAILURE;
  }

  if (direction != SHIFT_LEFT && direction != SHIFT_RIGHT) {
    std::cout << "Oops: Invalid direction in the input file.\n";
    return EXIT_FAILURE;
  }

  if (!(input_file >> shift_number)) {
    std::cout << "Oops: Could not read the shift number from the input file.\n";
    return EXIT_FAILURE;
  }

  // If we are supposed to shift to the left, make it easier on ourselves
  // and set the shift_number to the negative of itself!
  if (direction == SHIFT_LEFT) {
    shift_number *= -1;
  }

  // Do an encryption for each of the characters that we are able to
  // read from the file.
  while (input_file >> plaintext) {
    // First, determine the input letter's index within the alphabet.
    int plaintext_index{number_from_letter(plaintext)};
    // Second, shift that index according to the key.
    int provisional_ciphertext_index{plaintext_index + shift_number};
    // Third, wrap the index if necessary.
    int modulated_ciphertext_index{provisional_ciphertext_index %
                                   ALPHABET_LENGTH};
    // Fourth, declare and initialize a variable to hold the index of
    // the enciphered letter. Note: The cipher index may be negative
    // if the user requested that we shift left.
    int ciphertext_index{modulated_ciphertext_index};

    // Fifth, if the cipher index is less than 0, we have to
    // count backward from the end of the alphabet!
    if (ciphertext_index < 0) {
      ciphertext_index = ALPHABET_LENGTH + ciphertext_index;
    }

    // Sixth, convert the ciphertext_index to an actual
    // ciphertext character!
    char ciphertext = letter_from_number(ciphertext_index);

    // Seventh, and finally, print it out!
    std::cout << ciphertext;
  }

  // Don't forget that we want to print a newline at the end
  // of the output!
  std::cout << "\n";
  return EXIT_SUCCESS;
}
