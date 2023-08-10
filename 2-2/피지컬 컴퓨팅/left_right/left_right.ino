#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int rightBtn = 10;
const int leftBtn = 11;
const int jumpBtn = 2;
const int tilt = 12;
const int light = 0;

String str[4];
int state = 0;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.begin();

  pinMode(rightBtn, INPUT);
  pinMode(leftBtn, INPUT);
  pinMode(jumpBtn, INPUT);
  pinMode(tilt, INPUT);

  digitalWrite(rightBtn, HIGH);
  digitalWrite(leftBtn, HIGH);
  digitalWrite(jumpBtn, HIGH);
  digitalWrite(tilt, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(rightBtn) == LOW)
  {
    Serial.write(1);
    Serial.flush();
    lcd.clear();
    lcd.print("Left");
  }

  if (digitalRead(leftBtn) == LOW)
  {
    Serial.write(2);
    Serial.flush();
    lcd.clear();
    lcd.print("Right");
  }

  if (analogRead(light) > 50)
  {
    Serial.write(4);
    Serial.flush();
    lcd.clear();
    lcd.print("SUN");
  }

  if (digitalRead(tilt) == HIGH)
  {
    Serial.write(5);
    Serial.flush();
    lcd.clear();
    lcd.print("WATER");
  }

  if (Receive() == 1)
  {
    if (digitalRead(jumpBtn) == HIGH)
    {
      if (state == 0)
        state = 1;
    }

    if (digitalRead(jumpBtn) == LOW)
    {
      if (state == 1)
      {
        lcd.clear();

         if (count == 5)
        count = 0;

        String line = text(count);
        int len = line.length();
        
        if (len > 16)
        {
          lcd.print(line);
          lcd.setCursor(0, 1);
          lcd.print(line.substring(15));
        }
        
        ++count;
        
        state = 0;
      }
    }
  }
  delay(10);
}

int Receive()
{
  char data;
  if (Serial.available())
    data = Serial.read();

  if (data == 'F')
    return 1;
  else
    return -1;
}

String text(int count) {
  str[0] = "The Greatest Gift";
  str[1] = "you can give someone is";
  str[2] = "Your TIME, Your Attention,";
  str[3] = "Your Love, Your Concern";

  return str[count];
}
