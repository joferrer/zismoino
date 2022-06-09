#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 sensor;

int porta_A0 = A0;

int porta_D0 = 2;

int lectura_analogica = 0;
int lectura_digital = 0;

int gx, gy, gz;


void setup()
{
  Serial.begin(9600);
  pinMode(porta_A0, INPUT);
  pinMode(porta_D0, INPUT);
 
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor

  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
  else Serial.println("Error al iniciar el sensor");

}

void loop()
{
  // Leitura dos dados das portas do sensor
  lectura_analogica = analogRead(porta_A0);
  lectura_digital = digitalRead(porta_D0);

    //Serial.print("Lectura Analogica");
    //Serial.println(lectura_analogica);
   
  sensor.getRotation(&gx, &gy, &gz);
  float gx_deg_s = gx * (250.0/32768.0);
  float gy_deg_s = gy * (250.0/32768.0);
  float gz_deg_s = gz * (250.0/32768.0);
  //Mostrar las lecturas separadas por un [tab]
  //Serial.print(" g[x y z](deg/s):\t");
 // Serial.print(gx_deg_s); Serial.print("\t");
  //Serial.print(gy_deg_s); Serial.print("\t");
  //Serial.println(gz_deg_s);


  //HACIA LOS LADOS
  if(lectura_analogica >= 1020 && gy_deg_s >= 235){
    Serial.println("POSIBLE CHOQUE LATERAL Izquierda");
    }
  if( lectura_analogica >= 1020 && gy_deg_s <= -235){
    Serial.println("POSIBLE CHOQUE LATERAL Derecha");
    }
    //HACIA CABALLITO O LAPIZ
  if(lectura_analogica >= 1020 && gx_deg_s >= 235){
    Serial.println("POSIBLE CHOQUE LAPIZ");
    }
  if(lectura_analogica >= 1020 && gx_deg_s <= -235){
    Serial.println("POSIBLE CHOQUE CABALLITO");
    }  

  delay(200);


 
}

  
