#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h> 


#define ONE_WIRE_BUS 7//defineste la ce pin este conectat
#define FAN_PIN 10

OneWire oneWire(ONE_WIRE_BUS);//creaza o instanta a clasei oneWire pentru a comunica cu orice dispozitiv OneWire
DallasTemperature sensors(&oneWire);//trece referinta oneWire la biblioteca DallasTemperature
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//creaza variabila de tip LiquidCrystal

int Contrast=75;
double temp;
int fan = 10;
int fanSpeed;
int LED1 = 9;
int LED2 = 8;
int buzzer = A5;

void setup()
{
    Serial.begin(9600);//incepe comunicarea in serie la o viteza de 9600
    sensors.begin();//porneste biblioteca
    lcd.begin(16, 2);//initializeza dimensiunile LCD -ului
    analogWrite(6, Contrast);//scrie o valoare analogica(PWM), se poate utiliza pentru setarea luminozitatii sau modificarea vitezei
    pinMode(fan, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(buzzer, OUTPUT);
} 

void loop()
{ 
    temp = sensors.getTempCByIndex(0);
    sensors.requestTemperatures();//emite o temperatura globala si solicita toate dispozitivele de pe magistrala
    lcd.setCursor(0, 0);//seteaza locatia in care va fi afisat textul(rand/coloana)
    lcd.print("Temp:    ");//printeaza textul pe LCD
    lcd.print(sensors.getTempCByIndex(0));
    lcd.print("\337C");
    
    if(temp<22)
    {
      analogWrite(fan, 25);
      lcd.setCursor(0, 1);
      lcd.print("   LOW Speed    ");
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      noTone(buzzer);
    }
    else if(temp > 22 && temp < 24)
    {
      analogWrite(fan, 51);
      lcd.setCursor(0, 1);
      lcd.print("Fan Speed:  20% ");
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      noTone(buzzer);
    }
    else if(temp > 24 && temp < 26)
    {
      analogWrite(fan, 102);
      lcd.setCursor(0, 1);
      lcd.print("Fan Speed:  40% ");
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      noTone(buzzer);
    }
    else if(temp > 26 && temp < 28)
    {
      analogWrite(fan, 155);
      lcd.setCursor(0, 1);
      lcd.print("Fan Speed:  60% ");
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      noTone(buzzer);
    }
    else if(temp > 28 && temp <30)
    {
      analogWrite(fan, 205);
      lcd.setCursor(0, 1);
      lcd.print("Fan Speed:  80% ");
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      noTone(buzzer);
    }
    else if(temp >=30)
    {
      analogWrite(fan, 255);
      lcd.setCursor(0, 1);
      lcd.print("Fan Speed:  100% ");
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      tone(buzzer, 1000);
    }
}