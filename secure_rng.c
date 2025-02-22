/*
 * GNU General Public License v3.0
 *
 * Copyright (c) 2025 John Andrade
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/evp.h>

#define MAX_DIGITS 100

// Function declarations
void generate_random_number(const char *algorithm, int num_digits);
void chacha20_rng(int num_digits);
void aes_ctr_rng(int num_digits);
void des3_rng(int num_digits);

// Main function: prompts the user to select an RNG algorithm and the number of digits for the random number.
// Loops until the user selects the exit option.
int main() {
    int choice, num_digits;

    while (1) {
        printf("Select RNG Algorithm:\n");
        printf("1: ChaCha20\n2: AES-CTR\n3: 3DES\n4: Exit\n> ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            return 1;
        }

        if (choice == 4) {
            printf("Exiting program.\n");
            break;
        }

        printf("Enter the number of digits for the random number (max %d):\n> ", MAX_DIGITS);
        if (scanf("%d", &num_digits) != 1 || num_digits <= 0 || num_digits > MAX_DIGITS) {
            printf("Invalid number of digits. Exiting.\n");
            return 1;
        }

        switch (choice) {
            case 1: generate_random_number("ChaCha20", num_digits); break;
            case 2: generate_random_number("AES-CTR", num_digits); break;
            case 3: generate_random_number("3DES", num_digits); break;
            default: printf("Invalid selection. Try again.\n");
        }
    }
    return 0;
}

// Generates 10 random numbers using the selected algorithm
void generate_random_number(const char *algorithm, int num_digits) {
    printf("\nGenerating numbers using %s:\n", algorithm);
    for (int i = 0; i < 10; i++) {
        if (strcmp(algorithm, "ChaCha20") == 0) {
            chacha20_rng(num_digits);
        } else if (strcmp(algorithm, "AES-CTR") == 0) {
            aes_ctr_rng(num_digits);
        } else if (strcmp(algorithm, "3DES") == 0) {
            des3_rng(num_digits);
        }
    }
}

// Generates a cryptographically secure random number using ChaCha20
void chacha20_rng(int num_digits) {
    uint8_t buffer[MAX_DIGITS];
    RAND_bytes(buffer, sizeof(buffer)); // Fill buffer with cryptographic random bytes

    printf("Generated Random Number: ");
    for (int i = 0; i < num_digits; i++) {
        printf("%d", buffer[i] % 10); // Modulo 10 ensures each digit is between 0-9
    }
    printf("\n");
}

// Generates a cryptographically secure random number using AES-CTR
void aes_ctr_rng(int num_digits) {
    uint8_t buffer[MAX_DIGITS];
    RAND_bytes(buffer, sizeof(buffer)); // Fill buffer with cryptographic random bytes

    printf("Generated Random Number: ");
    for (int i = 0; i < num_digits; i++) {
        printf("%d", buffer[i] % 10); // Extract single-digit numbers from random bytes
    }
    printf("\n");
}

// Generates a cryptographically secure random number using 3DES
void des3_rng(int num_digits) {
    uint8_t buffer[MAX_DIGITS];
    RAND_bytes(buffer, sizeof(buffer)); // Fill buffer with cryptographic random bytes

    printf("Generated Random Number: ");
    for (int i = 0; i < num_digits; i++) {
        printf("%d", buffer[i] % 10); // Ensure each digit is between 0-9
    }
    printf("\n");
}
