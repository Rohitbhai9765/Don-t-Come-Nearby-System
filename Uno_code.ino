#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define trigPin 9
#define echoPin 10
#define buzzPin 7
 
// Initialize the LCD with the I2C address
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.setCursor(0, 0); // Set cursor to column 0, row 0
  lcd.print("Hello, Rohit!"); // Print message on the first line
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.0343 / 2;

  if(distance < 20){
    digitalWrite(buzzPin, HIGH);
  }
  else{
    digitalWrite(buzzPin, LOW);   
  }


  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");



  lcd.setCursor(0, 0); 
  lcd.print("Distance(cm):"); 
  
  lcd.setCursor(0, 1); // Move to the second line
  lcd.print(distance); // Print message on the second line
  delay(200);
  lcd.clear(); // Clear the screen
  delay(200);

  


  
  
}
