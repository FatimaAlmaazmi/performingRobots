/*
  Moving Robot Platform 
  By: Omar ElGamal and Fatima Almaazmi 
*/

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2,OUTPUT); 
  pinMode(3,OUTPUT); 
  pinMode(6,OUTPUT); 
  pinMode(7,OUTPUT); 
  Serial.print("i worked");
}

int number = 0; 

int leftMotor= 0;   //(2 and three)

int rightMotor= 0; //(6 and seven)

unsigned long previousMillis=0; 

//intervals for the panic attacks

// int stopInterval= 400;

//Jittering
const long jittering= 250; 
int jitterCount=16; 
int jitterCounter=0;
bool stopJitter=false; 

//Spinning 
const long Spin= 800; 
int spinCount=4; 
int spinCounter=0; 
bool stopSpin=false; 

//Resolved
const long resolved= 1600; 
int resolvedCounter=0; 
bool resetAll=false; 


void loop() {
  unsigned long currentMillis = millis();
  //Jittering  
  if(jitterCounter<=jitterCount&& currentMillis - previousMillis >= jittering &&stopJitter==false){
    previousMillis = currentMillis;
    Serial.print("hiii");
    
    if(leftMotor==0 && rightMotor==0){ 
      leftMotor= 200;
      rightMotor= 200;
    }
    else{ 
      leftMotor= 0;
      rightMotor= 0;
    }

    analogWrite(3,leftMotor); 
    analogWrite(6,rightMotor); 

    jitterCounter=jitterCounter+1;

}
  if (jitterCounter==jitterCount){ 
    stopJitter=true; 
    Serial.print("im here");
  }  

  // Spinning 
  if(currentMillis-previousMillis>=Spin && spinCounter<=spinCount && stopSpin==false &&stopSpin==false) {
      previousMillis = currentMillis;
      if(leftMotor==0 && rightMotor==0){ 
        leftMotor= 0;
        rightMotor= 230;
        }
      else{ 
        leftMotor= 0;
        rightMotor= 230;        
      }
       
      analogWrite(3,leftMotor); 
      analogWrite(6,rightMotor);  
        
      spinCounter=spinCounter+1;
  } 
  if (spinCount==spinCounter){ 
    stopSpin=true; 
  }

  //Resolved 
  if (stopSpin==true && stopJitter==true &&  resolvedCounter<=3 && currentMillis-previousMillis>=resolved ){ 
      previousMillis = currentMillis;
    if(leftMotor==0 && rightMotor==0){ 
        leftMotor= 200;
        rightMotor= 200;
        }
      else{ 
        leftMotor=0; 
        rightMotor=0;
      }
      analogWrite(3,leftMotor); 
      analogWrite(6,rightMotor);  
      resolvedCounter= resolvedCounter+1; 
       

  }
  
  //resetting the booleans and variables to start the seqeunce again 
  if (resolvedCounter==3){ 
    jitterCounter=0; 
    spinCounter=0; 
    stopJitter=false; 
    stopSpin=false;
    resolvedCounter=0;

  }



} 
