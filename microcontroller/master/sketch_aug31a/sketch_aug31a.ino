// master
#include <Wire.h>

void setup()
{
  Serial.begin(9600); /* begin serial for debug */
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1=A4 and SCL=D2=A5 of NodeMCU */
}

void loop()
{

  Wire.requestFrom(8, 4); /* request & read data of size 13 from slave */
  while (Wire.available())
  {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.print("ph ");
  Serial.println();

  //////////////////////////////////////////////////////////////////////////////

  Wire.requestFrom(9, 20); /* request & read data of size 13 from slave */
  while (Wire.available())
  {
    char d = Wire.read();
    Serial.print(d);
  }
  Serial.print("NPK  ");
  Serial.println();

  //////////////////////////////////////////////////////////////////////////////

  Wire.requestFrom(10, 15); /* request & read data of size 13 from slave */
  while (Wire.available())
  {
    char c = Wire.read();

    Serial.print(c);
  }
  Serial.print("hum & temp ");
  Serial.println();

  delay(1000);
}
