#include <Arduino.h>
#include <DHT.h>

#define sensorLDR A0
#define LED_R D1
#define LED_G D2
#define LED_B D3

#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
int nilaiSensor;

void setup()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  Serial.begin(115200);
  dht.begin();
  Serial.println("Contoh Penggunaan Sensor LDR dan DHT11");
  delay(3000);
}

void loop()
{
  nilaiSensor = analogRead(sensorLDR);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(nilaiSensor < 60 ){
    analogWrite(LED_R, 255); // LED Merah mati
    analogWrite(LED_G, 0); // LED Hijau nyala
    analogWrite(LED_B, 0); // LED Biru mati
  }else{
    analogWrite(LED_R, 0); // LED Merah mati
    analogWrite(LED_G, 0); // LED Hijau nyala
    analogWrite(LED_B, 255); // LED Biru mati
  }

  Serial.print("Nilai Sensor : ");
  Serial.println(nilaiSensor);

  if (isnan(h) || isnan(t)) {
    Serial.println("Berhasil membaca suhu dan kelembaban");
  } else {
    Serial.print("Suhu: ");
    Serial.print(t);
    Serial.print(" C, Kelembaban: ");
    Serial.print(h);
    Serial.println(" %");
  }

  delay(1000);
}
