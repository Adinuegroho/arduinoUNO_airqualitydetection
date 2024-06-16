#include "MQ7.h"      // Library MQ7
MQ7 mq7(A0, 5.0);

#include "DHT.h"          // Library DHT
#define relay 2       // Inisialisasi Relay
#define DHTPIN A1          // Inisialisasi DHT
#define DHTTYPE DHT22

#include "MQ135.h"      // Library MQ135
#define SENSORPIN A2    // Inisialisasi Sensor
#define RZERO 206.85      // kalibrasi sensor
MQ135 gasSensor = MQ135(SENSORPIN);

DHT dht (DHTPIN,DHTTYPE);
float kelembapan;
int monoksida;
float dioksida;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  float rzero = gasSensor.getRZero();
  pinMode(relay, OUTPUT);
}

void loop() {
  
  kelembapan = dht.readTemperature();  // Baca Suhu
  Serial.println(kelembapan);

  monoksida = mq7.getPPM();   // Baca CO
  Serial.print("Karbon Monoksida : ");
  Serial.println(monoksida); 

  dioksida = gasSensor.getPPM(); // Baca CO2
  Serial.println("Karbon Dioksida (in PPM): ");
  Serial.println(dioksida);

  if (kelembapan >= 20.0 && monoksida >= 20  && dioksida >= 20.0) {
          Serial.println("Kualitas udara bersih!");
          digitalWrite(relay, HIGH);    // Jika Relay High akan menyalakan kipas
  } else {
          Serial.println("Kualitas udara buruk!");
          digitalWrite(relay, LOW);   // Jika Relay Low akan mematikan kipas
  }

  delay(3000);
}
