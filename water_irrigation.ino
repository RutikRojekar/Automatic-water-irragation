#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 4, 9, 10, 11, 12);

const int sensorPin = A0; 
const int MotorInPin1 = 5;
const int MotorInPin2 = 6;

int sensorValue = 0;
int outputValue = 0;
int percentValue = 0;

bool state = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(MotorInPin1, OUTPUT);
 
 digitalWrite(MotorInPin1,HIGH);

  lcd.setCursor(0, 0);
  lcd.print("Automatic Plant");
  lcd.setCursor(0, 1);
  lcd.print("Watering System");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibrating");
  for (int i = 0; i < 10; i++) {
    if (i == 4)
    {
      lcd.setCursor(0, 1);
      lcd.print(".");
    }
    else  lcd.print(".");
    delay(200);
  }
  lcd.setCursor(5, 1);
  lcd.print("done");
  delay(1000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("SENSOR ACTIVE");
  delay(1500);

}

void loop() {

  sensorValue = analogRead(sensorPin);
  Serial.print("\n\nAnalog Value: ");
  Serial.print(sensorValue);

  percentValue = map(sensorValue, 1023, 100, 0, 100);
  Serial.print("\nPercentValue: ");
  Serial.print(percentValue);
  Serial.print("%");


  if (state == 0)
  {
    if (percentValue < 40)//change the value of percent according to requirement
    {
     motorStart ();
      state = 1;
    }
    else
    {
      motorStop();
      state = 0;
    }
  }

  else if (state == 1)
  {
    if (percentValue < 70)
    {
      motorStart ();
      state = 1;
    }
    else if (percentValue > 70)
    {
      motorStop();
      state = 0;
    }
  }
  delay(1000);
  lcd.clear();
}

void motorStop()

{
  digitalWrite(MotorInPin1,HIGH); // Stop motor
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(percentValue);
  lcd.print(" %");
  lcd.setCursor(0, 1);
  lcd.print("Motor: ");
  lcd.print("OFF");
}
void motorStart ()
{
  digitalWrite(MotorInPin1,LOW); 
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(percentValue);
  lcd.print(" %");
  lcd.setCursor(0, 1);
  lcd.print("Motor: ");
  lcd.print("ON");
}
