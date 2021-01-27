// EN.605.715.81.SP21 Software Development for Real-Time Embedded Systems
// Project 1 - Morse Code LED System Development
// Douglas Eucken
// Jan, 27th 2021

// Morse code generator for Arduino DUO (uses onboard LED)
// Takes serial input in the form of characters and displays as Morse code
// Program exits after sentinel character ("#") is recieved

int ledPin = 13;                       // Onboard active led pin
int tempo = 500;                       // timing value
bool done = false;                     // Sentinel character flag

void setup () {
 pinMode(ledPin, OUTPUT);
 start();
}

void start(){                         
 // Open serial port to PC
 Serial.begin(9600); 
   
 // Show welcome message on serial output
 Serial.println("EN.605.715.81.SP21 Software Development for Real-Time Embedded Systems");
 Serial.println("Project 1 - Morse Code LED System Development");
 Serial.println("Douglas Eucken");
 Serial.println("");
 Serial.println("This program translates your message into Morse code and flashes it on the onboard Arduino LED.");
 Serial.println("Enter your message or # to exit: ");
}

// Subroutine for dot output to LED
void dot() {
 digitalWrite(ledPin, HIGH);
 delay(1 * tempo);
 digitalWrite(ledPin, LOW);
 delay(1 * tempo);
}

// Subroutine for dash output to LED
// Each dash is traditionally twice as long as a dot, but I made it 3 times for visual clarity
void dash() {
 digitalWrite(ledPin, HIGH);
 delay(3 * tempo);
 digitalWrite(ledPin, LOW);
 delay(1 * tempo);
}

// Subroutine to determine which letter has been entered and call dot/dash subroutines
void morse(byte letter) {
 //Serial.println(letter, DEC);
 if (letter == 'a' or letter == 'A') {dot(); dash();}
 if (letter == 'b' or letter == 'B') {dash(); dot(); dot(); dot();}
 if (letter == 'c' or letter == 'C') {dash(); dot(); dash(); dot();}
 if (letter == 'd' or letter == 'D') {dash(); dot(); dot();}
 if (letter == 'e' or letter == 'E') {dot();}
 if (letter == 'f' or letter == 'F') {dot(); dot(); dash(); dot();}
 if (letter == 'g' or letter == 'G') {dash(); dash(); dot();}
 if (letter == 'h' or letter == 'H') {dot(); dot(); dot(); dot();}
 if (letter == 'i' or letter == 'I') {dot(); dot();}
 if (letter == 'j' or letter == 'J') {dot(); dash(); dash(); dash();}
 if (letter == 'k' or letter == 'K') {dash(); dot(); dash();}
 if (letter == 'l' or letter == 'L') {dot(); dash(); dot(); dot();}
 if (letter == 'm' or letter == 'M') {dash(); dash();}
 if (letter == 'n' or letter == 'N') {dash(); dot();}
 if (letter == 'o' or letter == 'O') {dash(); dash(); dash();}
 if (letter == 'p' or letter == 'P') {dot(); dash(); dash(); dot();}
 if (letter == 'q' or letter == 'Q') {dash(); dash(); dot(); dash();}
 if (letter == 'r' or letter == 'R') {dot(); dash(); dot();}
 if (letter == 's' or letter == 'S') {dot(); dot(); dot();}
 if (letter == 't' or letter == 'T') {dash();}
 if (letter == 'u' or letter == 'U') {dot(); dot(); dash();}
 if (letter == 'v' or letter == 'V') {dot(); dot(); dot(); dash();}
 if (letter == 'w' or letter == 'W') {dot(); dash(); dash();}
 if (letter == 'x' or letter == 'X') {dash(); dot(); dot(); dash();}
 if (letter == 'y' or letter == 'Y') {dash(); dot(); dash(); dash();}
 if (letter == 'z' or letter == 'Z') {dash(); dash(); dot(); dot();}
 if (letter == '1') {dot(); dash(); dash(); dash(); dash();}
 if (letter == '2') {dot(); dot(); dash(); dash(); dash();}
 if (letter == '3') {dot(); dot(); dot(); dash(); dash();}
 if (letter == '4') {dot(); dot(); dot(); dot(); dash();}
 if (letter == '5') {dot(); dot(); dot(); dot(); dot();}
 if (letter == '6') {dash(); dot(); dot(); dot(); dot();}
 if (letter == '7') {dash(); dash(); dot(); dot(); dot();}
 if (letter == '8') {dash(); dash(); dash(); dot(); dot();}
 if (letter == '9') {dash(); dash(); dash(); dash(); dot();}
 if (letter == '0') {dash(); dash(); dash(); dash(); dash();}

 // Wait 3 * tempo for space
 if (letter == ' ') {delay(4 * tempo);}
}

// Main program loop
void loop () {
 char ch;
 
 // This while loop waits for a string, displays it in Morse code, and only exits the loop if the sentinel is entered. 
 while (!done) {
   
    // Check to see if there are letters or numbers available to be read
    if (Serial.available()) {     
   
      // Read one letter or number at a time
      // Serial.read() returns the first (oldest) character in the buffer and removes that byte of data from the buffer
      ch = Serial.read();

      // Print the character to serial which is being displayed and skip CR and LF
      // Also causes serial TX LED to show the beginning of each new character of Morse
      if (ch != 10 and ch != 13)
        Serial.println(ch);
        delay(tempo);
      
      // Check for sentinel value
      if (ch == '#') {
       done = true;  
       Serial.println("Sentinel value of # entered, program will now exit.");
      }

      // If no sentinel, call morse subroutine for current character
      else {
        morse(ch);
      }
    }
 }
 // If sentinel is entered just loop forever
 // Power reset or reset button required to restart
 while(true) {} 
}
