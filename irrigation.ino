
//Include the library files
#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <SFE_BMP180.h>

//Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Create an object for the BMP180 sensor
SFE_BMP180 bmp;

char auth[] = "QVaEWHBzO4lKx5kIJ0HQ_xhPBLo4IaJF";//Enter your Auth token
char ssid[] = "himanshu";//Enter your WIFI name
char pass[] = "12345678";//Enter your WIFI password

DHT dht(D8, DHT11);//(sensor pin,sensor type)
BlynkTimer timer;
//Define component pins
 #define relay3 D5
#define relay1 D3
#define relay2 D4
#define rain A0
 #define trig D6
#define echo D7

//Create three variables for pressure
double T, P;
char status;

void setup() {
  Serial.begin(9600);
  bmp.begin();
  lcd.init();
  lcd.backlight();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);  
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print(" Monitor");
  lcd.setCursor(4, 1);
  lcd.print("System");
  delay(4000);
  lcd.clear();

//Call the functions
  timer.setInterval(100L, DHT11sensor);
  timer.setInterval(100L, pressure);
  timer.setInterval(100L, rainSensor);
  timer.setInterval(100L, ultrasonic);  
}

//Get the DHT11 sensor values
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t);

  lcd.setCursor(8, 0);
  lcd.print("H:");
  lcd.print(h);

}

//Get buttons values
BLYNK_WRITE(V4) {
 bool RelayOne = param.asInt();
  if (RelayOne == 1) {
    digitalWrite(relay1, LOW);
  } else {
    digitalWrite(relay1, HIGH);
  }
}

//Get buttons values
BLYNK_WRITE(V6) {
 bool Relaythree = param.asInt();
  if (Relaythree == 1) {
    digitalWrite(relay3, LOW);
  } else {
    digitalWrite(relay3, HIGH);
  }
}

//Get the rain sensor values
void rainSensor() {
  int value = analogRead(rain);
  value = map(value, 0, 1024, 0, 100);
  Blynk.virtualWrite(V2, value);

  lcd.setCursor(0, 1);
  lcd.print("R:");
  lcd.print(value);
  lcd.print(" ");
}
//Get buttons values
BLYNK_WRITE(V5) {
 bool RelayTwo = param.asInt();
  if (RelayTwo == 1) {
    digitalWrite(relay2, LOW);
  } else {
    digitalWrite(relay2, HIGH);
  }
}

//Get the pressure values
void pressure() {
  status =  bmp.startTemperature();
  if (status != 0) {
    delay(status);
    status = bmp.getTemperature(T);

    status = bmp.startPressure(3);// 0 to 3
    if (status != 0) {
      delay(status);
      status = bmp.getPressure(P, T);
      if (status != 0) {

      }
    }
  }

  Blynk.virtualWrite(V3, P);
  lcd.setCursor(8, 1);
  lcd.print("P:");
  lcd.print(P);
  delay(1000);
  }


//Get the ultrasonic sensor values
void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Blynk.virtualWrite(V7, cm);

  lcd.setCursor(8, 1);
  lcd.print("W:");
  lcd.print(cm);
  lcd.print("  ");
}



void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}
