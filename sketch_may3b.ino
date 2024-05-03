#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define pins
#define trigPin 3
#define echoPin 5
#define redLedPin 11
#define greenLedPin 12
#define buzzerPin 8 // Pin for the buzzer

// Define LCD address
#define LCD_ADDRESS 0x27 // Change this address if your LCD has a different address

// Define variables
long duration;
int distance;

// Initialize the LCD with the I2C address and number of columns and rows
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void setup() {
  Serial.begin(9600);
  // Set trigPin as an output
  pinMode(trigPin, OUTPUT);
  // Set echoPin as an input
  pinMode(echoPin, INPUT);
  // Set redLedPin and greenLedPin as outputs
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize the I2C LCD
  lcd.init();
  // Turn on the backlight
  lcd.backlight();

  // Print initial message
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
}

void loop() {
  // Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Set trigPin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Measure echoPin pulse duration
  duration = pulseIn(echoPin, HIGH);
  // Convert duration to distance 
  distance = duration * 0.034 / 2;
  // Turn on red LED if distance is less than 10 cm, otherwise turn on green LED

  Serial.print("Distance : ");
  Serial.println(distance);
  

  lcd.setCursor(9, 0);
  lcd.print("    "); // Clear previous distance
  lcd.setCursor(9, 0);
  lcd.print(distance);
 

  if (distance < 15) {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  } else if (distance >= 7 ) {
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  } else {
    // // Distance is either above 60 or less than 0
    // digitalWrite(redLedPin, LOW);
    // digitalWrite(greenLedPin, LOW);
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  }
  // Wait for 500 milliseconds before measuring again
  delay(500);
}
