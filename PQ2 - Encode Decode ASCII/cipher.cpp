/*!******************************************************************
 * \file      cipher.cpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par      
 * \date      08-09-2023
 * 
 * \brief     
 *********************************************************************/
#include <iostream>
#include <cstdint>
#include "cipher.h"

void print_bit(char v, int32_t pos) {
  char one = 1;
  if ( v & one<<pos ) { std::cout << "1"; } else { std::cout << "0"; }
}

void print_bits(char* buffer, int32_t start_pos, int32_t how_many) {
  std::cout << "Bits: ";
  for (int32_t i{}; i < how_many ;) { // for each char
    char *ch = buffer + (start_pos+i)/8;
    for (int32_t j{}; j<8 && i<how_many; ++j, ++i ) { // from more significant to less
      print_bit( *ch, j );
    }
  }
  std::cout << '\n';
}

int32_t read_bit(char const* buffer, int32_t i) {
  char const * ch = buffer + i/8;
  int32_t pos  = i%8;
  return (*ch & 1<<pos) ? 1:0;
}

// decode num_chars characters from ciphertext
// function assumes output C-style string is allocated by someone else and big enough
void decode(char const* ciphertext, int32_t num_chars, char* plaintext) {
  int32_t pos{};
  for(int32_t i{}; i < num_chars; ++i ) {
    // read 2 bits for group (00,01,10,11)
    int32_t group_index = read_bit( ciphertext, pos ) + 2*read_bit( ciphertext, pos+1 );
    int32_t index{}; // index inside group
    pos += 2;

    for(int32_t j{}; j < group_index+1; ++j ) {
      index += (read_bit(ciphertext, pos) << j);
      ++pos;
    }
    plaintext[i] = 'a' + ( (1<<(group_index+1)) -2) + index;
  }
  plaintext[num_chars] = 0; // null terminate final result
}

// assume all lower case input a-z (no spaces)
void encode(char const * plaintext, char* encryptedtext, int32_t *num_bits_used ) {
	// your stuff ...
  int32_t pos{};
    int32_t num_bits_encoded = 0;

    for (int32_t i = 0; plaintext[i] != '\0'; ++i) {
        char current_char = plaintext[i];
        // Determine the group and index for the current character 'current_char'.
        int32_t group_index;
        int32_t index;

        // Determine the group index (0, 1, 2, or 3) based on your encoding scheme.
        if (current_char >= 'a' && current_char <= 'b') {
            group_index = 0;
            index = current_char - 'a';
        } else if (current_char >= 'c' && current_char <= 'f') {
            group_index = 1;
            index = current_char - 'c';
        } else if (current_char >= 'g' && current_char <= 'n') {
            group_index = 2;
            index = current_char - 'g';
        } else if (current_char >= 'o' && current_char <= 'z') {
            group_index = 3;
            index = current_char - 'o';
        } else {
            // Handle unsupported characters (if any) here.
            // For example, you might throw an error or skip them.
        }

        // Encode the group_index and index into encryptedtext using the 'pos' variable.
        // You should set the appropriate bits in 'encryptedtext' based on the calculated values.
        for (int32_t j = 0; j < 2; ++j) {
            int32_t bit = (group_index >> j) & 1;
            if (bit) {
                encryptedtext[pos / 8] |= (1 << (pos % 8));
            } else {
                encryptedtext[pos / 8] &= ~(1 << (pos % 8));
            }
            ++pos;
        }

        for (int32_t j = 0; j < group_index + 1; ++j) {
            int32_t bit = (index >> j) & 1;
            if (bit) {
                encryptedtext[pos / 8] |= (1 << (pos % 8));
            } else {
                encryptedtext[pos / 8] &= ~(1 << (pos % 8));
            }
            ++pos;
        }

        // Update 'num_bits_encoded' to keep track of the total bits used for encoding.
        num_bits_encoded += group_index + 3; // 2 bits for group + group_index + 1 bits for index
    }

    // Set 'num_bits_used' to the total number of bits used for encoding.
    *num_bits_used = num_bits_encoded;
}
