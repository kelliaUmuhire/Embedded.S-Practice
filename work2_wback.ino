#include <ESP8266WiFi.h>
WiFiClient wifiClient;

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
  
 WiFi.begin("RCA-WiFi", "rca@2019");
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

  
  String mData="";
  String device_name = "tbg";
  mData = "device="+device_name+"&distance="+distance;
  sendData(80, "insecure.benax.rw", "/iot/" , mData); 
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

void sendData(const int Port, const char* host,const char* filepath , String data){
  
  wifiClient.connect(host, Port); 

  wifiClient.println("POST "+(String)filepath+" HTTP/1.1");
  wifiClient.println("Host: " + (String)host);
  wifiClient.println("User-Agent: ESP8266/1.0");
  
  wifiClient.print(data);

  Serial.println("Response: " + wifiClient.readStringUntil('\n'));
}