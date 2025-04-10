#include "main.h"
#include "config.hpp"
#include "screen.hpp"

#include "pros/apix.h"

using namespace pros;

char* autons[3] = {"Close","Far","Do Nothing"};
int autonSelect = 0;
char* colors[2] = {"Blue","Red"};
int autonColor = 0;//blue = 0 red = 1
Controller Controller1(E_CONTROLLER_MASTER);


void autonomous(){
	Task screen_task([&]() {
		while (true) {
			// print robot location to the brain screen
			pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
			pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
			pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
			// delay to save resources
			pros::delay(20);
		}
	});
	MotorGroup intake({-1,11});
	int turnSpeed = 40;
	float moveSpeed = lv_slider_get_value(selector::speedSlider);
    if(!selector::autonColor){
		switch(selector::autonType){ //Red
			case 0://Close
				chassis.setPose(-60,60,90);
				intake.move(-127);
				chassis.moveToPoint(-12,60,4000,{.maxSpeed = moveSpeed},false);
				break;
			case 1://Far
				chassis.setPose(-60,12,90);
				intake.move(127);
				chassis.moveToPoint(-12,12,3000,{.maxSpeed = moveSpeed},false);
				
				chassis.turnToHeading(0,2000,{.maxSpeed = turnSpeed},false);
				intake.move(-127);
				
				chassis.moveToPoint(-12,48,3000,{.maxSpeed = moveSpeed},false);
				
				chassis.moveToPoint(-12,24,2000,{.forwards = false,.maxSpeed = moveSpeed},false);
				delay(500);
				chassis.moveToPoint(-12,48,3000,{.maxSpeed = moveSpeed},false);
				
				chassis.moveToPoint(-12,36,2000,{.forwards = false,.maxSpeed = moveSpeed},false);
				
				chassis.turnToPoint(-60,36,2000,{.maxSpeed = turnSpeed},false);
				intake.move(127);
				chassis.moveToPoint(-64,36,3000,{.maxSpeed = moveSpeed},false);
				delay(1000);
				
				chassis.moveToPoint(-15,36,3000,{.forwards = false,.maxSpeed = moveSpeed},false);
				
				chassis.turnToPoint(-12,48,2000,{.maxSpeed = turnSpeed},false);
				intake.move(-127);
				delay(2000);
				chassis.moveToPoint(-12,48,2000,{.maxSpeed = moveSpeed},false);


				break;
			case 2://Anti Auton
				chassis.setPose(-60,12,-90);
				intake.move(127);
				chassis.moveToPoint(-12,12,4000,{.forwards = false});
				chassis.turnToHeading(-95,3000,{.direction = lemlib::AngularDirection::CW_CLOCKWISE},false);
				break;
		}
	}else{
		switch(selector::autonType){ //blue
			case 0://Close
				chassis.setPose(60,60,-90);
				intake.move(-127);
				chassis.moveToPoint(12,60,4000,{.maxSpeed = moveSpeed},false);
				break;
			case 1://Far
				chassis.setPose(60,12,-90);
				intake.move(127);
				chassis.moveToPoint(12,12,3000,{.maxSpeed = moveSpeed},false);
				
				chassis.turnToPoint(12,48,2000,{.maxSpeed = turnSpeed},false);
				intake.move(-127);
				
				chassis.moveToPoint(12,48,3000,{.maxSpeed = moveSpeed},false);
				
				chassis.moveToPoint(12,24,2000,{.forwards = false,.maxSpeed = moveSpeed},false);
				delay(500);
				chassis.moveToPoint(12,48,3000,{.maxSpeed = moveSpeed},false);
				
				chassis.moveToPoint(12,36,2000,{.forwards = false,.maxSpeed = moveSpeed},false);
				chassis.turnToPoint(60,36,2000,{.maxSpeed = turnSpeed},false);
				intake.move(127);
				chassis.moveToPoint(64,36,3000,{.maxSpeed = moveSpeed},false);
				delay(1000);
				
				chassis.moveToPoint(15,36,3000,{.forwards = false,.maxSpeed = moveSpeed},false);
				
				chassis.turnToPoint(12,48,2000,{.maxSpeed = turnSpeed},false);
				intake.move(-127);
				delay(1000);
				chassis.moveToPoint(12,48,2000,{.maxSpeed = moveSpeed},false);
				break;
			case 2://Do nothing
			break;
		}

	}
	selector::disableDebug();
	while (true)
	{
		delay(100);
	}
}
void initialize(){
	selector::screenInit();
    chassis.calibrate(); // calibrate sensors
	
}
void competition_initialize(){
	selector::disableDebug();
}
ADIDigitalOut leftWing('B');
ADIDigitalOut rightWing('A');
void pistonUpdate(bool leftPiston, bool rightPiston){
	leftWing.set_value(leftPiston);
	rightWing.set_value(rightPiston);
}
void opcontrol(){
	MotorGroup intake({1,-11});
	selector::debugLoop(Controller1);
	int intakeSpin = 0;
	bool piston[2] = {false,false};
	bool pistonActual = false;
	while (true) {
		if(Controller1.get_digital_new_press(DIGITAL_Y)){
			//right wing indivigual
			piston[1] = !piston[1];
			pistonActual = !piston[1];
			if(piston[0] == piston[1]){
				pistonActual = piston[0];
			}
			pistonUpdate(piston[0],piston[1]);
		}
		if(Controller1.get_digital_new_press(DIGITAL_RIGHT)){
			//left wing indivigual
			piston[0] = !piston[0];
			pistonActual = !piston[0];
			if(piston[0] == piston[1]){
				pistonActual = piston[0];
			}
			pistonUpdate(piston[0],piston[1]);
		}
		if(Controller1.get_digital_new_press(DIGITAL_L1)){
			pistonActual = !pistonActual;
			piston[0] = pistonActual;
			piston[1] = pistonActual;
			pistonUpdate(piston[0],piston[1]); 
		}
		if(Controller1.get_digital_new_press(DIGITAL_R1)){
			intakeSpin = (intakeSpin == 0)?-1:(intakeSpin == 1)?-1:0;
		}

		if(Controller1.get_digital_new_press(DIGITAL_R2)){
			intakeSpin = (intakeSpin == 0)?1:(intakeSpin == -1)?1:0;
		}
		intake.move(intakeSpin*127);
		int leftY = Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int rightY = Controller1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		chassis.tank(leftY, rightY);
		delay(1);
	}
	
}