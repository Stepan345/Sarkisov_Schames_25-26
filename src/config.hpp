#pragma once
#include "lemlib/api.hpp"
#include "liblvgl/llemu.hpp"

#include "main.h"
using namespace pros;

MotorGroup LeftDrive({-5, -6, -7}, pros::MotorGearset::blue);
MotorGroup RightDrive({1, 2, 3}, pros::MotorGearset::blue);
Imu imu(7); 
//adi::Encoder vertical_encoder('A','B',false);
adi::Encoder horizontal_encoder('C','D',false);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -6.75);
lemlib::Drivetrain drivetrain(
	&LeftDrive,
	&RightDrive,
	13.25,
	lemlib::Omniwheel::NEW_275,
	450,
	2
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(15,//15 proportional gain (kP)
                                              0, // integral gain (kI)
                                              25, //3 derivative gain (kD)
                                              3, // anti windup
                                              1, // 1 small error range, in inches
                                              100, // 100 small error range timeout, in milliseconds
                                              3, // 3 large error range, in inches
                                              500, // 500 large error range timeout, in milliseconds
                                              100 // 20 maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // 3 anti windup
                                              1, // 1 small error range, in degrees
                                              100, // 100 small error range timeout, in milliseconds
                                              31, // 3l arge error range, in degrees
                                              500, // 500 large error range timeout, in milliseconds
                                              100 // 0 maximum acceleration (slew)
);
lemlib::OdomSensors sensors(
    nullptr, // vertical tracking wheel 1, set to null
    nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
    &horizontal_tracking_wheel, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
    &imu // inertial sensor
);
// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
    5, // minimum output where drivetrain will move out of 127
    1.02 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
    5, // minimum output where drivetrain will move out of 127
    1.02// expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain,
lateral_controller,
angular_controller,
sensors,
&throttle_curve, 
&steer_curve
);
