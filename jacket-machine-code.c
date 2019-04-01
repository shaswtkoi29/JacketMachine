#include <dht.h>

int ledPin=13;
#include "DHT.h"
#define dht_apin A3 // Analog Pin sensor is connected to
#include <SoftwareSerial.h>

// Attach the serial display's RX line to analog pin 4
SoftwareSerial mySerial(3,A4); // pin 4 = TX, pin 3 = RX (unused)

dht DHT;
void setup()
{
pinMode(ledPin,OUTPUT);
Serial.begin(9600);
mySerial.begin(9600);

delay(500);//boot up time
}

void loop() // run over and over again
{
//getting the voltage reading from the temperature sensor
int reading = analogRead(A0);
int reading2= analogRead(A2);

int sensorValue1=0;
int val=0;
int val2=0;
// converting that reading to voltage, for 3.3v arduino use 3.3
float voltage = reading * 5.0;
voltage /= 1024.0;

// print out the voltage
Serial.print(voltage); Serial.println(" volts");

// now print out the temperature
float temperatureC = (voltage - 0.5) * 100 ; //converating from 10 mv per degree wit 500 mV offset
//to degrees ((voltage - 500mV) times 100)
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" "); // clear display
mySerial.write(" ");
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);

mySerial.print("TEMPERATURE HERE= "); mySerial.print(temperatureC) ;mySerial.print(" C");
delay(2000);
sensorValue1 = analogRead(reading2);// read the value from the sensor
val= sensorValue1/4;
Serial.println(val); //Write the value of the photoresistor to the serial monitor.

DHT.read11(A3);
float V= DHT.humidity;
Serial.print("Current humidity = ");
Serial.print(DHT.humidity);
Serial.print("% ");
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" "); // clear display
mySerial.write(" ");
mySerial.write(" ");
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.print("HUMIDITY HERE= ");
mySerial.print(V); mySerial.print("%");

delay(2000);
if(val>0&&val<30){
digitalWrite(ledPin,LOW);
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" "); // clear display
mySerial.write(" ");
mySerial.write(" ");
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" IT IS DARK HERE ");
delay(2000);
}

else if(val>30&& val<120){
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" "); // clear display
mySerial.write(" ");
mySerial.write(" ");
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write("LESS AMOUNT OF LIGHT ");
delay(2000);
}
else if(val>120&& val<250){
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" "); // clear display
mySerial.write(" ");
mySerial.write(" ");
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" IT IS BRIGHT HERE ");
delay(2000);
}
if((V>0)&&(temperatureC>=23)+val<80)
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" "); // clear display
mySerial.write(" ");
mySerial.write(" ");
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write("We don't need jacket ");
delay(2500);
}
else if((V>0) && (temperatureC>=17)+val<90){
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" "); // clear display
mySerial.write(" ");
mySerial.write(" ");
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write("We MAY need jacket ");
delay(2500);
}
else if(V>55){
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" "); // clear display
mySerial.write(" ");
mySerial.write(" ");
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" We MAY need jacket butcarry raincoat");
delay(2500);
}
else {
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" "); // clear display
mySerial.write(" ");
mySerial.write(" ");
mySerial.write(254); // move cursor to beginning of first line
mySerial.write(128);
mySerial.write(" We need jacket ");
delay(2500);
}
}

