#include "main.h"
#include "config.hpp"
#include "screen.hpp"
#include <string>

#include "pros/apix.h"

using namespace pros;

//char* autons[3] = {"Close","Far","Do Nothing"};
int autonSelect = 0;
//char* colors[2] = {"Blue","Red"};
int autonColor = 0;//blue = 0 red = 1
Controller Controller1(E_CONTROLLER_MASTER);
adi::DigitalOut Tongue('A');
void autonomous(){
	Motor Indexer(18);
	Motor Intake(19); 
	Motor Upper(20);	
	int turnSpeed = lv_slider_get_value(selector::turnSlider);
	float moveSpeed = lv_slider_get_value(selector::speedSlider);
	pros::Task print([](){
		while(true){
			double poseX = (chassis.getPose().x);
			double poseY = (chassis.getPose().y);
			int poseHeading = (chassis.getPose().theta);
			//Controller1.set_text(0,0,"X: "+std::to_string(poseX)+"\nY: "+std::to_string(poseY)+"\nT: "+std::to_string(poseHeading));
			std::cout << "\33[2J\r";
			std::cout << "\nX: "+std::to_string(poseX);
			std::cout << "\nY: "+std::to_string(poseY);
			std::cout << "\nT: "+std::to_string(poseHeading);
			delay(500);
		}
	});
    if(selector::autonColor == 0){
		switch(selector::autonType){ //Red
			case 0://Close
				Intake.move(127);
				Indexer.move(127);
				chassis.setPose(-49,0,180);
				Tongue.set_value(true);
				chassis.moveToPoint(-38,-48,3000,{.maxSpeed = moveSpeed},false);
				chassis.turnToHeading(-90,2000,{.maxSpeed = turnSpeed},false);
				chassis.moveToPose(-58,-47,-90,5000,{.maxSpeed = 127},false);//move to tube
				delay(4000);
				chassis.moveToPoint(-48,-48,2000,{.forwards = false,.maxSpeed = moveSpeed},false);
				Tongue.set_value(false);
				break;
			case 1://Far
				chassis.setPose(-48,-12,90);
				Intake.move(127);
				Indexer.move(-127);
				chassis.moveToPose(-36,-24,90,3000,{.maxSpeed = moveSpeed,.minSpeed = moveSpeed-50},false);
				chassis.moveToPoint(-13,-24,3000,{.maxSpeed = moveSpeed*0.75f},false);//pick up center cubes
				chassis.turnToPoint(-48,-48,3000,{.maxSpeed = turnSpeed},false);
				Indexer.brake();
				Intake.brake();
				chassis.moveToPoint(-48,-48,3000,{.maxSpeed = moveSpeed},false);
				Tongue.set_value(true);//extend tongue
				chassis.turnToPoint(-58,-48,3000,{.maxSpeed = (int)moveSpeed},false);
				Intake.move(127);
				Indexer.move(-127);
				chassis.moveToPose(-58,-48,-90,5000,{.maxSpeed = 127},false);//move to tube
				delay(3000);//wait a couple of seconds to intake
				chassis.moveToPoint(-48,-48,2000,{.forwards = false,.maxSpeed = moveSpeed},false);//reverse out of the tube
				chassis.turnToHeading(90,2000,{.maxSpeed = turnSpeed},false);
				Tongue.set_value(false);//retract tongue
				delay(500);//half a second delay to let tongue fully retract
				chassis.moveToPose(-30,-48,90,2000,{.maxSpeed = moveSpeed},false);//move to long goal
				Intake.move(127);
				Indexer.move(127);
				Upper.move(127);//outake
				while(!Controller1.get_digital_new_press(DIGITAL_A)){//reverses the indexer every couple of seconds in order to stop the balls from getting stuck
					delay(3000);
					Indexer.move(-127);
					delay(1000);
					Indexer.move(127);
				}
				break;
			case 2://Anti Auton
				chassis.setPose(0,0,0);
				chassis.moveToPoint(24,24,6700,{.maxSpeed = moveSpeed},false);
				delay(5000);
				chassis.turnToPoint(0,0,6700,{.maxSpeed = turnSpeed},false);
				chassis.moveToPoint(0,0,6700,{.maxSpeed = moveSpeed},false);
				chassis.turnToHeading(0,6700,{.maxSpeed = turnSpeed},false);
				delay(1000);
				chassis.moveToPose(24,24,90,6700,{.maxSpeed = moveSpeed},false);
				delay(5000);
				chassis.turnToPoint(0,0,6700,{.maxSpeed = turnSpeed},false);
				chassis.moveToPoint(0,0,6700,{.maxSpeed = moveSpeed},false);
				chassis.turnToHeading(0,6700,{.maxSpeed = turnSpeed},false);
				break;
		}
	}else if(selector::autonColor == 1){
		switch(selector::autonType){ //blue
			case 0://Close
				

				break;
			case 1://Far

				break;
			case 2://Do nothing
				
				//chassis.turnToHeading(-95,3000,{.direction = lemlib::AngularDirection::CW_CLOCKWISE},false);
				break;
		}

	}else{//skills
		switch(selector::autonType){
			case 0://Skills 1
				chassis.setPose(-48,0,90);
				Intake.move(127);
				Indexer.move(-127);
				//collect balls from center
				chassis.turnToPoint(-17,28,2000,{.maxSpeed = turnSpeed},false);
				chassis.moveToPoint(-17,28,4000,{.maxSpeed = moveSpeed*0.666f,.minSpeed=moveSpeed*0.333f},false);
				chassis.moveToPoint(28,25,4000,{.maxSpeed = moveSpeed,.minSpeed = moveSpeed * 0.666f},false);
				chassis.moveToPoint(38,47,4000,{.maxSpeed = moveSpeed},false);
				Tongue.set_value(true);
				//align with loader
				chassis.turnToPoint(68,47,2000,{.maxSpeed = turnSpeed},false);
				chassis.moveToPose(58,47,90,5000,{.maxSpeed = 127},false);//move to tube
				for(int i=0;i<5;i++){//rock back and forth to intake balls better
					delay(1000);//wait a couple of seconds to intake
					chassis.moveToPoint(53,47,2000,{.forwards = false,.maxSpeed = moveSpeed},false);
					chassis.moveToPose(58,47,90,5000,{.maxSpeed = moveSpeed},false);
				}
				chassis.moveToPoint(48,47,2000,{.forwards = false,.maxSpeed = moveSpeed},false);//reverse out of the tube
				chassis.turnToHeading(-90,2000,{.maxSpeed = turnSpeed},false);
				Tongue.set_value(false);//retract tongue
				delay(500);//half a second delay to let tongue fully retract
				chassis.moveToPose(30,-48,-90,2000,{.maxSpeed = moveSpeed},false);//move to long goal
				Intake.move(127);
				Indexer.move(127);
				Upper.move(127);//outake
				delay(5000);
				Upper.brake();
				Indexer.move(-127);
				chassis.moveToPoint(48,47,2000,{.forwards = false,.maxSpeed = moveSpeed},false);//reverse out of long goal
				chassis.turnToPoint(24,-24,2000,{.maxSpeed = turnSpeed},false);
				chassis.moveToPose(24,-24,-90,4000,{.maxSpeed = moveSpeed,.minSpeed = moveSpeed * 0.5f},false);
				chassis.moveToPose(-24,-24,225,4000,{.maxSpeed = moveSpeed,.minSpeed = moveSpeed * 0.5f},false);
				chassis.moveToPoint(-48,-48,5000,{.maxSpeed = moveSpeed},false);
				Tongue.set_value(true);//extend tongue
				chassis.turnToPoint(-58,-48,2000,{.maxSpeed = turnSpeed},false);
				chassis.moveToPose(-58,-48,-90,5000,{.maxSpeed = 127},false);//move to tube
				for(int i=0;i<5;i++){//rock back and forth to intake balls better
					delay(1000);//wait a couple of seconds to intake
					chassis.moveToPoint(55,47,2000,{.forwards = false,.maxSpeed = moveSpeed},false);
					chassis.moveToPose(58,47,-90,5000,{.maxSpeed = moveSpeed},false);
				}
				chassis.moveToPoint(-48,-48,2000,{.forwards = false,.maxSpeed = moveSpeed},false);//reverse out of the tube
				chassis.turnToHeading(90,2000,{.maxSpeed = turnSpeed},false);
				Tongue.set_value(false);//retract tongue
				delay(500);//half a second delay to let tongue fully retract
				chassis.moveToPose(-30,-48,90,2000,{.maxSpeed = moveSpeed},false);//move to long goal
				Intake.move(127);
				Indexer.move(127);
				Upper.move(127);//outake
				while(!Controller1.get_digital_new_press(DIGITAL_A)){//reverses the indexer every couple of seconds in order to stop the balls from getting stuck
					delay(3000);
					Indexer.move(-127);
					delay(1000);
					Indexer.move(127);
				}
				break;
			case 2://Anti Auton
				
				break;
		}
	}

	//selector::disableDebug();
}
void initialize(){
	selector::screenInit();
    chassis.calibrate(); //calibrate sensors

	
}
void competition_initialize(){
	selector::disableDebug();
}

