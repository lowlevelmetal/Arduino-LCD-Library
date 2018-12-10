// Custom LCD Library Test - 4Bit Mode
// 16 x 2 LCD Based On HD44780

// Matthew Geiger

// Define Pins
#define LCD_RS 2
#define LCD_RW 3
#define LCD_E  4
#define LCD_D0 5
#define LCD_D1 6
#define LCD_D2 7
#define LCD_D3 8
#define LCD_D4 9
#define LCD_D5 10
#define LCD_D6 11
#define LCD_D7 12

// Setup LCD
void SetupLCD() {
  // Set Pins for Output
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_RW, OUTPUT);
  pinMode(LCD_E,  OUTPUT);
  pinMode(LCD_D0, OUTPUT);
  pinMode(LCD_D1, OUTPUT);
  pinMode(LCD_D2, OUTPUT);
  pinMode(LCD_D3, OUTPUT);
  pinMode(LCD_D4, OUTPUT);
  pinMode(LCD_D5, OUTPUT);
  pinMode(LCD_D6, OUTPUT);
  pinMode(LCD_D7, OUTPUT);
  
  // Run INIT
  InitLCD();
  
  // Give LCD Time To Catch Up
  delay(100);
}

void PullDownBus() {
  digitalWrite(LCD_D0, LOW);
  digitalWrite(LCD_D1, LOW);
  digitalWrite(LCD_D2, LOW);
  digitalWrite(LCD_D3, LOW);
  digitalWrite(LCD_D4, LOW);
  digitalWrite(LCD_D5, LOW);
  digitalWrite(LCD_D6, LOW);
  digitalWrite(LCD_D7, LOW);
}

// Send Character
void SendCharacter(char cCharacter) {
 SendCommand(byte(cCharacter), 0x1);
}

// Init LCD
void InitLCD() {
  // Start Communication Timing
  digitalWrite(LCD_E, LOW);
  digitalWrite(LCD_RW, LOW);
  
  // Run LCD 4Bit Init
  InitSequence();
  
  // Reset Screen and Cursor
  // Configure Dimensions
  SendCommand(0b00101100, 0x0);
  // Turn on Screen, Enable Cursor, and Blink Cursor
  SendCommand(0b00001111, 0x0);
  // Clear Display
  SendCommand(0b00000001, 0x0);
  //Set Print from Left To Write
  SendCommand(0b00000110, 0x0);
} 

// LCD 4Bit Init
void InitSequence() {
 // LCD Init Commands for 4Bit Mode
 write4(0b0011);
 write4(0b0011);
 write4(0b0011);
 write4(0b0010);
 
}

void write4(byte cCharacter) {
  digitalWrite(LCD_RW, LOW);
  digitalWrite(LCD_RS, LOW);
  
  // Communication Timing
  delayMicroseconds(1);
  
  // Write Data
  if((cCharacter >> 0) & 1) {
   digitalWrite(LCD_D4, HIGH); 
  } else { 
   digitalWrite(LCD_D4, LOW);
  }
  
  if((cCharacter >> 1) & 1) {
   digitalWrite(LCD_D5, HIGH); 
  } else { 
   digitalWrite(LCD_D5, LOW);
  }
  
  if((cCharacter >> 2) & 1) {
   digitalWrite(LCD_D6, HIGH); 
  } else { 
   digitalWrite(LCD_D6, LOW);
  }
  
  if((cCharacter >> 3) & 1) {
   digitalWrite(LCD_D7, HIGH); 
  } else { 
   digitalWrite(LCD_D7, LOW);
  }
  
  // Pulse Enable
  ClockPulse();
}

// Sends Write Command
void SendCommand(byte cCharacter, byte bBool) {
  digitalWrite(LCD_RW, LOW);
  
  // Select Register
  if(bBool) {
   digitalWrite(LCD_RS, HIGH);
  } else {
   digitalWrite(LCD_RS, LOW);
  }
  
  // Communication Timing
  delayMicroseconds(1);
 
  // Send First Section of ASCII
  if((cCharacter >> 4) & 1) {
   digitalWrite(LCD_D4, HIGH); 
  }else { 
   digitalWrite(LCD_D4, LOW);
  }
  
  if((cCharacter >> 5) & 1) {
   digitalWrite(LCD_D5, HIGH); 
  } else { 
   digitalWrite(LCD_D5, LOW);
  }
  
  if((cCharacter >> 6) & 1) {
   digitalWrite(LCD_D6, HIGH); 
  } else { 
   digitalWrite(LCD_D6, LOW);
  }
  
  if((cCharacter >> 7) & 1) {
   digitalWrite(LCD_D7, HIGH); 
  } else { 
   digitalWrite(LCD_D7, LOW);
  }
  
  // Pulse Enable
  ClockPulse();
  
  // Send Second Section of ASCII
  if((cCharacter >> 0) & 1) {
   digitalWrite(LCD_D4, HIGH); 
  } else { 
   digitalWrite(LCD_D4, LOW);
  }
  
  if((cCharacter >> 1) & 1) {
   digitalWrite(LCD_D5, HIGH); 
  } else { 
   digitalWrite(LCD_D5, LOW);
  }
  
  if((cCharacter >> 2) & 1) {
   digitalWrite(LCD_D6, HIGH); 
  } else { 
   digitalWrite(LCD_D6, LOW);
  }
  
  if((cCharacter >> 3) & 1) {
   digitalWrite(LCD_D7, HIGH); 
  } else { 
   digitalWrite(LCD_D7, LOW);
  }
  
  // Pulse Enable
  ClockPulse();
  
  // Pull Bus LOW
  PullDownBus();
}

// Pulse Enable
void ClockPulse() {
 delayMicroseconds(1);
 digitalWrite(LCD_E, HIGH);
 delayMicroseconds(1);
 digitalWrite(LCD_E, LOW);
 delayMicroseconds(1);
 
}

// Sends String
void SendPhrase(char *szPhrase) {
 // Send Characters
 for(int i = 0; i < strlen(szPhrase); i++) {
   SendCharacter(byte(szPhrase[i]));
 }
}

void SetCursor(byte choice) {
  if(choice == 0x0) {
    SendCommand(0b00001100, 0x0);
  } else {
    SendCommand(0b00001111, 0x0);
  }
}

void ClearScreen() {
  SendCommand(0b00000001, 0x0);
}

void setup() {
  // Initialize LCD
  SetupLCD();
  
  // Stop Cursor
  SetCursor(0);
}
  
void loop() {
  SendPhrase("Driver Test");
  delay(1500);
  ClearScreen();
  delay(1500);
}
