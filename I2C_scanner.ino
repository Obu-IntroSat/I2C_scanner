#include <Wire.h>
#include <IS_Bluetooth.h>

void setup(){
  delay(500);
  Wire.begin();
  delay(500);
  Serial.begin(115200, SERIAL_8E1);
  Serial.println("\nI2C Scanner");

} 

void loop(){  

if (Serial.available()) {
    char command = Serial.read();
    if (command == 'b') {
      enter_bootloader();
    }
  }

  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 8; address < 127; address++ ) {
    Wire.beginTransmission(address);
    delay(100);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(1000);
}
