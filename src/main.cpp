#include "main.h"
#include "aps.hpp"
using namespace pros;
//a mutex to ensure thread safety
Mutex mtx;
Controller Controller1(E_CONTROLLER_MASTER);

void APSLoop(){
	double lastRotationL;
	double lastRotationR;
	double lastRotationB;
	std::cout << "APS Loop Started" << std::endl;
	MotorGroup LeftDrive({-18, -19, -20});
	MotorGroup RightDrive({8, 9, 10});
	while(true){
		
		double deltaL;
		double deltaR;
		double deltaB;
		//if we start having thread errors move the calculation for the distance into the mutex protected zone
		mtx.take(TIMEOUT_MAX);
		//update position only when we have the mutex
		deltaL = aps::degToTravel(LeftDrive.get_position()-lastRotationL,2.75);
		deltaR = aps::degToTravel(RightDrive.get_position()-lastRotationR,2.75);
		
		lastRotationL = LeftDrive.get_position();
		lastRotationR = RightDrive.get_position();

		aps::updateGlobalTransform(deltaL,deltaR,deltaB);
		mtx.give();
		delay(5);
	}
}
void loggerLoop(){
	MotorGroup LeftDrive({-18, -19, -20});
	MotorGroup RightDrive({8, 9, 10});
	while(true){		
		mtx.take(TIMEOUT_MAX);
		aps::position pos = aps::globalPos;
		std::cout << "X: "<< pos.x << std::endl;
		std::cout << "Y: "<< pos.y << std::endl;
		std::cout << "Heading: "<< pos.heading << std::endl;
		std::cout << "LeftDriveRotation: " << LeftDrive.get_position() << std::endl;
		std::cout << "RightDriveRotation: " << RightDrive.get_position() << std::endl;
		mtx.give();
		delay(1000);
	}
}

void initialize(){
	aps::setOffsets(2,2,2);
	Task logger(loggerLoop);
	//Task APS(APSLoop);
}
void competition_initialize(){
	//LCD Autonomous Selector
}

void autonomous(){

}

void opcontrol(){
	MotorGroup LeftDrive({-18, -19, -20});
	MotorGroup RightDrive({8, 9, 10});
	while (true) {
		LeftDrive.move(Controller1.get_analog(ANALOG_LEFT_Y));
		RightDrive.move(Controller1.get_analog(ANALOG_RIGHT_Y));
		delay(1);
	}
}