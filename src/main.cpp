#include "main.h"
#include "config.hpp"
using namespace pros;


void competition_initialize(){
	//LCD Autonomous Selector
}
Controller Controller1(E_CONTROLLER_MASTER);
ASSET(path_txt);
void autonomous(){
    chassis.setPose(0, 0, 0);
    chassis.follow(path_txt,10,60000);
    //chassis.turnToHeading(90,1000000);
}
void initialize(){
	init();
}
void opcontrol(){
	while (true) {
		int leftY = Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int rightY = Controller1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		chassis.tank(leftY, rightY);
		delay(1);
	}
}