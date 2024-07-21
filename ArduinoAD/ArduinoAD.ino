#include <Adafruit_BME680.h>
#include <bme68x.h>
#include <bme68x_defs.h>

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_BME680 bme; 
#define SEALEVELPRESSURE_HPA (1013.25)

#define BUTTON_PIN 10 

void setup(){
  Serial.begin(9600); 
  while(!Serial); 
  lcd.begin(16,2); 
  // lcd.print("hello, w");
  // lcd.setCursor(0,1);
  // lcd.print("orld!");
  if(!bme.begin()){
    while(1) Serial.println("BME fail"); 
  }
  else {
    Serial.println("bme success"); 
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

enum Mode {
  TEMP,
  PRES,
  HUM,
  GAS,
  ALT
};

int choice = 0; 
bool pressed = false; 

void loop(){
  // Serial.println("hello"); 
  if(!bme.performReading()){
    Serial.println("bad reading"); 
    return; 
  }

  switch(choice){
    case TEMP:
      lcd.setCursor(0,0); 
      lcd.print("Temp =");
      lcd.setCursor(0,1); 
      lcd.print((String)(bme.temperature) + "*C");
      break;
    case PRES:
      lcd.setCursor(0,0); 
      lcd.print("Pres =");
      lcd.setCursor(0,1); 
      lcd.print((String)(bme.pressure) + "hPa");
      break;
    case HUM:
      lcd.setCursor(0,0); 
      lcd.print("Hum =");
      lcd.setCursor(0,1); 
      lcd.print((String)(bme.humidity) + "%");
      break;
    case GAS:
      lcd.setCursor(0,0); 
      lcd.print("Gas =");
      lcd.setCursor(0,1); 
      lcd.print((String)(bme.gas_resistance / 1000.0) + "KO");
      break;
    case ALT:
      lcd.setCursor(0,0); 
      lcd.print("Alt =");
      lcd.setCursor(0,1); 
      lcd.print((String)(bme.readAltitude(SEALEVELPRESSURE_HPA)) + "m");
      break;
    default:
      lcd.setCursor(0,0);
      lcd.print("error"); 
  }

  if(digitalRead(BUTTON_PIN) == 0 && !pressed){
    choice = (choice + 1) % 5;
    lcd.clear(); 
    pressed = true; 
  }
  else if(digitalRead(BUTTON_PIN) == 1){
    pressed = false; 
  }
  
}