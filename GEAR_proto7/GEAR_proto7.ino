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
#define SENSORRIGHT_1 5 //rightfoot_left
#define SENSORRIGHT_2 4 //rightfoot_right
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
  threshForward_R_L = 200/1; // go forward w
  
  threshRight_R_H = 500;
  threshRight_R_L = 500/4.5; // go right d
  
  threshLeft_R_H = 500;
  threshLeft_R_L = 600.0/4.5; // go left a
  
  threshHeel_R_H = 500;
  threshHeel_R_L = 400/4; //go back s
  
  // LEFT foot
  threshForward_L_H = 500;
  threshForward_L_L = 130/2;
  
  threshRight_L_H = 500;
  threshRight_L_L = 220/2;
  
  threshLeft_L_H = 500;
  threshLeft_L_L = 200/2;
  
  threshHeel_L_H = 500;
  threshHeel_L_L = 100/1.3;
}
/////////////////////END OF Setting Player Thresholds//////////////////////////

int sleeptime = 1.0;

void waitForDualCommandRelease(bool (*f)(), bool (*g)()){
    while(f() && g()) {
      sensor_comm.readSensors();
      delay(50);
    }
    delay(10);
}

void waitForCommandRelease( bool (*f)() ){
    Serial.println("single");
    while(f()) {
      sensor_comm.readSensors();
      delay(50);
    }
    Serial.println("z");
    delay(10);
}

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

//  int test = sensor_comm.read_right1output();
//  int test1 = sensor_comm.read_right2output();
//  int test2 = sensor_comm.read_right3output();
//  Serial.println(test);
//  Serial.println(test1);
//  Serial.println(test2);
//  int test = sensor_comm.read_left1output();
//  int test1 = sensor_comm.read_left2output();
//  int test2 = sensor_comm.read_left3output();
//  Serial.println(test);
//  Serial.println(test1);
//  Serial.println(test2);
//  delay(100);

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
  
//////// NEW LOGIC ////
  //forward
  if(isForward()) {
    control_com.signalFront(); 
    
    while(isForward()) {
      sensor_comm.readSensors();
      delay(50);
    }
    Serial.println("z");
//    Serial.flush();
    delay(10);
  }
  //right
  else if(isRight() && !isLeft()) {
    control_com.signalRight(); 
    while(isRight() && !isLeft()) {
      sensor_comm.readSensors();
      delay(50);
    }
    Serial.println("z");
//    Serial.flush();
    delay(10);
  }
  //left
  else if(isLeft() && !isRight()) {
    control_com.signalLeft(); 
    while(isLeft() && !isRight()) {
      sensor_comm.readSensors();
      delay(50); 
    }
    Serial.println("z");
//    Serial.flush();
    delay(10);
  }
  else if(isBack()) {
    control_com.signalBack(); 
    while(isBack()) {
      sensor_comm.readSensors();
      delay(50);
    }
    Serial.println("z");
//    Serial.flush();
    delay(10);
  }
  
  else if(isReload()) {
    control_com.signalReload(); 
    while(isReload()) {
      sensor_comm.readSensors();
      delay(10);
    }
    Serial.println("z");
//    Serial.flush();
    sleep();
    delay(10);
  }
  
  if (isCrouch()) {
    control_com.signalCrouch(); // send command for crouch

    while(isCrouch()) {
      sensor_comm.readSensors();
      if(isForward()) {
        Serial.println("x");
        delay(50);
        control_com.signalFront();
        waitForDualCommandRelease(isCrouch, isForward);
      }
      else if(isRight()) {
        Serial.println("x");
        delay(50);
        control_com.signalRight();
        waitForDualCommandRelease(isCrouch, isRight);
      }
      else if(isLeft()) {
        Serial.println("x");
        delay(50);
        control_com.signalLeft();
        waitForDualCommandRelease(isCrouch, isLeft);
      }
      else if(isBack()) {
        Serial.println("x");
        delay(50);
        control_com.signalBack();
        waitForDualCommandRelease(isCrouch, isBack);
      }
      delay(50);
    }
    Serial.println("z");
    delay(10);
  }
  
  
  if(isJump()) {
    control_com.signalJump(); 
    while(isJump()) {
      sensor_comm.readSensors();
      
      if(isForward()) {
        Serial.println("x");
        delay(50);
        control_com.signalFront();
        waitForDualCommandRelease(isJump, isForward);
      }
      else if(isRight()) {
        Serial.println("x");
        delay(50);
        control_com.signalRight();
        waitForDualCommandRelease(isJump, isRight);
      }
      else if(isLeft()) {
        Serial.println("x");
        delay(50);
        control_com.signalLeft();
        waitForDualCommandRelease(isJump, isLeft);
      }
      else if(isBack()) {
        Serial.println("x");
        delay(50);
        control_com.signalBack();
        waitForDualCommandRelease(isJump, isBack);
      }
      delay(50);
    }
    Serial.println("z");
    delay(10);
  }
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

bool isLeft() {
  if (sensor_comm.read_right1output() > threshLeft_R_L) {
    return true;
  }
  else {
    return false;
  }
}

bool isBack() {
  if (sensor_comm.read_right3output() > threshHeel_R_L) {
    return true;
  }
  else {
    return false;
  }
}

bool isReload() {
  if (sensor_comm.read_left2output() > threshRight_L_L) {
    return true;
  }
  else {
    return false;
  }
}

bool isCrouch() {
  if (sensor_comm.read_left3output() > threshHeel_L_L) {
    return true;
  }
  else {
    return false;
  }
}
bool isJump() {
  if (sensor_comm.read_left1output() > threshLeft_L_L) {
    return true;
  } 
  else {
    return false;
  }
}

