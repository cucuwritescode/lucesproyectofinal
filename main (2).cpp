#include "mbed.h"

// Define the 7-segment display pins
DigitalOut segments[] = {D6, D7, D8, D9, D10, D11, D12};

// Function to display a character on the 7-segment display
void displayCharacter(char character) {
    // Define the patterns for each character (A, B, C, ..., Z)
    const char patterns[][7] = {
        {1, 1, 1, 1, 1, 0, 1}, // A
        {0, 0, 1, 1, 1, 1, 1}, // B
        {0, 0, 0, 1, 1, 0, 1}, // C
        {0, 1, 1, 1, 1, 0, 1}, // D
        {1, 0, 0, 1, 1, 1, 1}, // E
        {1, 0, 0, 0, 1, 1, 1}, // F
        {1, 0, 1, 1, 1, 1, 0}, // G
        {0, 0, 1, 0, 1, 1, 1}, // H
        {1, 0, 0, 0, 1, 0, 0}, // I
        {1, 0, 1, 1, 0, 0, 0}, // J
        {1, 0, 1, 0, 1, 1, 1}, // K
        {0, 0, 0, 1, 1, 1, 0}, // L
        {1, 0, 1, 0, 1, 0, 1}, // M
        {0, 0, 1, 0, 1, 0, 1}, // N
        {0, 0, 1, 1, 1, 0, 1}, // O
        {1, 1, 0, 0, 1, 1, 1}, // P
        {1, 1, 1, 0, 0, 1, 1}, // Q
        {0, 0, 0, 0, 1, 0, 1}, // R
        {1, 0, 1, 1, 0, 1, 0}, // S
        {0, 0, 0, 1, 1, 1, 1}, // T
        {0, 0, 1, 1, 1, 0, 0}, // U
        {0, 1, 0, 1, 0, 1, 0}, // V
        {0, 1, 0, 1, 0, 1, 1}, // W
        {0, 0, 1, 0, 1, 0, 0}, // X
        {0, 1, 1, 1, 0, 1, 1}, // Y
        {1, 1, 0, 1, 1, 0, 0}  // Z
    };

    // Convert character to uppercase manually
    char upperChar = (character >= 'a' && character <= 'z') ? (character - 'a' + 'A') : character;

    // Check if the character is a space
    if (upperChar == ' ') {
        ThisThread::sleep_for(1000);  // Delay for spaces
    } else {
        // Display the character
        for (int i = 0; i < 7; ++i) {
            segments[i] = patterns[upperChar - 'A'][i];
        }
        ThisThread::sleep_for(500);  // Display time for each character
    }

    // Turn off all segments
    for (int i = 0; i < 7; ++i) {
        segments[i] = 0;
    }
}

int main() {
    // Input for first and last names (limited to 15 characters)
    printf("Enter your first name (up to 15 characters)\n");
    char firstnamein[15];
    scanf("%s", firstnamein);

    printf("Enter your last name (up to 15 characters)\n");
    char lastnamein[15];
    scanf("%s", lastnamein);

    printf("Displaying now\n");

    // Display first name
    for (int i = 0; firstnamein[i] != '\0'; ++i) {
        displayCharacter(firstnamein[i]);
    }

    ThisThread::sleep_for(1000);  // Pause between names

    // Display last name
    for (int i = 0; lastnamein[i] != '\0'; ++i) {
        displayCharacter(lastnamein[i]);
    }
}

