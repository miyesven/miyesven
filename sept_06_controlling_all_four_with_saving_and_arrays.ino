//two pot controlling two servos--> EDITED TO FOUR POTS CONTROLLING FOUR SERVOS (9 SEPT 1:46AM LOL)
//works perfectly
#include <Servo.h>
#define TIMEDIFF 1000

Servo servoZero;
Servo servoOne;
Servo servoTwo;
Servo servoThree;

int num0,num1,num2,num3;
int arrayNum0, arrayNum1,arrayNum2,arrayNum3; //after saving the number in the array

int servo0=12; //digital
int servo1=11;
int servo2=10;
int servo3=9;

int pot0=2; //analog
int pot1=3;
int pot2=4;
int pot3=5;

int pos0, pos1, pos2, pos3; //position written from pot to servo

int array0[4]={0}; //to store pot numbers
int array1[4]={0};
int array2[4]={0};
int array3[4]={0};

int record=0; //boolean to record (when==1) and play (when==2)for each pot and servo couple

int i=0; //to keep track of array number in first couple;
int j=0;
int k=0;
int m=0; 
int increm00, increm01, increm02, increm03; //keep track of increments from one position to the other on each servo
int increm10,increm11, increm12, increm13;
int increm20,increm21, increm22, increm23;
int increm30, increm31, increm32, increm33;
int a0,a1,a2,a3;//get values in arrays
int b0,b1,b2,b3;
int c0,c1,c2,c3;
int d0,d1,d2,d3;

int button = 13; //if button on, then the led on the arduino lights up
int foo; //keep track if the switch is open or not
int count=0; //keep track of the recording the first and second position of the servos
int moving=0; //keep track of movement of the servos moving from neutral to the first then second positions
int tick=0; //keep track of how many increments moved the servos during moving (record=2)
int timeDelay[4]={30,30,10,15}; //delay between origin and each position
unsigned long time1=0, time2=0; //checking time between two button presses 
int reset=0;//checking for two button presses in record==2
int timediff; //time diff between two button presses


void setup() {
  servoZero.attach(servo0);
  servoOne.attach(servo1);
  servoTwo.attach(servo2);
  servoThree.attach(servo3);

  servoZero.writeMicroseconds(700);
  servoOne.writeMicroseconds(700);
  servoTwo.writeMicroseconds(700);
  servoThree.writeMicroseconds(700);

  Serial.begin(9600);

  pinMode(button, INPUT);
}

