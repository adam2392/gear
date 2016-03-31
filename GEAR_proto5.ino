/*
@file gameShoeRun.ino
 @brief Microcontroller firmware to run the flexiforce sensor system
 @author Adam Li, George Levay
 */
//#include <Keyboard.h>
//#include "Mouse.h"
//define 4 force sensor pin outs

//left shoe sensors
#define SENSORLEFT_1 1
#define SENSORLEFT_2 0
#define SENSORLEFT_3 2

//right shoe sensors
#define SENSORRIGHT_1 3
#define SENSORRIGHT_2 4
#define SENSORRIGHT_3 5

//other hardware parts
#define ledpin 6
#define PUSHPIN 7

//*********************** Set Variables for GUI Customization *****************
enum { 
  BUFFSZ = 100 };
const char UP_ARROW[] = "up_arrow";
const char DOWN_ARROW[] = "down_arrow";
const char RIGHT_ARROW[] = "right_arrow";
const char LEFT_ARROW[] = "left_arrow";
const char SPACE[] = "space";
const char SHIFT[] = "shift";
const char RIGHT_MOUSE[] = "right_mouse";

char commands[BUFFSZ];
char *front_command, *right_command, *left_command, *back_command;
char *jump_command, *aim_command, *reload_command, *crouch_command;

/* Function: setCommands
 Input: index - the index of which command to set
 comm - the char pointer to 
 */
void setCommands(int index, char* comm) {  
  //  Serial.println("setting commands!");
  if(index==0) {
    set_front(comm);
  }
  else if(index==1) {
    set_right(comm);
  }
  else if(index==2) {
    set_left(comm);
  }
  else if(index==3) {
    set_back(comm);
  }
  else if(index==4) {
    set_jump(comm);
  }
  else if(index==5) {
    set_aim(comm);
  }
  else if(index==6) {
    set_reload(comm);
  }
  else if(index==7) {
    set_crouch(comm);
  }
  else {
    Serial.println("Error in setCommands() due to index!");
  }
}

/* Functions for setting global variables for each gaming command */
void set_front(char* comm) {
  front_command = comm;
}
void set_left(char* comm) {
  left_command = comm;
  //  pressCommand(left_command);
}
void set_right(char* comm) {
  right_command = comm;
}
void set_back(char* comm) {
  back_command = comm;
}
void set_jump(char* comm) {
  jump_command = comm;
}
void set_aim(char* comm) {
  aim_command = comm;
}
void set_reload(char* comm) {
  reload_command = comm;
}
void set_crouch(char* comm) {
  crouch_command = comm;
}

/* Function to read in serial input */
void readSerial(char* outStr) {
  boolean stringComplete = false; //whether string is complete or not
  char incomingByte;              //buffer to store incoming characters in serial
  int index = 0;                  //to index through char array

  //loop to read in serial data
  while(Serial.available()) {
    incomingByte = Serial.read();     // read in byte by byte

    if(incomingByte == '\n') {        // when newline, terminate
      stringComplete = true;
      break;
    }
    outStr[index] = incomingByte; //store the character read
    index++;                           //increment index
  }
}
//******************************end of gui*************************************


/* Function to initiate pressing of commands */
void pressCommand(char *comm) {
  char *buffComm = comm;
  Serial.println(buffComm);
  
  if( buffComm == UP_ARROW ) {

  }
  else if( buffComm == RIGHT_ARROW) {

  }
  else if( buffComm == LEFT_ARROW) {  
  }
  else if(strcmp(buffComm, DOWN_ARROW)) {
//    Serial.println("Down arrow set");
  }
  else if( buffComm == RIGHT_MOUSE) {
    Keyboard.press(MOUSE_RIGHT);
  }
  else if( buffComm == SPACE) {
    Keyboard.press(' ');
  }
  else if( buffComm == SHIFT) {
    Keyboard.press(KEY_RIGHT_SHIFT);
  }
  else if( buffComm == "q") {
    Keyboard.press('q');
  }
  else if( buffComm == "w") {
    Keyboard.press('w');
  }
  else if( buffComm == "e") {
    Keyboard.press('e');
  }
  else if( buffComm == "r") {
    Keyboard.press('r');
  }
  else if( buffComm == "a") {
    Keyboard.press('a');
  }
  else if( buffComm == "s") {
    Keyboard.press('s');
  }
  else if( buffComm == "d") {
    Keyboard.press('d');
  }
  else if( buffComm == "g") {
    Keyboard.press('g');
  }
  else
    Serial.println("No Commands Found!");
}

