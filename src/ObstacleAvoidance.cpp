#include "ObstacleAvoidance.h"
/*
  state 0: obstacles - turning
  state 1: turned enough, go straight ahead for a second
*/

void obstacle_avoidance() {
  switch (state) {
    case 0:
      // turn 90 degrees

      // remember to update the angle of the robot

      break;
    case 1:
      // go straight for a second

      // remember to update robot position
      break;
  }

}
void function() {
/* switch (state) {
    case 0:
      distance_to_move = distance_to_move - go_distance(distance_to_move);
      if (read_sonar() < safe_dist) {
        delay(1000);
        radians_to_turn = pi/2;
        state = 1;
      }
      if (distance_to_move == 0) {
        stopmotors();
      }
      break;
    case 1:
        
        state = 2;
        break;
    case 2:
        
        break;
    case 3:
        compute_radians(robot_pos, destination_point);
        radians_to_turn = radians_to_turn - turn_radians(radians_to_turn);
        if (radians_to_turn == 0) {
          state = 0;
        }
        break;
    default:
        stopmotors();
        break;
    }
    return 0;
*/
}