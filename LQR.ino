#include <Servo.h>
Servo myservo;
const int sensordistancia = A0;
long D_cm0, D_cmf;
long Setpointpos , Setpointpo , Setpointvel, dt, vel , errorD, u1, u2, utotal;
long t0 , tf ;
long i, n , grados;
//long k[] = { -3.5886,  -11.4550,   47.0209,   10.0045};
long k[] = { -7.0886,  -33.4550,   47.0209,   10.0045};
void setup()
{
  myservo.attach(7);
  Serial.begin(9600);
  Setpointpos = 20;
  dt = 1;
}

void loop()
{
  t0 = millis(); //tiempo antes de iniciar la lectura
  dt = (tf - t0);
  D_cm0 = distancia(100);
  vel = (D_cmf - D_cm0) / dt;
  Setpointpo = Setpointpos/4;
  errorD = D_cm0 - Setpointpo;
  Serial.println(float(utotal));
  /***** LEY DE CONTROL ************/
  u1 = -k[0] * errorD;
  u2 = -k[1] * vel;
  /********************************/
  utotal = u1 + u2;
  grados = map (utotal , -180 , 220 , 1600 , 1200 );
  if (grados<1600 and grados > 1200){
  myservo.writeMicroseconds(grados);
  Serial.println(utotal);
  D_cmf = distancia(100);
  tf = millis();}
}

float distancia(float n)
{
  long suma = 0;
  long lectura;
  long cm;
  for (int i = 0; i < n; i++)
  {
    lectura = analogRead(sensordistancia); // lectura del sensor 0
    suma = suma + lectura;
  }
  long adc = suma / n;
  cm = pow(3027.4 / adc, 1.2134); // conversión a centímetros
  return (cm);
}