void loop(){
  
//moving the potentiometers to their places
 if(record==0){
  /***moving in real time for two servo and potentiometer couple****/
  num0=analogRead(pot0);
  pos0= convertToPot(num0);
  servoZero.writeMicroseconds(pos0); //writing to servos in real time

  num1=analogRead(pot1);
  pos1= convertToPot(num1);
  servoOne.writeMicroseconds(pos1); //writing to servos in real time

  
  num2=analogRead(pot2);
  pos2= convertToPot(num2);
  servoTwo.writeMicroseconds(pos2); //writing to servos in real time

  
  num3=analogRead(pot3);
  pos3= convertToPot(num3);
  servoThree.writeMicroseconds(pos3); //writing to servos in real time

  if (foo==1){  //if button pressed once, enter record mode, foo detection is below
    record=1;
  }
}

 /*****record mode activated*********/
 if(record==1){ 
    if (count==0 && foo==1){   //**first record of the positions of servos
      array0[0]=pos0;
      array1[0]=pos1;
      array2[0]=pos2;
      array3[0]=pos3;
      
      count=1;
    } 
    if (count==1 && foo==0){ //switching off the button and preparing for the second position of the servos  
        count=2;
        record=0; //go back to moving the servos by moving the potentiometers
    } 
    
    if (count==2 && foo==1){   //**second record of positions of servos
        array0[1]=pos0;
        array1[1]=pos1;
        array2[1]=pos2;
        array3[1]=pos3;
        count=3;
    } 
    
    if(count==3 && foo==0){
        record=0; 
        count=4;
     }

    if (count==4 && foo==1){
        array0[2]=pos0;     //**third record of positions of servos
        array1[2]=pos1;
        array2[2]=pos2;
        array3[2]=pos3;
        count=5;
    }
    
    if (count==5 && foo==0){
       record=0;
       count=6;
    }

    if (count==6 && foo==1){
        array0[3]=pos0;     //**fourth record of positions of servos
        array1[3]=pos1;
        array2[3]=pos2;
        array3[3]=pos3;
        count=7;
    }

    if (count==7 && foo==0){
        record=2; 
    }
 } /*end of record=1*/


  /*****play mode activated***********/
  if (record==2){
    if(moving==0){ 
      pos0=700;
      pos1=700;
      pos2=700;
      pos3=700;
      
      servoZero.writeMicroseconds(pos0);
      servoOne.writeMicroseconds(pos1);
      servoTwo.writeMicroseconds(pos2);
      servoThree.writeMicroseconds(pos3);
      
      increm00=findingIncrements (700, array0[0]);
      increm01=findingIncrements ( array0[0], array0[1]);
      increm02=findingIncrements (array0[1], array0[2]);
      increm03=findingIncrements ( array0[2], array0[3]);
      
      increm10=findingIncrements (700, array1[0]);
      increm11=findingIncrements ( array1[0], array1[1]);
      increm12=findingIncrements ( array1[1], array1[2]);
      increm13=findingIncrements ( array1[2], array1[3]);
      
      increm20=findingIncrements (700, array2[0]);
      increm21=findingIncrements ( array2[0], array2[1]);
      increm22=findingIncrements ( array2[1], array2[2]);
      increm23=findingIncrements ( array2[2], array2[3]);

    
      increm30= findingIncrements (700, array3[0]);
      increm31=findingIncrements ( array3[0], array3[1]);
      increm32=findingIncrements ( array3[1], array3[2]);
      increm33=findingIncrements ( array3[2], array3[3]);

      a0=array0[0]; a1=array0[1];a2=array0[2];a3=array0[3];
      b0=array1[0]; b1=array1[1];b2=array1[2];b3=array1[3];
      c0=array2[0]; c1=array2[1];c2=array2[2];c3=array2[3];
      d0=array3[0]; d1=array3[1];d2=array3[2];d3=array3[3];

      moving=1;
    } 
    
    if (moving==1){
      if (tick<20){
        pos0+= increm00;
        pos1+= increm10;
        pos2+= increm20;
        pos3+= increm30;
        servoZero.writeMicroseconds(pos0);
        servoOne.writeMicroseconds(pos1);
        servoTwo.writeMicroseconds(pos2);
        servoThree.writeMicroseconds(pos3);
        tick++;
        //delay(timeDelay[0]);
      }
      if (tick==20){
        moving=2;
        tick=0;
      }
    } 
    
    if (moving==2){
      if(tick<20){
        pos0+= increm01;
        pos1+= increm11;
        pos2+= increm21;
        pos3+= increm31;

        servoZero.writeMicroseconds(pos0);
        servoOne.writeMicroseconds(pos1);
        servoTwo.writeMicroseconds(pos2);
        servoThree.writeMicroseconds(pos3);
        tick++;
        delay(timeDelay[1]);
      } 
      if (tick==20){
        moving=3;
        tick=0;
      }
    }

    if (moving==3){
      if(tick<20){
        pos0+= increm02;
        pos1+= increm12;
        pos2+= increm22;
        pos3+= increm32;

        servoZero.writeMicroseconds(pos0);
        servoOne.writeMicroseconds(pos1);
        servoTwo.writeMicroseconds(pos2);
        servoThree.writeMicroseconds(pos3);
        tick++;
        delay(timeDelay[2]);
      } 
      if (tick==20){
        moving=4;
        tick=0;
      }
    }

   if (moving==4){
    if(tick<20){
      pos0+= increm03;
      pos1+= increm13;
      pos2+= increm23;
      pos3+= increm33;

      servoZero.writeMicroseconds(pos0);
      servoOne.writeMicroseconds(pos1);
      servoTwo.writeMicroseconds(pos2);
      servoThree.writeMicroseconds(pos3);
      tick++;
      delay(timeDelay[3]);
    } 
    if (tick==20){
      moving=5;
      tick=0;
      }
    }

   if (moving==5){
     moving=0; //go back to original position, then loop back
   }

   //check if reset mode is activated by user
   if (reset==0 && foo==1){ 
    reset=1;
    time1=millis();
   }
   if (reset==1 && foo==1){
    reset=2;
    time2=millis();
    timediff=time2-time1;
   }

   /********** RESET MODE ACTIVATED (OR NOT)******************/
   if (reset==2 && timediff<=TIMEDIFF) {   
    record=0;  //go back to before record mode
    count=0;
    moving=0; 
    time1=0;
    time2=0;
    reset=0;
    tick=0;
   }else {
    reset=0;
   }
} /*end of record=2*/

/******DETECTION OF BUTTON**********/
  foo=digitalRead(button);


//to keep track of everything- this thing is the bomb
Serial.print("record=");
Serial.print(record);
Serial.println();
Serial.print("count=");
Serial.print(count);
Serial.println();
Serial.print("foo=");
Serial.print(foo);
Serial.println();
Serial.print("moving=");
Serial.print(moving);
Serial.println();
Serial.print("tick=");
Serial.print(tick);
Serial.println();
Serial.print("reset=");
Serial.print(reset);
Serial.println();

} /*end of loop*/

int convertToPot (int x){
  int y= (x*1.66)+ 700;
  return y;
}

int findingIncrements (int previousNum, int num){
  int diff;
  diff=num-previousNum;
  diff=diff/20;
  return diff;
}

