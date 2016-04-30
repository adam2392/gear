/*
@file gameShoeRun.ino
@brief Microcontroller firmware to run the flexiforce sensor system
@author Adam Li, George Levay
*/
#include <ControlComputer.h>
#include <Sensor_Comm.h>


//define 4 force sensor pin outs
//left shoe sensors
#define SENSORLEFT_1 0
#define SENSORLEFT_2 6
#define SENSORLEFT_3 7

//right shoe sensors
#define SENSORRIGHT_1 4 //rightfoot_left
#define SENSORRIGHT_2 5 //rightfoot_right
#define SENSORRIGHT_3 3 //rightfoot_heel

//other hardware parts
#define ledpin 11
#define PUSHPIN 9
#define POWERPIN 10

// command char array for customizing commands
enum { BUFFSZ = 100 };
char commands[BUFFSZ];

// DEFINE CLASSES
Sensor_Comm sensor_comm(SENSORLEFT_1, SENSORLEFT_2, SENSORLEFT_3, 
              SENSORRIGHT_1, SENSORRIGHT_2, SENSORRIGHT_3, PUSHPIN);
ControlComputer control_com;

/////////////////////Setting Player Thresholds//////////////////////////
int player = 1;

// Creating thresholds with high and low levels
// RIGHT foot
int threshForward_R_H, threshForward_R_L, threshRight_R_H, threshRight_R_L;
int threshLeft_R_H, threshLeft_R_L, threshHeel_R_H, threshHeel_R_L;

// LEFT foot
int threshForward_L_H, threshForward_L_L, threshRight_L_H, threshRight_L_L;
int threshLeft_L_H, threshLeft_L_L, threshHeel_L_H, threshHeel_L_L;
 
// Setting threshold levels for players
void player1() {
  // RIGHT FOOT
  threshForward_R_H = 800;
  threshForward_R_L = 200/3; // go forward w
  
  threshRight_R_H = 500;
  threshRight_R_L = 500/4; // go right d
  
  threshLeft_R_H = 500;
  threshLeft_R_L = 500/4; // go left a
  
  threshHeel_R_H = 500;
  threshHeel_R_L = 400/8; //go back s
  
  // LEFT foot
  threshForward_L_H = 500;
  threshForward_L_L = 130/2;
  
  threshRight_L_H = 500;
  threshRight_L_L = 220/2;
  
  threshLeft_L_H = 500;
  threshLeft_L_L = 200/2;
  
  threshHeel_L_H = 500;
  threshHeel_L_L = 100/2;
}
/////////////////////END OF Setting Player Thresholds//////////////////////////

