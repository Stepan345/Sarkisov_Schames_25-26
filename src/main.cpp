#include "main.h"
#include "aps.hpp"
using namespace pros;

//a mutex to ensure thread safety
Mutex mtx;


void APSLoop(){
	double lastRotationL;
	double lastRotationR;
	double lastRotationB;
	std::cout << "APS Loop Started" << std::endl;
	while(true){
		double deltaL;
		double deltaR;
		double deltaB;
		//if we start having thread errors move the calculation for the distance into the mutex protected zone
		mtx.take(TIMEOUT_MAX);
		//update position only when we have the mutex
		aps::updateGlobalTransform(deltaL,deltaR,deltaB);
		mtx.give();
		delay(5);
	}
}
void initialize(){
	Task APS(APSLoop);
}
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

		if(!mtx.take(5))continue;
		aps::position pos = aps::globalPos;
		mtx.give();
		std::cout << "X: "<< pos.x << std::endl;
		std::cout << "Y: "<< pos.y << std::endl;
		std::cout << "Heading: "<< pos.heading << std::endl;


		delay(1);
	}
}