#include <Servo.h> 
Servo myservo;   
int pos = 0;  // posicion del servo
// PROGRAMA BUENO
//float kp=5.0;
//float ki=4.5;
//float kd=2.9;

//float kp=5.446;
//float ki=1.58;
//float kd=4.695;

float kp = 7.0;
float ki = 0.001;
float kd = 4.5;

float error_previo;
float integral=0;
int sp=15;///////////////distancia
float output=0;
int PV=0;
int error=0;
int sc;

void setup() 
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  myservo.attach(7);
}
void loop() 
{
  long tiempo=millis(); //tiempo antes de iniciar la lectura
  int D_cm=distancia(20); //lectura de distancia
  tiempo=millis()-tiempo; //milisegundos que duró la lectura
  Serial.print("  Distancia:  ");
  Serial.print(D_cm);
  Serial.print("  cm");
  error = sp - D_cm;
  Serial.print("  Error:  ");
  Serial.print(error);
  PV=D_cm;
  if(sp==0)
  {
    integral=0;
  }
  if(integral>200)
  {
    integral=200;
  }
  if(integral<0)
  {
    integral=abs(integral);
  }
  integral=integral+(error*0.25);
  float derivative=(error-error_previo)/0.25;
  output=kp*error+ki*integral+kd*derivative;
  error_previo=error;
  Serial.print("    ");
  Serial.print(output+1400+sp);
  Serial.println(" ");
  myservo.writeMicroseconds(output+1400+sp);
  delay(150);
}
float distancia(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A0);
  }  
  float adc=suma/n;
  float distancia_cm = 17569.7 * pow(adc, -1.2062);
  return(distancia_cm);
}
