// http://stackoverflow.com/questions/21396985/how-to-use-cgeventcreatekeyboardevent-in-python-on-mac
// https://developer.apple.com/library/mac/documentation/Carbon/Reference/QuartzEventServicesRef/index.html#//apple_ref/c/tdef/CGMouseButton

#include "ControlComputer.h"
#include "string.h"


void ControlComputer::readSerial(char *outCommands) {
  bool stringComplete = false; //whether string is complete or not
  char incomingByte;              //buffer to store incoming characters in serial
  int index = 0;                  //to index through char array

  //loop to read in serial data
  while(Serial.available()) {
    incomingByte = Serial.read();     // read in byte by byte

    if(incomingByte == '\n') {        // when newline, terminate
      stringComplete = true;
      break;
    }
    outCommands[index] = incomingByte; //store the character read
    index++;                           //increment index
  }
}


void ControlComputer::signalFront() {
//  Keyboard.press('w');
  pressCommand(&front_command);
  // Serial.println("w");
  // Serial.println("new command down");
  // Serial.println(front_command);
}
void ControlComputer::signalRight() {
//  Keyboard.press('d');
  pressCommand(&right_command);
  // Serial.println("d");
}
void ControlComputer::signalLeft() {
//  Keyboard.press('a');
  pressCommand(&left_command);
  // Serial.println("a");
}
void ControlComputer::signalBack() {
//  Keyboard.press('s');
  pressCommand(&back_command);
  // Serial.println("s");
}
void ControlComputer::signalJump() {
//  Keyboard.press(' ');
  pressCommand(&jump_command);
  // Serial.println(" ");
}
void ControlComputer::signalAim() {
//  Mouse.press(MOUSE_RIGHT);
  pressCommand(&aim_command);
}
void ControlComputer::signalReload() {
//  Keyboard.press('r');
  pressCommand(&reload_command);
  // Serial.println("r");
}
void ControlComputer::signalCrouch() {
//  Keyboard.press('g');
  pressCommand(&crouch_command);
  // Serial.println("g");
}

void ControlComputer::pressCommand(char *comm) {
  char *buffComm = comm;  
  // Serial.println(*buffComm);
  // Serial.print("This is comm: ");
  // Serial.print(comm);

  if( *buffComm == UP_ARROW) {
    Serial.flush();
    Serial.println("UP");
    Serial.flush();
  }
  else if( *buffComm == RIGHT_ARROW) {
    Serial.flush();
    Serial.println("DOWN");
    Serial.flush();
  }
  else if( *buffComm == LEFT_ARROW) {
    Serial.flush();
    Serial.println("LEFT"); 
    Serial.flush();
  }
  else if(*buffComm == DOWN_ARROW) {
    Serial.flush();
   Serial.println("DOWN");
   Serial.flush();
  }
  else if(*buffComm == SPACE) {
    Serial.flush();
    Serial.println("SPACE");
    Serial.flush();
  }
  else if( *buffComm == 'q') {
    Serial.flush();
    Serial.println("q");
    Serial.flush();
  }
  else if( *buffComm == 'w') {
    Serial.flush();
    Serial.println("w");
    Serial.flush();
  }
  else if( *buffComm == 'e') {
    Serial.flush();
    Serial.println("e");
    Serial.flush();
  }
  else if( *buffComm == 'r') {
    Serial.flush();
    Serial.println("r");
    Serial.flush();
  }
  else if( *buffComm == 'a') {
    Serial.flush();
    Serial.println("a");
    Serial.flush();
  }
  else if( *buffComm == 's') {
    Serial.flush();
    Serial.println("s");
    Serial.flush();
  }
  else if( *buffComm == 'd') {
    Serial.flush();
    Serial.println("d");
    Serial.flush();
  }
  else if( *buffComm == 'g') {
    Serial.flush();
    Serial.println("g");
    Serial.flush();
  }
  else {
    // Serial.print(*buffComm);
    Serial.print('not set');
    Serial.flush();
  }
}

/* Function: setCommands
 Input: index - the index of which command to set
 comm - the char pointer to 
 */
void ControlComputer::setCommands(int index, char* comm) {  
  if(index==0) {
    front_command = *comm;
  }
  else if(index==1) {
    right_command = *comm;
  }
  else if(index==2) {
    left_command = *comm;
  }
  else if(index==3) {
    right_command = *comm;
  }
  else if(index==4) {
    back_command = *comm;
  }
  // else if(index==5) {
  //   aim_command = comm;
  // }
  else if(index==6) {
    reload_command = *comm;
  }
  else if(index==7) {
    crouch_command = *comm;
  }
}