void setup() {
  Serial.begin(9600);
 
  pinMode(SENSORRIGHT_1, INPUT);
  pinMode(SENSORRIGHT_2, INPUT);
  pinMode(SENSORRIGHT_3, INPUT);
  pinMode(SENSORLEFT_1, INPUT);
  pinMode(SENSORLEFT_2, INPUT);
  pinMode(SENSORLEFT_3, INPUT);
  pinMode(PUSHPIN, INPUT);
  pinMode(13, OUTPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(POWERPIN, OUTPUT);
  
  //calibrate sensors 
  sensor_comm.calibrateSensors();

  //**** NEED TO INCLUDE SOME INITIALIZATION OF SENSOR VALUES FOR GOING FORWARD/BACKWARDS
  //**** ALSO REPLACE ALL SIGNAL WITH controlCom

  
  //initialize threshold values
  if (player == 1){
    player1();
  }
  
  else if(player == 2){
//    player2();
  }
  
  //turn on LEDs to show that we are running
  digitalWrite(ledpin, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(POWERPIN, HIGH);
}

void loop() {

  delay(30);

  int test = sensor_comm.read_right1output();
  int test1 = sensor_comm.read_right2output();
  int test2 = sensor_comm.read_right3output();
  Serial.println(test);
  Serial.println(test1);
  Serial.println(test2);
////  test = sensor_comm.read_left1output();
////  test1 = sensor_comm.read_left2output();
////  test2 = sensor_comm.read_left3output();
////  Serial.println(test);
////  Serial.println(test1);
////  Serial.println(test2);
  delay(100);

 //read in sensors right away
  sensor_comm.readSensors();

  // EITHER RECALIBRATE OR SET COMMANDS
  if(sensor_comm.read_buttonPress()) {
//    control_com.pressCommand("w"); // test line (YOU CAN SEE IT PRESSING W WITH BUTTON :))
    sensor_comm.calibrateSensors();        //recalibrate
    
    //flash led to show we recalibrated
    delay(10);
    for(int i=1; i<10; i++) {
      digitalWrite(ledpin, LOW);
      delay(100);
      digitalWrite(ledpin, HIGH);
      delay(100);
    }

    int begtime = millis();
    int endtime = millis();
    bool customize_sensor_state = false;
    sensor_comm.readSensors();
    while(sensor_comm.read_buttonPress()) {
      sensor_comm.readSensors();
      
      endtime = millis();
      if(abs(endtime-begtime)/1000.0 > 3.0) {
        Serial.println("customizing sensors 01");
        customize_sensor_state = true;
        break;
      }
    }

    if(customize_sensor_state) {
      Serial.println("customizing sensors 02");    
      boolean startPressing = false;
      while(1) {   // infinite loop until we are done customizing the command
        delay(10);
  //      Serial.print("IN INFINITE LOOP");
        if(!startPressing) {
          for(int i=0; i<8; i++) {
            if(Serial.available()) {
              memset(commands,'\0', BUFFSZ);
              control_com.readSerial(commands);
              
              Serial.println("this is a command:");
              Serial.println(commands);
              control_com.setCommands(i, commands); 
              startPressing = true;
            }
          }            
        } else { // finished setting commands
          Serial.println("break");
          Serial.println("These are your new commands");
          control_com.printFront();
          control_com.printRight();
          control_com.printLeft();
          control_com.printBack();
          break;
        }
      }
    }
  }
  
  /////////////////Conditional LOGIC////////////////////////
  //moving
  //forward move; both RF front sensors pressed
  if(sensor_comm.read_right1output() > threshForward_R_L &&
       sensor_comm.read_right2output() > threshForward_R_L) {
//    while(sensor_comm.read_right1output() > threshForward_R_L &&
//         sensor_comm.read_right2output() > threshForward_R_L) {
//      control_com.signalFront();
////      Serial.println("Pressing front");
////      control_com.printFront();
//      sensor_comm.readSensors();
//    }
  }
  //move right; RF right sensor pressed
//  else if (sensor_comm.read_right2output() > threshRight_R_L) {
//    control_com.signalRight();
//    while(sensor_comm.read_right2output() > threshRight_R_L) {
//      sensor_comm.readSensors();
//      control_com.signalRight();
//    }
//  }
//  //move left; RF left sensors pressed 
//  else if (sensor_comm.read_right1output() > threshLeft_R_L) {
//    control_com.signalLeft();
//    while(sensor_comm.read_right1output() > threshLeft_R_L) {     
//      sensor_comm.readSensors();
//      control_com.signalLeft();
//    }
//  }
  //move back
  else if(sensor_comm.read_right3output() > threshHeel_R_L) {
    control_com.signalBack();   
    while(sensor_comm.read_right3output() > threshHeel_R_L) { 
      sensor_comm.readSensors();
    } 
  }
  
  //Jump and move combos
  if(sensor_comm.read_left1output() > threshLeft_L_L) {
    control_com.signalJump();  
  }
  
  //jump and fwd 
  else if(sensor_comm.read_right1output() > threshForward_R_L &&
     sensor_comm.read_right2output() > threshForward_R_L &&
     sensor_comm.read_left1output() > threshLeft_L_L) {
    control_com.signalFront();
    control_com.signalJump(); 
    while(sensor_comm.read_right1output() > threshForward_R_L &&
         sensor_comm.read_right2output() > threshForward_R_L &&
         sensor_comm.read_left1output() > threshLeft_L_L) {
           
      sensor_comm.readSensors();
    }
  }
  
  //jump and right
  else if(sensor_comm.read_right2output() > threshRight_R_L &&
     sensor_comm.read_left1output() > threshLeft_L_L) {
    control_com.signalRight();
    control_com.signalJump(); 
    while(sensor_comm.read_right2output() > threshRight_R_L &&
    sensor_comm.read_left1output() > threshLeft_L_L) {
           
      sensor_comm.readSensors();
    } 
  }
  
  //jump and left
  else if(sensor_comm.read_right1output() > threshLeft_R_L &&
          sensor_comm.read_left1output() > threshLeft_L_L) {
    control_com.signalLeft();
    control_com.signalJump(); 
    while(sensor_comm.read_right1output() > threshLeft_R_L &&
    sensor_comm.read_left1output() > threshLeft_L_L) {
           
      sensor_comm.readSensors();
    } 
  }
  
  //jump and back
  else if(sensor_comm.read_right3output() > threshHeel_R_L &&
     sensor_comm.read_left1output() > threshLeft_L_L) {
    control_com.signalBack();
    control_com.signalJump(); 
    while(sensor_comm.read_right3output() > threshHeel_R_L &&
         sensor_comm.read_left1output() > threshLeft_L_L) {
           
      sensor_comm.readSensors();
    } 
  }

  // crouching
  if(sensor_comm.read_left3output() > threshHeel_L_L) {
    control_com.signalCrouch();
  }
  
  //crouch and fwd
  else if(sensor_comm.read_right1output() > threshForward_R_L && 
          sensor_comm.read_right2output() > threshForward_R_L &&
          sensor_comm.read_left3output() > threshHeel_L_L) {
    control_com.signalCrouch();
    control_com.signalFront(); 
    while(sensor_comm.read_right1output() > threshForward_R_L && 
         sensor_comm.read_right2output() > threshForward_R_L &&
         sensor_comm.read_left3output() > threshHeel_L_L) {
           
      sensor_comm.readSensors();
    } 
  }
  
  //crouch and right
  else if(sensor_comm.read_right2output() > threshRight_R_L &&
          sensor_comm.read_left3output() > threshHeel_L_L) {
    control_com.signalRight();
    control_com.signalCrouch(); 
    while(sensor_comm.read_right2output() > threshRight_R_L &&
         sensor_comm.read_left3output() > threshHeel_L_L) {
           
      sensor_comm.readSensors();
    } 
  }
  
  //crouch and left
  else if(sensor_comm.read_right1output() > threshLeft_R_L &&
          sensor_comm.read_left3output() > threshHeel_L_L) {
    control_com.signalLeft();
    control_com.signalCrouch(); 
    while(sensor_comm.read_right1output() > threshLeft_R_L &&
         sensor_comm.read_left3output() > threshHeel_L_L) {   
      sensor_comm.readSensors();
    } 
  }
  
  //crouch and back
  else if(sensor_comm.read_right3output() > threshHeel_R_L &&
          sensor_comm.read_left3output() > threshHeel_L_L) {
    control_com.signalBack();
    control_com.signalCrouch(); 
    while(sensor_comm.read_right3output() > threshHeel_R_L &&
         sensor_comm.read_left3output() > threshHeel_L_L) {  
            sensor_comm.readSensors();
    }
  }
  
  //reload
  else if(sensor_comm.read_left2output() > threshRight_L_L) {
    control_com.signalReload();  
    delay(100);
  }

  else if(isForward()) {
    control_com.signalFront();
    delay(10);   
  }
    //move right; RF right sensor pressed
  else if (isRight()) {
    control_com.signalRight();
    delay(10);
  }
  //move left; RF left sensors pressed 
  else if (sensor_comm.read_right1output() > threshLeft_R_L) {
    control_com.signalLeft();
    delay(10);
  }

  
  ///////Mouse buttons
//  else if(sensor_comm.read_left1output() > threshForward_L_L && sensor_comm.read_left2output() > threshForward_L_L) {
//    Mouse.release(MOUSE_RIGHT);
//
//    while(sensor_comm.read_left1output() > threshForward_L_L && sensor_comm.read_left2output() > threshForward_L_L) {
//      sensor_comm.readSensors();
//      control_com.signalAim(); 
//      delay(100); 
//      if (sensor_comm.read_left1output() < threshForward_L_L || sensor_comm.read_left2output() < threshForward_L_L 
//     //|| 
//       //   sensor_comm.read_left1output() < threshForward_L_L && sensor_comm.read_left2output() < threshForward_L_L
//       ) {
//        Mouse.release(MOUSE_RIGHT);
//      }
//    }
//    delay(100);
//  }
}

bool isForward() {
  if (sensor_comm.read_right1output() > threshForward_R_L && 
       sensor_comm.read_right2output() > threshForward_R_L) {
       return true;
   }
   else {
    return false;
   }
}

bool isRight() {
  if (sensor_comm.read_right2output() > threshRight_R_L) {
    return true;
  }
   else {
    return false;
   }
}

