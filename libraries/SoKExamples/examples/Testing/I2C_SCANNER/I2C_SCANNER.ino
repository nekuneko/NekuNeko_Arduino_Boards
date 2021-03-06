#include <Wire.h>

// By default, scan is performed on internal I2C
#define Wire Wire1 //*/ // Comment this line to scan external I2C devices

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  
  while (!Serial);            
  Serial.println("\nI2C Scanner");

  /*/ Enable this lines if you are testing I2C devices on 
  // NeKuNeKo's SoK Radio Station in order to enable Si4713
  pinMode(SOK, OUTPUT);
  digitalWrite(SOK, HIGH);
  // */
}


void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}
