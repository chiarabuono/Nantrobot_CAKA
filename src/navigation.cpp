#include<iostream>
#include<vector>
#include<tuple>
#include <Arduino.h>
#include <math.h>

double const pi = 3.14159265358979323846;

float turn_radians(float radians) {
    return 0;
}

float go_distance(float dist){
    return 0;
}

void obstacle_avoidance();

class Robot{
    public:
        double cur_speed;
        double x = 0;
        double y = 0;
        double orientation = pi; // angle to the +ve x axis, can only take four values (0, 90, 180, 270)
        int state = 0;
        void turnLeft();
        void turnRight();
        void moveForward();
        void moveBackward();
        void stopmotors();


        void setXY(){
            //computes the current x and y coordinates of the robot every defined time period
        }

        void setOrientation(){

        }


        std::pair<double, double> Displacement(std::pair<double, double> destination){
            // computes the displacement vector from the current coordinates to the destination
            // should run every x seconds
            auto [x_dest, y_dest] = destination;
            double dx = x_dest - x;
            double dy = y_dest - y;

            double distance = sqrt(pow(dx, 2) + pow(dy, 2));
            double angle = atan2(dy, dx);   // possible point of error, many angles can give the same tan

            return {distance, angle};
        }
};

std::pair<double, double> destination = {2, 3};
auto [x_dest, y_dest] = destination;

void loop(){

    Robot robot;

    switch(robot.state){
        case 0:
            robot.stopmotors();
        case 1:
                // compute current coordinates relative to the origin
            robot.setXY();

            // compute distance and heading to the destination
            
            auto [distance, heading] = robot.Displacement(destination);
            double turn_angle = heading - robot.orientation;
            turn_radians(turn_angle);
            robot.orientation = robot.orientation + turn_angle;
            while (distance > 10){ // while distance is greater than some threshold value
                double distance = distance- go_distance(distance);
            }
            robot.state = 0;
        case 2:
            obstacle_avoidance();
            robot.state = 1;
        default:
            robot.stopmotors();
        
    }

    
    

}
