#include <Sensor_Comm.h>

Sensor_Comm::Sensor_Comm(int sensorleft_1, int sensorleft_2, int sensorleft_3,
	int sensorright_1, int sensorright_2, int sensorright_3, int pushpin) {
	// set sensors
	SENSORLEFT_1 = sensorleft_1;
	SENSORLEFT_2 = sensorleft_2;
	SENSORLEFT_3 = sensorleft_3;
	SENSORRIGHT_1 = sensorright_1;
	SENSORRIGHT_2 = sensorright_2;
	SENSORRIGHT_3 = sensorright_3;
	PUSHPIN = pushpin;
}

void Sensor_Comm::calibrateSensors() {
	//read in the analog input of sensors before start of program
    initialleft_1_output = analogRead(SENSORLEFT_1);
    initialleft_2_output = analogRead(SENSORLEFT_2);
    initialleft_3_output = analogRead(SENSORLEFT_3);
    initialright_1_output = analogRead(SENSORRIGHT_1);
    initialright_2_output = analogRead(SENSORRIGHT_2);
    initialright_3_output = analogRead(SENSORRIGHT_3);
}
void Sensor_Comm::readSensors() {
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

/* MEMBER ACCESSOR FUNCTIONS */
int Sensor_Comm::read_left1output() {
	return left_1_output;
}
int Sensor_Comm::read_left2output() {
	return left_2_output;
}
int Sensor_Comm::read_left3output() {
	return left_3_output;
}
int Sensor_Comm::read_right1output() {
	return right_1_output;
}
int Sensor_Comm::read_right2output() {
	return right_2_output;
}
int Sensor_Comm::read_right3output() {
	return right_3_output;
}
int Sensor_Comm::read_buttonPress() {
	return buttonPress;
}

