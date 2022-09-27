#include <SoftwareSerial.h>
#include <Servo.h>

//Bluetooth 

SoftwareSerial BT(10, 11);
int greenLedBluetooth = 12;
int redLedBluetooth = 13;

//CAR LOCK

int redLedCarLock = 9;
int greenLedCarLock = 8;
Servo leftServo;
Servo rightServo;

//**************************************

//INDICATOR LEDs

int indicatorsLeds = 3;

//**************************************

char a; 

//TOKENS

int btConnectionToken = 0;
int carLockToken = 0;

//**************************************

void setup()
{

  leftServo.attach(5);
  rightServo.attach(6);
  
  pinMode(greenLedBluetooth,OUTPUT);
  pinMode(redLedBluetooth, OUTPUT);
  pinMode(indicatorsLeds,OUTPUT);
  pinMode(redLedCarLock,OUTPUT);
  pinMode(greenLedCarLock,OUTPUT);
  
  BT.begin(9600);

}

void loop()
{
  
  carStartStatus();

  if (BT.available())

  {
    a=(BT.read());
    
    if (a=='a')
    {
      
      bluetoothConnected();
      BT.print("1");
      welcomeIndicatorLEDsEffect();
      
    } else if(a=='o'){
      
      carLockToken = 1;
      openCar();
      BT.print("2");
          
    } else if(a=='c'){

      carLockToken = 0;
      closeCar();
      BT.print("3");
          
    }
    
   }
}

void bluetoothNotConnected(){

digitalWrite(greenLedBluetooth,LOW);
digitalWrite(redLedBluetooth,HIGH);
delay(500);
digitalWrite(redLedBluetooth,LOW);
delay(500);

}

void bluetoothConnected(){

btConnectionToken = 1;
digitalWrite(redLedBluetooth,LOW);
digitalWrite(greenLedBluetooth, HIGH);

}

void carStartStatus() {

  if (btConnectionToken == 0)
  {
    
    bluetoothNotConnected();
  
  }

  if (carLockToken == 0) {

    closeCar();

  } 
  
}

void welcomeIndicatorLEDsEffect() {

digitalWrite(indicatorsLeds,HIGH);
delay(600);
digitalWrite(indicatorsLeds,LOW);

}

void openCar(){

digitalWrite(redLedCarLock,LOW);
digitalWrite(greenLedCarLock,HIGH);
leftServo.write(0);
rightServo.write(0);
  
}

void closeCar(){
  
digitalWrite(redLedCarLock,HIGH);
digitalWrite(greenLedCarLock,LOW);
leftServo.write(180);
rightServo.write(180);
    
}
