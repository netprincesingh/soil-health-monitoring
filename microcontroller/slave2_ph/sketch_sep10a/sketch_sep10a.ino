// ph
#include <Wire.h>
#include <floatToString.h>
#include <SoftwareSerial.h>

#define RE 8
#define DE 7

const byte ph[] = {0x01, 0x03, 0x00, 0x0d, 0x00, 0x01, 0x15, 0xc9};
byte values[11];
SoftwareSerial mod(2, 3);

void setup()
{
  Wire.begin(8); /* join i2c bus with address 8 */

  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);
  mod.begin(9600); // 4800
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  delay(3000);

  /* start serial for debug */
}

void loop()
{
  delay(100);
}

float phv()
{
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);

  if (mod.write(ph, sizeof(ph)) == 8) //
  {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++) // 7
    {
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }

  float soil_ph = float(values[4]) / 10;
  Serial.print("Soil Ph: ");
  Serial.println(soil_ph, 1);
  Serial.print(values[4], 1);

  return soil_ph;

  delay(2000);
}
// function that executes whenever data is requested from master
void requestEvent()
{

  char s[5];
  float a = phv();
  floatToString(a, s, sizeof(s), 2);

  Wire.write(s);
}