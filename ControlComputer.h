#ifndef CONTROLCOMPUTER_H_
#define CONTROLCOMPUTER_H_

#include <Arduino.h>
#include <string.h>

class ControlComputer {
public:
	// ControlComputer() : front_command('w') {}
	// ControlComputer();

	// action press Keyboard functions
	void signalFront();
	void signalRight();
	void signalLeft();
	void signalBack();
	void signalJump();
	void signalAim();
	void signalReload();
	void signalCrouch();

	void pressCommand(char *comm);
	void readSerial(char *outCommands);

	/* Function: setCommands
	 Input: index - the index of which command to set
	 comm - the char pointer to 
	 */
	void setCommands(int index, char* comm);

	private:
		// enum { BUFFSZ = 100 };
		// const char UP_ARROW[sizeof("up_arrow")] = "up_arrow";
		// const char DOWN_ARROW[sizeof("down_arrow")] = "down_arrow";
		// const char RIGHT_ARROW[sizeof("right_arrow")] = "right_arrow";
		// const char LEFT_ARROW[sizeof("left_arrow")] = "left_arrow";
		// const char SPACE[sizeof("space")] = "space";
		// const char SHIFT[sizeof("shift")] = "shift";
		// const char RIGHT_MOUSE[sizeof("right_mouse")] = "right_mouse";

		const char SPACE = '1';
		const char UP_ARROW = '2';
		const char DOWN_ARROW = '3';
		const char RIGHT_ARROW = '4';
		const char LEFT_ARROW = '5';
		const char SHIFT = '6';
		const char RIGHT_MOUSE = '7';

		// char commands[BUFFSZ];
		char front_command = 'w';
		char right_command = 'd';
		char left_command = 'a';
		char back_command = 's';
		char jump_command = '1';
		char aim_command = 'aiming not set';
		char reload_command = 'r';
		char crouch_command = 'g';
};
#endif