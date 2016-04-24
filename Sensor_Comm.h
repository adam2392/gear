#ifndef SENSOR_COMM_H_
#define SENSOR_COMM_H_

#include <Arduino.h>

class Sensor_Comm {
public:
	Sensor_Comm(int sensorleft_1, int sensorleft_2, int sensorleft_3, 
		int sensorright_1, int sensorright_2, int sensorright_3, int pushpin);
	void calibrateSensors();
	void readSensors();

	//member-accessor functions
	int read_left1output();
	int read_left2output();
	int read_left3output();
	int read_right1output();
	int read_right2output();
	int read_right3output();
	int read_buttonPress();

	private:
	// initialize SENSOR pins
	int SENSORLEFT_1;
	int SENSORLEFT_2;
	int SENSORLEFT_3;
	int SENSORRIGHT_1;
	int SENSORRIGHT_2;
	int SENSORRIGHT_3;
	int PUSHPIN;

	//define global calibration values
	//LEFT FOOT   
	// FRONT LEFT
	int initialleft_1_output;
	//FRONT RIGHT
	int initialleft_2_output;
	//HEEL
	int initialleft_3_output;
	//output of the front force sensor
	 //RIGHT FOOT
	//FRONT LEFT
	int initialright_1_output;
	//FRONT RIGHT
	int initialright_2_output;
	//HEEL
	int initialright_3_output;

	//define global output sensor values
	int left_1_output;
	int left_2_output;
	int left_3_output;
	int right_1_output;
	int right_2_output;
	int right_3_output;
	int buttonPress;
};
#endif