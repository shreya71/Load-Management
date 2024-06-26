//LCD_I2C
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

int supply = 100;
//getting signal at A0
int ana_pin = A0;
const int avgval = 400;
long int sense_val = 0;
float volts;
float amps = 0;

//loop
bool run = true;

//to check current
float checkcurrent()
{
  for(int t = 0; t < avgval; t++)
  {
    sense_val += analogRead(ana_pin);
    delay(4);
  }

  //calculations for acs712 sensor to convert sensor 
  sense_val = sense_val / avgval;
  volts = sense_val * 5.0 / 1024.0;
  amps = (volts - 2.5) / 0.185;
  // Serial.print("Current val = ");
  // Serial.print(amps);
  // Serial.println("Amps");
  // Serial.println(volts);
  return amps;
}

void setup() {
  //Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  }

void distributeLoad(float amps) {

  switch(supply) {

    case 100: {
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      break;
    }

    case 80: {
      if(amps > 1.38){
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      }
      if(amps < 1.38)
      {
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      }
      break;
    }
    
    case 70: {
      if(amps > 1.14){
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      }
      if(amps < 1.14)
      {
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      }
      break;
    }
    case 50: {
      if(amps > 0.7){
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      }
      if(amps < 0.7)
      {
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      }
      break;
    }
    case 40: {
      if(amps > 0.49){
      Serial.println("Only critical loads can be turned ON");
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      }
      if(amps < 0.49)
      {
        digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      }
      break;
    }
    case 30: {
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
      break;
    }
  }
}

void loop() {
  if(run)
  {
  // SoC 100%
  supply = 100;
  lcd.print("SOC 100%");
      lcd.setCursor(0,1);
      lcd.print("All Loads ON");
  distributeLoad(amps);
  delay(1000); 
  
  checkcurrent();
  lcd.clear();

  // Soc 80%
  supply = 80;
  lcd.setCursor(1,0);
  lcd.print("SOC 80%");
  distributeLoad(amps);
  delay(1000);

  checkcurrent();
  lcd.clear();

  // SoC 70%
  supply = 70;
  lcd.setCursor(1,0);
  lcd.print("SOC 70%");
  distributeLoad(amps);
  delay(1000);

  checkcurrent();
  lcd.clear();

  // SoC 50%   
  supply = 50;
  lcd.setCursor(1,0);
  lcd.print("SOC 50%");
  distributeLoad(amps);
  delay(2000);

  checkcurrent();
   lcd.clear();

  // SoC 40%  
  supply = 40;
  lcd.setCursor(1,0);
      lcd.print("SOC 40%");
      lcd.setCursor(0,1);
  distributeLoad(amps);
  delay(2000);

  checkcurrent();
   lcd.clear();

  // Soc 30%   system shutdown
  supply = 30;
  lcd.setCursor(1,0);
      lcd.print("SOC 30%");
      lcd.setCursor(0,1);
      lcd.print("System Shutdown");
  distributeLoad(amps);

  run = false;
}
}