int tongueState = 0;
void pistonUpdate(){
	tongueState = !tongueState;
	Tongue.set_value(tongueState);
}
Distance dist(4);
void opcontrol(){
	//chassis.calibrate(false);
	//Task controllerUI(UI)
	
	int intake = 0;
	int indexer = 0;
	int upper = 0;
	Motor Indexer(18);
	Motor Intake(19); 
	Motor Upper(20);	
	selector::debugLoop(Controller1);
	//Controller1.set_text(0,0,"works");
	//Controller1.clear();
	double lastVal = 0;
	int errRange = 50;
	int ballCount = 0;
	while (true){
		if(indexer < 0){
			//while out-taking detect on leaving frame. actual < last
			double difference = dist.get() - lastVal;
			if(difference<-errRange){
				ballCount--;
				ballCount = (ballCount < 0)?0:ballCount;
			}
		}else if(indexer > 0){
			double difference = dist.get() - lastVal;
			if(difference>errRange){
				ballCount++;
			}
		}
		//Controller1.set_text(0,0,"X:"+std::to_string(chassis.getPose().x)+" Y: "+std::to_string(chassis.getPose().y));
		Controller1.set_text(0,0,"Cubits: "+std::to_string(ballCount));
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
		if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
			upper = 0;
			indexer = 0;
			intake = 0;
		}
		if(Controller1.get_digital(E_CONTROLLER_DIGITAL_B)){
			indexer = -1;
		}
		if(Controller1.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)){
			pistonUpdate();
		}
		Indexer.move(95.25*indexer);
		Intake.move(127*intake);
		Upper.move(127*upper);
		delay(5);
	}
}
