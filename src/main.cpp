#include "main.h"
#include "config.hpp"
#include "screen.hpp"
#include <string>

#include "pros/apix.h"

using namespace pros;

char* autons[3] = {"Close","Far","Do Nothing"};
int autonSelect = 0;
char* colors[2] = {"Blue","Red"};
int autonColor = 0;//blue = 0 red = 1
Controller Controller1(E_CONTROLLER_MASTER);


void autonomous(){
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
				chassis.moveToPoint(-15,36,2000,{.forwards = false, .maxSpeed = moveSpeed},false);
				break;
			case 2://Anti Auton
				chassis.setPose(-60,12,-90);
				intake.move(127);
				chassis.moveToPoint(-12,12,4000,{.forwards = false});
				//chassis.turnToHeading(-95,3000,{.direction = lemlib::AngularDirection::CW_CLOCKWISE},false);
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
				chassis.moveToPoint(15,36,3000,{.forwards = false,.maxSpeed = moveSpeed},false);
				break;
			case 2://Do nothing
				chassis.setPose(-60,12,-90);
				intake.move(127);
				chassis.moveToPoint(-12,12,4000,{.forwards = false});
				//chassis.turnToHeading(-95,3000,{.direction = lemlib::AngularDirection::CW_CLOCKWISE},false);
				break;
		}

	}

	//selector::disableDebug();
}
void initialize(){
	selector::screenInit();
    //chassis.calibrate(); // calibrate sensors
	
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
// void UI(){
// 	int cursor = 0;
// 	auto options[3] = {
// 		"Upper Score",
// 		"Middle Score",
// 		"Lower Score"

// 	};
// 	auto rumbleOptions[3] = {
// 		".",
// 		"..",
// 		"..."
// 	};
// 	while(true){
// 		if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
// 			cursor = (cursor <= 0)?0:cursor-=1;
// 			controller_rumble(rumbleOptions[cursor]);
// 		}
// 		if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
// 			cursor = (cursor >= 2)?2:cursor+=1;
// 			controller_rumble(rumbleOptions[cursor]);
// 		}
// 		for(int i = 0;i<stringOptions.length;i+=1){
// 			Controller1.set_text(i,0,obj_created + (cursor == i)?"<":"");
// 		}
// 		delay(250);
// 	}
// }
void opcontrol(){
	//Task controllerUI(UI)
	Motor Indexer(18);
	Motor Intake(19); 
	Motor Upper(20);
	selector::debugLoop(Controller1);
	int intake = 0;
	int indexer = 0;
	int upper = 0;
	while (true) {
		
		chassis.tank(Controller1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),Controller1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
		if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)){
			intake = (intake == 1)?0:1;
		}else if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
			intake = (intake == -1)?0:-1;
		}

		if(Controller1.get_digital(E_CONTROLLER_DIGITAL_UP)){
			intake = 1;
			upper = 0;
			indexer = -1.5;
		}
		if(Controller1.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
			intake = -1;
			indexer = 1;
			upper = 0;
		}
		if(Controller1.get_digital(E_CONTROLLER_DIGITAL_L1)){
			upper = -1;
			indexer = 1;
			intake = 1;
		}
		if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
			upper = 1;
			indexer = 1;
			intake = 1;
		}
		if(Controller1.get_digital(E_CONTROLLER_DIGITAL_A)){
			upper = 0;
			indexer = 0;
			intake = 0;
		}
		if(Controller1.get_digital(E_CONTROLLER_DIGITAL_B)){
			indexer = -1;
		}
		Indexer.move(95.25*indexer);
		Intake.move(127*intake);
		Upper.move(127*upper);
		delay(5);
	}
}
