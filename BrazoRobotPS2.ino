
/*
EBLUDT 02/02/2015
Brazo robot controlado por 3 servos y un mando ps2 para arduino.
https://www.youtube.com/watch?v=WSRLUlyWnJA

Es necesario descargar la libreria ps2x de bill porter
http://www.billporter.info/2010/06/05/playstation-2-controller-arduino-library-v1-0/

Mas projectos arduino en http://montarelpollo.blogspot.com.es/

Esquema pines para mi mando

1   DATA      VERDE
2   NARANJA   COMMAND
3   AZUL      VIBRATION (7VOLTS)
4   NEGRO     TIERRA
5   AMARILLO  3,3 V
6   ROJO      ATTENTION
7   LILA      CLOCK
8   BLANCO    CONO


*/
#include <PS2X_lib.h>  //for v1.6
#include <Servo.h> 

PS2X ps2x; // create PS2 Controller Class

// declaramos objetos

Servo servoh;  // Crea un Objeto servo  horizontal
Servo servov; //servo vertical
Servo servom; //servo micro

//declaramos constantes
int pinServoh=10;
int pinServov=11;
int pinServom=9;

//declaramos variables
int posicionh;    // Variable de la posicion del servo  
int posicionv; //variable de la posicion vertical
int posicionm;
int cont;
int error = 0; 
int difh=0;
int difv=0;
int difm=0;
int estadom=0;

void setup(){
    Serial.begin(57600);
    error=ps2x.config_gamepad(3,5,6,4,true,true);   //setup pins and settings:  GamePad(clock(lila), command(naranja), attention(rojo), data (verde), Pressures?, Rumble?) check for error
    servoh.attach(pinServoh);  // Selecionamos el pin 2 como el pin de control para els ervo  
    servov.attach(pinServov);
    servom.attach(pinServom);
    posicionh= 90;//posicion inicial servo
    posicionv=90; // 
    posicionm=90;
    servoh.write(posicionh);
    servov.write(posicionv);
    servom.write(posicionm); 
  
}

void loop(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */
   
   
    //////////////////////////////////////////////aumento servo vertical
    ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed
    
    difv=ps2x.Analog(PSS_LY),DEC;
    difv=difv-128;
    difv=difv;  
    difv= map(difv, 127, -128, -2, 3);
       if ((posicionv>=0) || (posicionv<=180)){ //comprobamos que la posicion del servo no sea mayor que 180 o menos que 0
      posicionv=posicionv-difv;
    }
    
    if (posicionv>120) {
      posicionv=120;
    }
    else if (posicionv<0){
      posicionv=0;
    }
    servov.write(posicionv); 
    
    
    /////horizontal
    ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed
    
    difh=ps2x.Analog(PSS_LX),DEC;
    difh=difh-128;
    difh=difh;  
    difh= map(difh, -128, 127, -4, 5);
       if ((posicionh>=0) || (posicionh<=180)){ //comprobamos que la posicion del servo no sea mayor que 180 o menos que 0
      posicionh=posicionh-difh;
    }
    
    if (posicionh>180) {
      posicionh=180;
    }
    else if (posicionh<0){
      posicionh=0;
    }
    servoh.write(posicionh);
    
      
    ////////////////////////////////////////////////aumento micro
    ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed
    
    difm=ps2x.Analog(PSS_RY),DEC;
    difm=difm-128;
     
    difm= map(difm, -128, 127, -4, 5);
       if ((posicionm>=0) || (posicionm<=180)){ //comprobamos que la posicion del servo no sea mayor que 180 o menos que 0
           posicionm=posicionm-difm;
   
    }
    
    if (posicionm>180) {
      posicionm=180;
    }
    else if (posicionm<0){
      posicionm=0;
    }
    
    
      servom.write(posicionm);
    
    
    
    /////////////////////////////servo hoprizontal
    
    
    
    
    
     if(ps2x.Button(PSB_CROSS)){
       posicionh= 90;//posicion inicial servo
       posicionv=90; // 
       posicionm=90;
       servoh.write(posicionh);
       servov.write(posicionv);
       servom.write(posicionm);
     }
       
    
    
    
    
    
  
    
    delay(10);// antes 10 para qeu vaya todo mas lento
     
}
