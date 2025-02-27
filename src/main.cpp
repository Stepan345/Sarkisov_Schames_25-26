#include "main.h"
using namespace pros;


void competition_initialize(){
	//LCD Autonomous Selector
}
Controller Controller1(E_CONTROLLER_MASTER);
MotorGroup LeftDrive({18, 19, 20});
MotorGroup RightDrive({8, 9, 10});
void autonomous(){

}

void opcontrol(){
	while (true) {
		LeftDrive.move(Controller1.get_analog(ANALOG_LEFT_Y));
		RightDrive.move(Controller1.get_analog(ANALOG_RIGHT_Y));
	}
}