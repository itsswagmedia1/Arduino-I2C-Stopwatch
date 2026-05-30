#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// (If 0x27 doesn't work, try 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Definitions
const int startStopButtonPin = 2; // Button 1: Start / Stop (or Continue)
const int resetButtonPin = 3;     // Button 2: Reset

// Stopwatch Timing Variables
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long pausedTime = 0;
bool isRunning = false;

// Button State Variables (for debouncing)
bool lastStartStopState = HIGH;
bool lastResetState = HIGH;

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Set up button pins with internal pull-up resistors
  pinMode(startStopButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  
  // Initial Display Status
  showReadyScreen();
}

void loop() {
  // Read current button states
  bool currentStartStopState = digitalRead(startStopButtonPin);
  bool currentResetState = digitalRead(resetButtonPin);

  // --- START / STOP BUTTON LOGIC ---
  if (currentStartStopState == LOW && lastStartStopState == HIGH) {
    delay(50); // Simple debounce delay
    if (!isRunning) {
      // Starting or Continuing the stopwatch
      startTime = millis() - pausedTime;
      isRunning = true;
    } else {
      // Stopping/Pausing the stopwatch
      pausedTime = millis() - startTime;
      isRunning = false;
    }
  }
  lastStartStopState = currentStartStopState;

  // --- RESET BUTTON LOGIC ---
  if (currentResetState == LOW && lastResetState == HIGH) {
    delay(50); // Simple debounce delay
    if (!isRunning) {
      // Only reset if the stopwatch is currently paused
      elapsedTime = 0;
      pausedTime = 0;
      showReadyScreen();
    }
  }
  lastResetState = currentResetState;

  // --- TIME UPDATE LOGIC ---
  if (isRunning) {
    elapsedTime = millis() - startTime;
    displayTime(elapsedTime);
  }
}

// Helper to show the initial screen
void showReadyScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stopwatch Ready");
  lcd.setCursor(0, 1);
  lcd.print("Time: 00:00:00");
}

// Helper to format and display milliseconds to MM:SS:CC (Centiseconds)
void displayTime(unsigned long totalMillis) {
  unsigned long totalSeconds = totalMillis / 1000;
  unsigned long minutes = totalSeconds / 60;
  unsigned long seconds = totalSeconds % 60;
  unsigned long centiseconds = (totalMillis % 1000) / 10; // 1/100th of a second

  lcd.setCursor(0, 0);
  lcd.print("Stopwatch Run  "); // Clears old "Ready" text safely
  
  lcd.setCursor(6, 1); // Jump straight to where the numbers sit
  
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
  lcd.print(":");
  
  if (centiseconds < 10) lcd.print("0");
  lcd.print(centiseconds);
}