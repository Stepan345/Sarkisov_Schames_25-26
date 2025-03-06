#include "main.h"
#include "config.hpp"
using namespace pros;


void competition_initialize(){
	//LCD Autonomous Selector
}
Controller Controller1(E_CONTROLLER_MASTER);
// MotorGroup LeftDrive({-18, -19, -20}, pros::MotorGearset::blue);
// MotorGroup RightDrive({8, 9, 10}, pros::MotorGearset::blue);

void autonomous(){

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