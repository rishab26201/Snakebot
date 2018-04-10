
#include <Servo.h> 

// Define servo objects for the snake segments
Servo s1; 
Servo s2;
Servo s3;
Servo s4; 
Servo s5;
Servo s6;
Servo s7;
float Qp[8],di[5],set[5]; //////////
int n=8;  /////////
int i,j,pos;
Servo servo[8];
void asgn(int a,int b,int c,int d,int e)
{  
  set[0]=a; set[1]=b; set[2]=c; set[3]=d; set[4]=e;
  
  for(i=0;i<5;i++)  
    di[i]=(set[i]-Qp[pos+i])/10; 
    if(pos==0) 
    {
      for(i=0;i<=10;i++)
      {
        s7.write(Qp[0]+(di[0]*i));
        s6.write(Qp[1]+(di[1]*i));
        s5.write(Qp[2]+(di[2]*i));
        s4.write(Qp[3]+(di[3]*i));
        s3.write(Qp[4]+(di[4]*i));
        delay(80);
      }
    }
    else
    {
      for(i=0;i<=10;i++)
     {       
        s6.write(Qp[1]+(di[0]*i));
        s5.write(Qp[2]+(di[1]*i));
        s4.write(Qp[3]+(di[2]*i));
        s3.write(Qp[4]+(di[3]*i));
        s2.write(Qp[5]+(di[4]*i));
        delay(80);
      }
    }
  for(j=0;j<5;j++)
    Qp[pos+j]=set[j];  
       
}

char m='x';
  
// Define variables
int counter = 0; 
float lag = 1.15; 
int frequency = 4; 
int A = 60; // Horizontal amplitude 
int B = 50; // Vertical amplitude

void setup() 
{   
   s1.attach(2);
   s2.attach(9);
   s3.attach(10);
   s4.attach(5);
   s5.attach(7);
   s6.attach(11);
   s7.attach(8);
   
   s1.write(90);
   s2.write(90); 
   s3.write(90);
   s4.write(90);
   
   s5.write(90);
   s6.write(90);
   s7.write(90);
   Serial.begin(9600);
 
//starting position
   /*s1.write(90+A*cos(0*lag));
   s3.write(90+A*cos(1*lag)); 
   s5.write(90+A*cos(2*lag));
   s7.write(90+A*cos(3*lag));
 
   delay(3000);*/ 
} 

  
void loop() 
{
// Serpentine motion
  if (Serial.available())
 {m=Serial.read();
 Serial.println(m);
 while (m=='w'){
  forward(); 
  if(Serial.available())m=Serial.read();
  }
  while(m=='s'){
  backward();
  if(Serial.available())m=Serial.read();
  }
  while (m=='a'){
  turnl();
  if(Serial.available())m=Serial.read();
  }
  while(m=='q'){
  sidewind();
  if(Serial.available())m=Serial.read();
  }
  while(m=='h'){
  halt();
  if(Serial.available())m=Serial.read();
}
}
}

void forward(){
  for(counter = 0; counter < 360; counter += 1)  {
    delay(10);
    s1.write(90+A*cos(frequency*counter*3.14159/180-0*lag));
    s3.write(90+A*cos(frequency*counter*3.14159/180-1*lag));
    s5.write(90+A*cos(frequency*counter*3.14159/180-2*lag));
    s7.write(90+A*cos(frequency*counter*3.14159/180-3*lag));
  }
}
void backward(){
  for(counter = 0; counter < 360; counter += 1)  {
    delay(10);
    s7.write(90+A*cos(frequency*counter*3.14159/180-0*lag));
    s5.write(90+A*cos(frequency*counter*3.14159/180-1*lag));
    s3.write(90+A*cos(frequency*counter*3.14159/180-2*lag));
    s1.write(90+A*cos(frequency*counter*3.14159/180-3*lag));
  }
}
void turnl(){
    s3.write(120);
    delay(200);
    s2.write(120);
    delay(200);
    s5.write(60);
    delay(200);
    s4.write(50);
    delay(200);
    s2.write(90);
    delay(200);
    s3.write(90);
    delay(200);
    s7.write(170);
    delay(100);
    s3.write(60);
    delay(100);
    s4.write(90);
    delay(100);
    delay(200);
    s5.write(90);
    s7.write(90);
    delay(100);
    s3.write(90);
}
void sidewind()
{
  //////// head motion (initiation)  ////////////////
  pos=0;      /////
  asgn(90,90,90,90,90); 
  asgn(150,60,90,90,90);  
  asgn(90,30,90,90,90); //////// 
  asgn(0,90,120,60,90);  
  asgn(90,150,90,30,90);  
  //////////  pulse transfer  //////////
  pos=1;
  asgn(120,30,90,120,60);  
  asgn(90,90,150,90,40);   

  ///////// tail motion (pulse ending)  /////////
  pos=1; 
  asgn(150,90,10,120,60); //tail placing  
  asgn(150,120,10,50,30);    /// lifting and placing
  asgn(120,110,90,60,90);   ///moving (pushing body using tail)
  asgn(90,90,150,90,120); 
  
  asgn(90,90,120,150,110);  /// tail align
  asgn(90,90,90,90,90);
}
void halt(){
  s1.write(90);
   s3.write(90); 
   s5.write(90);
   s7.write(90);
   s2.write(90);
   s4.write(90);
   s6.write(100);
}
void turnr(){
  
}

