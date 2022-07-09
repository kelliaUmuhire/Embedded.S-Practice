// DECLARE THE PINS
#include <LiquidCrystal_I2C.h>
int LED_PIN = 13;
int echoPin = 12;
int trigPin = 14;

LiquidCrystal_I2C lcd(0x27, 16, 2);
// SETUP THE ENV, DETERMINE OUTPUT AND INPUT PINS
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  lcd.begin(5,4);
  lcd.init();
  lcd.backlight();
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
}

void loop() {
  //write to lcd
  lcd.setCursor(0,0);
  lcd.print("Here we come");

//FIRST TURN OFF THE LED
digitalWrite(LED_PIN, LOW);

// PREPARE TRIGPIN TO OUTPUT
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
int duration = pulseIn(echoPin, HIGH);
int distance = (duration/2)/29.1;



if(distance >= 50 || distance<= 0) {
  digitalWrite(LED_PIN, LOW);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Out of Range");
  
  Serial.println(distance);
  Serial.println("Out of Range");
  }
  else{
    Serial.println(distance);
    Serial.println("cm");
      
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(distance);
    lcd.print("cm");
    digitalWrite(LED_PIN, HIGH);
    }
  delay(50);
}