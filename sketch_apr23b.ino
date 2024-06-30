// Include library for LCD and define pins
#include "LiquidCrystal.h"

////////////////////////LCD///////////////////////////////////////
const int rs = 9, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/////////////////////////////////////////////////////////////////

#define GasSensorPin A5 
const int buzzer = 11;
const int mq135_aqi_sensor = A3;
int aqi_ppm = 0;
int smokeA0 = A1;

///// Your threshold value///////
int sensorThres = 500;
////////////////////////////////
void setup() 
{
  analogWrite(2,20);
  pinMode (mq135_aqi_sensor, INPUT);
  pinMode(smokeA0, INPUT);
  pinMode (buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  // Initiate serial and lcd communication
  Serial.begin (9600);
  lcd.clear();
  lcd.begin (16, 2);

  Serial.println("AQI Alert System");
  //lcd.setCursor(0, 0);
  //lcd.print("AQI Alert System");
  delay(1000);
}

void loop() {
  
  //////////////////mq-9 sensor//////////////////////////
  int gasValue = analogRead(GasSensorPin);

  int gasThreshold = 350; 

  lcd.setCursor(0, 0);
  lcd.print("MQ-9 SENSOR: ");
  lcd.print(gasValue);
  //lcd.setCursor(0, 1);
  //lcd.print("                ");
  delay(2000);
  //lcd.clear();
  Serial.print("MQ-9 SENSOR:   ");
  Serial.println(gasValue);
  if (gasValue > gasThreshold) {

    while(gasValue > gasThreshold)
    {
      if(gasValue > gasThreshold)
      {
    gasValue = analogRead(GasSensorPin);
    digitalWrite(buzzer, HIGH);
    Serial.println("Gas detected! Buzzer is ON");
    Serial.print("MQ-9 SENSOR:   ");
    Serial.println(gasValue);
    lcd.setCursor(0, 0);
  lcd.print("Gas detected!");
  delay(1000);
  lcd.clear();
      }
      else{
        break;
      }
    }
  } else {
    digitalWrite(buzzer, LOW);
    Serial.println("No gas detected. Buzzer is OFF");
      lcd.setCursor(0, 1);
      lcd.print("No gas detected!");
      delay(2000);
      lcd.clear();
  }
//////////////////////////////////////////////////////////////////
/////////////////////////mq-135/////////////////////////////////////////
   aqi_ppm = analogRead(mq135_aqi_sensor);

  Serial.print("Air Quality: ");
  Serial.println(aqi_ppm);

  lcd.setCursor(0, 0);
  lcd.print("Air Quality: ");
  lcd.print(aqi_ppm);
  lcd.print("\n ");
  delay(2000);

  if ((aqi_ppm >= 0) && (aqi_ppm <= 50))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Good");
    delay(2000);
    Serial.println("AQI Good"); 
  }
  else if ((aqi_ppm >= 51) && (aqi_ppm <= 100))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Moderate");
    delay(2000);
    lcd.clear();
    Serial.println("AQI Moderate");
  }
  else if ((aqi_ppm >= 101) && (aqi_ppm <= 200))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Unhealthy");
    delay(2000);
    lcd.clear();
    Serial.println("AQI Unhealthy");
  }
  else if ((aqi_ppm >= 201) && (aqi_ppm <= 300))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI V. Unhealthy");
    delay(2000);
    lcd.clear();
    Serial.println("AQI V. Unhealthy");
  }
  else if (aqi_ppm >= 301)
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Hazardous");
    delay(2000);
    lcd.clear();
    Serial.println("AQI Hazardous");
  } 
  ////////////////////////mq-2///////////////////////////////////////////
  int analogSensor = analogRead(smokeA0);

  lcd.setCursor(0, 0);
  lcd.print("MQ-2 SENSOR: ");
  lcd.print(analogSensor);
  delay(2000);
  //lcd.clear();
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);

  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    while(analogSensor > sensorThres)
    {
      if (analogSensor > sensorThres)
      {
    analogSensor = analogRead(smokeA0);
    digitalWrite(buzzer,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("smoke detected!");
    Serial.print("Pin A0: ");
    Serial.println(analogSensor);
    delay(1000);
    lcd.clear();
      }
      else
      {
        break;
      }
    }
  }
  else
  {
    digitalWrite(buzzer,LOW);
    lcd.setCursor(0, 1);
    lcd.print("No Smoke Detect");
    delay(1000);
    lcd.clear();
  }
  ///////////////////////////////////////////////////////////////////
 // delay (700);
}
