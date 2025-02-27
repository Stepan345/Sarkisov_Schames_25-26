#include <cmath>
namespace aps{struct position{
    double x;
    double y;
    double heading;
};
position globalPos = {0,0,0};

position getGlobalPosition(){
    return globalPos;
}
double sL;
double sR;
double sB;

void setOffsets(double offsetL, double offsetR, double offsetB){
    sL = offsetL;
    sR = offsetR;
    sB = offsetB;
}

double getLocalYTransform(double deltaL,double deltaR){
    if(deltaL == deltaR){
        //if the robot went in a straight line, just return the distance.
        return deltaL;
    }
    //change in heading
    double deltaTheta = (deltaL-deltaR)/(sL+sR);
    
    double arcLength = (deltaR/deltaTheta)+sR;

    double chordLength = 2* std::sin(deltaTheta/2)*arcLength;
    return chordLength;
}
double getLocalXTransform(double deltaL,double deltaR,double deltaB){
    double deltaTheta = (deltaL-deltaR)/(sL+sR);
    //expected travel if the turn had no drift
    double perfectDistance = 2 * M_PI * sB * (deltaTheta/2*M_PI);

    double drift = deltaB-perfectDistance;
    return drift;
}
position rotateTransform(position transform,double rotation){
    position rotatedTransform;
    rotatedTransform.x = ((transform.x*std::cos(-rotation))+(transform.y*std::sin(rotation/2)));
    rotatedTransform.y = ((transform.x*std::sin(-rotation))+(transform.y*std::cos(rotation/2)));
    rotatedTransform.heading = transform.heading+rotation;
    return rotatedTransform;
}

void updateGlobalTransform(double deltaL,double deltaR,double deltaB){

    return;
}}