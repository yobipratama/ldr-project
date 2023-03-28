#include <Arduino.h>
#include <SimpleDHT.h>

#define pinDHT 6 // SD3 pin signal sensor DHT

byte temperature = 0;
byte humidity = 0;

SimpleDHT11 dht11(D0); // instan sensor dht11

#define sensorLDR A0
int nilaiSensor;
// Deklarasi pin untuk setiap LED
#define pinDHT 6 // SD3 pin signal sensor DHT
#define RED_PIN D1
#define GREEN_PIN D2
#define BLUE_PIN D3
#define trigPin D7
#define echoPin D5

long duration;
int distance;

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  Serial.println("Tugas");
  delay(3000);
}

void loop()
{

  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Pembacaan DHT11 gagal, err=");
    Serial.println(err);
    delay(1000);
    return;
  }

  nilaiSensor = analogRead(sensorLDR);
  if (nilaiSensor <= 1000 && temperature < 24)
  {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }
  else
  {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
  }

  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calculate duration of sound wave
  duration = pulseIn(echoPin, HIGH);

  // Convert duration to distance (in cm)
  distance = duration * 0.034 / 2;

  // if (distance == 2)
  // {
  //   digitalWrite(RED_PIN, LOW);
  //   digitalWrite(GREEN_PIN, LOW);
  //   digitalWrite(BLUE_PIN, HIGH);
  // }
  // else if (distance == 4)
  // {
  //   digitalWrite(RED_PIN, LOW);
  //   digitalWrite(GREEN_PIN, HIGH);
  //   digitalWrite(BLUE_PIN, LOW);
  // }
  // else if (distance == 6)
  // {
  //   digitalWrite(RED_PIN, HIGH);
  //   digitalWrite(GREEN_PIN, LOW);
  //   digitalWrite(BLUE_PIN, LOW);
  // }
  // else if (distance > 6)
  // {
  //   digitalWrite(RED_PIN, HIGH);
  //   digitalWrite(GREEN_PIN, LOW);
  //   digitalWrite(BLUE_PIN, LOW);
  //   delay(1000);

  //   digitalWrite(RED_PIN, LOW);
  //   digitalWrite(GREEN_PIN, HIGH);
  //   digitalWrite(BLUE_PIN, LOW);
  //   delay(1000);

  //   digitalWrite(RED_PIN, LOW);
  //   digitalWrite(GREEN_PIN, LOW);
  //   digitalWrite(BLUE_PIN, HIGH);
  //   delay(1000);
  // }

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Sample OK: ");
  Serial.print((int)temperature);
  Serial.print(" *C, ");
  Serial.println("");
  Serial.print("Nilai Sensor : ");
  Serial.println(nilaiSensor);
  Serial.println("");
  delay(1000);
}