//define global calibration values
//LEFT FOOT   
// FRONT LEFT
int initialleft_1_output = 0;

//FRONT RIGHT
int initialleft_2_output = 0;

//HEEL
int initialleft_3_output = 0;

//output of the front force sensor
//RIGHT FOOT
//FRONT LEFT
int initialright_1_output = 0;

//FRONT RIGHT
int initialright_2_output = 0;

//HEEL
int initialright_3_output = 0;

//define global output sensor values
int left_1_output = 0;
int left_2_output = 0;
int left_3_output = 0;
int right_1_output = 0;
int right_2_output = 0;
int right_3_output = 0;

int buttonPress = 0;

int debug_on = 1;



void calibrateSensors() {
  //read in the analog input of sensors before start of program
  initialleft_1_output = analogRead(SENSORLEFT_1);
  initialleft_2_output = analogRead(SENSORLEFT_2);
  initialleft_3_output = analogRead(SENSORLEFT_3);
  initialright_1_output = analogRead(SENSORRIGHT_1);
  initialright_2_output = analogRead(SENSORRIGHT_2);
  initialright_3_output = analogRead(SENSORRIGHT_3);
}

void readSensors() {
  // read in analog input after t = 0
  left_1_output = abs(analogRead(SENSORLEFT_1) - initialleft_1_output);
  left_2_output = abs(analogRead(SENSORLEFT_2) - initialleft_2_output);
  left_3_output = abs(analogRead(SENSORLEFT_3) - initialleft_3_output);
  right_1_output = abs(analogRead(SENSORRIGHT_1) - initialright_1_output);
  right_2_output = abs(analogRead(SENSORRIGHT_2) - initialright_2_output);
  right_3_output = abs(analogRead(SENSORRIGHT_3) - initialright_3_output);

  // determine if button was pressed
  buttonPress = digitalRead(PUSHPIN); 
}

/////////////////////Setting Player Thresholds//////////////////////////
int player = 1;

// Creating thresholds with high and low levels
// RIGHT foot

int threshForward_R_H;
int threshForward_R_L;

int threshRight_R_H;
int threshRight_R_L;

int threshLeft_R_H;
int threshLeft_R_L;

int threshHeel_R_H;
int threshHeel_R_L;

// LEFT foot

int threshForward_L_H;
int threshForward_L_L;

int threshRight_L_H;
int threshRight_L_L;

int threshLeft_L_H;
int threshLeft_L_L;

int threshHeel_L_H;
int threshHeel_L_L;

// Setting threshold levels for players
void player1() {

  threshForward_R_H = 800;
  threshForward_R_L = 200;

  threshRight_R_H = 500;
  threshRight_R_L = 500;

  threshLeft_R_H = 500;
  threshLeft_R_L = 500;

  threshHeel_R_H = 500;
  threshHeel_R_L = 400;

  // LEFT foot

  threshForward_L_H = 500;
  threshForward_L_L = 130;

  threshRight_L_H = 500;
  threshRight_L_L = 220;

  threshLeft_L_H = 500;
  threshLeft_L_L = 200;

  threshHeel_L_H = 500;
  threshHeel_L_L = 100;
}
/////////////////////END OF Setting Player Thresholds//////////////////////////
void signalFront() {
//  Keyboard.press('w');
  pressCommand(front_command);
}
void signalRight() {
//  Keyboard.press('d');
  pressCommand(right_command);
}
void signalLeft() {
//  Keyboard.press('a');
  pressCommand(left_command);
}
void signalBack() {
//  Keyboard.press('s');
  pressCommand(back_command);
}
void signalJump() {
//  Keyboard.press(' ');
  pressCommand(jump_command);
}
void signalAim() {
//  Mouse.press(MOUSE_RIGHT);
  pressCommand(aim_command);
}
void signalReload() {
//  Keyboard.press('r');
  pressCommand(reload_command);
}
void signalCrouch() {
//  Keyboard.press('g');
  pressCommand(crouch_command);
}

