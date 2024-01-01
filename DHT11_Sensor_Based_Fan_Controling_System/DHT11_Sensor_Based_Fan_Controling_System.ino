#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 7        
#define DHTTYPE DHT11  

#define MOTOR_PIN_ENA 9  
#define MOTOR_PIN_IN1 10 
#define MOTOR_PIN_IN2 11 

#define TEMPERATURE_THRESHOLD 28 
#define TEMPERATURE_THRESHOLD1 32 

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup() {
  Serial.begin(9600);
  dht.begin();

  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
}

void loop() {
  delay(2000); 

  float temperature = dht.readTemperature(); 
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  lcd.setCursor(0, 1); 
  lcd.print("                "); 

  if (temperature > TEMPERATURE_THRESHOLD1) {
    analogWrite(MOTOR_PIN_ENA, 255);    
    digitalWrite(MOTOR_PIN_IN1, HIGH);  
    digitalWrite(MOTOR_PIN_IN2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("FAN Speed: Max");
  }
  else if (temperature > TEMPERATURE_THRESHOLD) {
    analogWrite(MOTOR_PIN_ENA, 100);    
    digitalWrite(MOTOR_PIN_IN1, HIGH); 
    digitalWrite(MOTOR_PIN_IN2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("FAN Speed: Med");
  }
  else {
    // Decrease motor speed
    analogWrite(MOTOR_PIN_ENA, 45);   
    digitalWrite(MOTOR_PIN_IN1, HIGH);  
    digitalWrite(MOTOR_PIN_IN2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("FAN Speed: Low");
  }

  lcd.setCursor(12, 0); 
  lcd.print(temperature); 
}
