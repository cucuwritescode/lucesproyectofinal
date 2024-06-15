 #include "mbed.h"
//button creation
DigitalIn button1(D2, PullUp); //button 1 is connected to pin D2
DigitalIn button2(BUTTON1); //button 2 is connected to pin D3
//define the 7-segment display pins that will be used.
DigitalOut segments[] = {D6, D7, D8, D9, D10, D11, D12};
//function to display a character on the 7-segment display
void displayCharacter(char character, int displayTime) {
//define the patterns for each character (A, B, C, ..., Z)
    const char patterns[26][7] = {
        {1, 1, 1, 1, 1, 0, 1}, // A
        {0, 0, 1, 1, 1, 1, 1}, // B
        {0, 0, 0, 1, 1, 0, 1}, // C
        {0, 1, 1, 1, 1, 0, 1}, // D
        {1, 0, 0, 1, 1, 1, 1}, // E
        {1, 0, 0, 0, 1, 1, 1}, // F
        {1, 0, 1, 1, 1, 1, 0}, // G
        {0, 0, 1, 0, 1, 1, 1}, // H
        {1, 0, 0, 0, 1, 0, 0}, // I
        {1, 0, 1, 1, 0, 0, 0}, // J                                                                                                                                                                                                                                                                                                         B
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
//check if the character is a space
    if (character == ' ') {
        ThisThread::sleep_for(1s); //delay for spaces
    } else {
        //display the character
        for (int i = 0; i < 7; ++i) {
            segments[i]= patterns[character - 65][i];
        }
        ThisThread::sleep_for(500);  //display time for each character
    }
//loop to turn off all segments
    for (int i = 0; i < 7; ++i) {
        segments[i] = 0;
    }
}
//the purpose of this function is to play a simple melody
void playMelody() {
    PwmOut speaker(D3); //speaker is connected to pin SCK/D13
//here I define specific frequencies (equal-tempered scale, A4 = 440 Hz) for the tones that construct the melody. These being:A5, F5, E5, C6
    const float frequencies[] = {880.0, 698.46, 659.26, 1046.5};
    for (int i = 0; i < 4; ++i) {
        speaker.period(1.0 / frequencies[i]); //set the period for the current tone
        speaker.write(0.1); //play the tone at 10% duty cycle. This represents the volume/intensity of the tones that will be produced
        ThisThread::sleep_for(2s); //play for 1200 milliseconds
        speaker.write(0.0); //stop the tone
        ThisThread::sleep_for(300); //add a short pause between tones
    }
}
int main(){
    printf("Playing initial melody...\n");
    playMelody();
    printf("Please type in your first name and press button 1\n");
    char nombre[15];
    int i = 0;
    while (i < 15) {
        char c = getchar();//read character from the console
        if (c == '\n' || c == '\r') {//'\r'stands for 'carriage return' which is essentially something used in antiquated technology
            break;//exit the loop when Enter key is pressed (in most modern computers I know of the enter key is represented by '\r')
        }
        putchar(c);//print the character back to the console
        nombre[i++] = c;//store the character in the array
    }

    nombre[i] = '\0';//null-terminate the string
    printf("\nPlease type in your last name and press button 2\n");
    char apellido[15];
    i = 0;
    while (i < 15) {
        char c = getchar();//read character from the console
        if (c == '\n' || c == '\r') {
            break;//exit the loop when enter key is pressed
        }
        putchar(c);//print character back to console
        apellido[i++] = c;//store character in array
    }
    apellido[i] = '\0';  //null-terminate the string
    printf("\nDisplaying now\n");
    //display first name when button 1 is pressed
    
    while (true) {
        if (button1 == 0) {
            ThisThread::sleep_for(200ms);
            printf("\nDisplaying first name: %s\n", nombre);
            for (int j = 0; j < strlen(nombre); ++j) {
                displayCharacter(nombre[j], 500);
            }
        }
    if(button2 == 0){
        ThisThread::sleep_for(200ms);
        printf("\nDisplaying last name: %s\n", apellido);
        for (int j = 0; j < strlen(apellido); ++j) {
            displayCharacter(apellido[j], 500);
            }

        }
    }

}