void setup() {
  Serial.begin(9600);

  // set pin modes
  pinMode(SENSORRIGHT_1, INPUT);
  pinMode(SENSORRIGHT_2, INPUT);
  pinMode(SENSORRIGHT_3, INPUT);
  pinMode(SENSORLEFT_1, INPUT);
  pinMode(SENSORLEFT_2, INPUT);
  pinMode(SENSORLEFT_3, INPUT);
  pinMode(PUSHPIN, INPUT);
  pinMode(13, OUTPUT);
  pinMode(ledpin, OUTPUT);

  //initialize keyboard and mouse
  Keyboard.begin();
  Mouse.begin();

  //calibrate sensors on first pass
  calibrateSensors();

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
}

// code variable for state
// state=1: GUI customizing
// state=2: shoe ready to use
// initialize state=2
int state = 2;


/* IF USING INTEL, DON'T INCLUDE SERIAL PRINT LN'S */
void loop() {
  delay(10);

  //read in sensors right away
  readSensors();

  // Enter GUI Customization
  if(state==1) {
    // loop through 8 settings for gaming
    for(int i=0; i<8; i++) {
      if(Serial.available()) {
        memset(commands,'\0', BUFFSZ);
        readSerial(commands);
  
        setCommands(i, commands); 
      }
    }
  }

  Keyboard.releaseAll();

  if(buttonPress) {
    calibrateSensors();        //recalibrate

    //flash led to show we recalibrated
    digitalWrite(ledpin, LOW); 
    digitalWrite(ledpin, HIGH);
  }

  /////////////////Conditional LOGIC////////////////////////
  //moving
  //forward move; both RF front sensors pressed
  if(right_1_output > threshForward_R_L &&
    right_2_output > threshForward_R_L) {
    //    Keyboard.releaseAll();

    while(right_1_output > threshForward_R_L &&
      right_2_output > threshForward_R_L) {
      signalFront();
      readSensors();

      if (right_1_output < threshForward_R_L ||
        right_2_output < threshForward_R_L) {
        Keyboard.releaseAll();
      }
    }
  }
  //move right; RF right sensor pressed
  else if (right_2_output > threshRight_R_L) {
    //    Keyboard.releaseAll();
    signalRight();
    while(right_2_output > threshRight_R_L) {

      readSensors();

      if (right_2_output < threshRight_R_L) {
        Keyboard.releaseAll();
      }
    }
  }
  //move left; RF left sensors pressed 
  else if (right_1_output > threshLeft_R_L) {
    //    Keyboard.releaseAll();
    signalLeft();
    while(right_1_output > threshLeft_R_L) {

      readSensors();

      if (right_1_output < threshLeft_R_L) {
        Keyboard.releaseAll();
      }
    }
  }
  //move back
  else if(right_3_output > threshHeel_R_L) {
    //    Keyboard.releaseAll();
    signalBack();   
    while(right_3_output > threshHeel_R_L) {

      readSensors();

      if (right_3_output < threshHeel_R_L) {
        Keyboard.releaseAll();
      }
    } 
  }

  //Jump and move combos
  if(left_1_output > threshLeft_L_L) {
    //    Keyboard.releaseAll();
    signalJump();  
  }

  //jump and fwd

  else if(right_1_output > threshForward_R_L &&
    right_2_output > threshForward_R_L &&
    left_1_output > threshLeft_L_L) {
    //    Keyboard.releaseAll();
    signalFront();
    signalJump(); 
    while(right_1_output > threshForward_R_L &&
      right_2_output > threshForward_R_L &&
      left_1_output > threshLeft_L_L) {

      readSensors();

      if (right_1_output < threshForward_R_L ||
        right_2_output < threshForward_R_L ||
        left_1_output < threshLeft_L_L) {
        Keyboard.releaseAll();
      }
    }
  }

  //jump and right

  else if(right_2_output > threshRight_R_L &&
    left_1_output > threshLeft_L_L) {
    //    Keyboard.releaseAll();
    signalRight();
    signalJump(); 
    while(right_2_output > threshRight_R_L &&
      left_1_output > threshLeft_L_L) {

      readSensors();

      if (right_2_output < threshRight_R_L ||
        left_1_output < threshLeft_L_L) {
        Keyboard.releaseAll();
      }
    } 
  }

  //jump and left

  else if(right_1_output > threshLeft_R_L &&
    left_1_output > threshLeft_L_L) {
    //    Keyboard.releaseAll();
    signalLeft();
    signalJump(); 
    while(right_1_output > threshLeft_R_L &&
      left_1_output > threshLeft_L_L) {

      readSensors();

      if (right_1_output < threshLeft_R_L ||
        left_1_output < threshLeft_L_L) {
        Keyboard.releaseAll();
      }
    } 
  }

  //jump and back

  else if(right_3_output > threshHeel_R_L &&
    left_1_output > threshLeft_L_L) {
    //    Keyboard.releaseAll();
    signalBack();
    signalJump(); 
    while(right_3_output > threshHeel_R_L &&
      left_1_output > threshLeft_L_L) {

      readSensors();

      if (right_3_output < threshHeel_R_L ||
        left_1_output < threshLeft_L_L) {
        Keyboard.releaseAll();
      }
    } 
  }

  if(left_3_output > threshHeel_L_L) {
    //    Keyboard.releaseAll();
    signalCrouch();
    //        while(left_3_output > threshHeel_L_L) {
    //             
    //              readSensors();
    //
    //        if (left_3_output < threshHeel_L_L) {
    //               Keyboard.releaseAll();
    //          }
    //      } 
  }

  //crouch and fwd

  else if(right_1_output > threshForward_R_L && 
    right_2_output > threshForward_R_L &&
    left_3_output > threshHeel_L_L) {
    //    Keyboard.releaseAll();

    signalCrouch();
    signalFront(); 
    while(right_1_output > threshForward_R_L && 
      right_2_output > threshForward_R_L &&
      left_3_output > threshHeel_L_L) {

      readSensors();

      if (right_1_output < threshForward_R_L || 
        right_2_output < threshForward_R_L ||
        left_3_output < threshHeel_L_L) {
        Keyboard.releaseAll();
      }
    } 
  }

  //crouch and right
  else if(right_2_output > threshRight_R_L &&
    left_3_output > threshHeel_L_L) {
    //    Keyboard.releaseAll();
    signalRight();
    signalCrouch(); 
    while(right_2_output > threshRight_R_L &&
      left_3_output > threshHeel_L_L) {

      readSensors();

      if (right_2_output < threshRight_R_L ||
        left_3_output < threshHeel_L_L) {
        Keyboard.releaseAll();
      }
    } 
  }

  //crouch and left
  else if(right_1_output > threshLeft_R_L &&
    left_3_output > threshHeel_L_L) {
    //    Keyboard.releaseAll();
    signalLeft();
    signalCrouch(); 
    while(right_1_output > threshLeft_R_L &&
      left_3_output > threshHeel_L_L) {

      readSensors();

      if (right_1_output < threshLeft_R_L ||
        left_3_output < threshHeel_L_L) {
        Keyboard.releaseAll();
      }
    } 
  }

  //crouch and back
  else if(right_3_output > threshHeel_R_L &&
    left_3_output > threshHeel_L_L) {
    //    Keyboard.releaseAll();
    signalBack();
    signalCrouch(); 
    while(right_3_output > threshHeel_R_L &&
      left_3_output > threshHeel_L_L) {

      readSensors();

      if (right_3_output < threshHeel_R_L ||
        left_3_output < threshHeel_L_L) {
        Keyboard.releaseAll();
      }
    } 
  }

  //reload
  else if(left_2_output > threshRight_L_L) {
    //    Keyboard.releaseAll();
    signalReload();  
    delay(100);
  }

  ///////Mouse buttons
  else if(left_1_output > threshForward_L_L && left_2_output > threshForward_L_L) {
    Mouse.release(MOUSE_RIGHT);

    while(left_1_output > threshForward_L_L && left_2_output > threshForward_L_L) {
      readSensors();
      signalAim(); 
      delay(100); 
      if (
      left_1_output < threshForward_L_L || left_2_output < threshForward_L_L 
        //|| 
      //   left_1_output < threshForward_L_L && left_2_output < threshForward_L_L
      ) {
        Mouse.release(MOUSE_RIGHT);
      }
    }
    delay(100);
  }
  else{
    Keyboard.releaseAll();
  }
}

