/*

Author : Nathaniel Mann (except for drive up ramp method)
TO-DO :
        X move the fucntions to a library file




NOTES
      How to //print accel values
        //printf("%i\n",accel_y());
        //printf("%i\n",accel_y());







*/




#include <kipr/botball.h>
///////////////////////////////////////////////////////////////////////////////
//preprocessor definitions
///////////////////////////////////////////////////////////////////////////////

// general usefull information
#define ticks 955.8
#define ticks_per_centimeter ticks/18
#define l_motor_factor  1//0.55
#define r_motor_factor 1

#define axisSensor 30

//servos and motors
#define left_motor 0
#define right_motor 1
#define lift_arm 2//farthest is 1200, closest is 170
#define raise_robot 0//1630 is highest, 140 is lowest
#define lift_claw 3//-100 is highest, 2360 is lowest
#define open_claw 1//2000 is closed, 900 is open

// sensors
#define left_light 1
#define right_light 0

// directions for driviing and turns
#define forward 1
#define backward -1
#define right -1
#define left 1

// positons for the wheels
#define tall 1630
#define low 0
#define rampPosition 800


///////////////////////////////////////////////////////////////////////////////
// fucntion definitons
///////////////////////////////////////////////////////////////////////////////
void moveWheels(int wheelPosition);
void driveUpTheRamp();
void twoStepTurn(int speed, int time, int turnDirection, int driveDirection);
void turn(int speed, int time, int direction);
void drive(int speed, int distance, int direction);
void moveServo(int port, int position, int speed);


///////////////////////////////////////////////////////////////////////////////
//main method
///////////////////////////////////////////////////////////////////////////////

int main()
{

    set_servo_position(raise_robot, low);
    enable_servos();
    moveServo(2, 350, 50);
    //drive(100, 30, backward);
    motor (left_motor, -100*l_motor_factor);
    motor (right_motor, -100*r_motor_factor);
msleep(1500);
    int i;
    for(i = 1; i<20; i++){
        set_servo_position(raise_robot, rampPosition);
    msleep(150);
        set_servo_position(raise_robot, low);
    }

    msleep(2000);



    /*
    //drive on to the ramp
    drive(100, 10, backward);

    //call the ramp method
    moveWheels(rampPosition);
    msleep(400);
    while(analog (right_light) < 4050){
        motor (left_motor, -50);
       	motor (right_motor, -25);
        msleep(20);
    }
    driveUpTheRamp();
    twoStepTurn(75, 860, right, backward);// this is a place that it could go wrong bc I changed it to backward from forward
    // initial two stage turn procedure
    drive(75, 5, forward);
    twoStepTurn(75, 860, right, backward);// this is a place that it could go wrong bc I changed it to backward from forward
*/
    return 0;
}




///////////////////////////////////////////////////////////////////////////////
//method definitions
///////////////////////////////////////////////////////////////////////////////

/* Name     : drive
Purpose     : turns two motors making the robor drive in a certain direction
Parameters  : int speed     - the speed (0-100) at which the robot will turn
              int distance  - roughly the distance in CM that the robot will driveUpTheRamp
              int direction - the direction that the robot will turn. Pass in either forward OR backward.
*/
void drive(int speed, int distance, int direction){
    int tick_distance = ticks_per_centimeter * distance;
	clear_motor_position_counter(left_motor);
	while (fabs(get_motor_position_counter(left_motor)) < tick_distance){
		motor (left_motor, (int)(speed*direction*l_motor_factor));
		motor (right_motor, (int)(speed*direction));
	}
	msleep(0);
}

/* Name     : driveUpTheRamp
Purpose     : takes the robot up the ramp with what may as well be jamaican voodoo. I need to go back and find out how this works.
*/
void driveUpTheRamp(){
  while(accel_y()>axisSensor){
      if (analog (left_light) > 4000){
          motor (left_motor, -50);
          motor (right_motor, -25);
          msleep(10);
          //printf("peach\tleft: %i",analog(left_light));
          //printf("accel_y: %i", accel_y);
          if(accel_y()<0)
              break;
      }
      else if (analog (right_light) > 4000){
          motor (left_motor, -25);
          motor (right_motor, -50);
          msleep(10);
          //printf("plum\tright: %i",analog(right_light));
          if(accel_y()<0)
              break;
      }
      else{
        motor(left_motor,-100*l_motor_factor);
        motor(right_motor,-100*r_motor_factor);
        msleep(10);
        }
      }
    }

/* Name     : turn
Purpose     : executes a turn acording to the parameters
Parameters  : int speed     - the speed (0-100) at which the robot will turn
              int time      - the time that the robot will turn in milliseconds. Thsi controlls how for the robot turns.
              int direction - the direction that the robot will turn. Pass in either left OR right.

*/
void turn(int speed, int time, int direction){
  motor (left_motor, -direction*speed*l_motor_factor);
  motor (right_motor, direction*speed*r_motor_factor);
  msleep(time);
  ao();


}

/* Name     : twoStepTurn
Purpose     : executes a  90 degree turn in two parts
Parameters  : int speed         - the speed (0-100) at which the robot will turn
              int time          - the time that the robot will turn in milliseconds. Thsi controlls how for the robot turns.
              int turnDirection - the direction that the robot will turn. Pass in either left OR right.
              int driveDirection- the direction that the robot will drive during the turn.
*/
void twoStepTurn(int speed, int time, int turnDirection, int driveDirection){
  turn(speed, time/2, turnDirection);
  drive(75, 5, driveDirection);
  turn(75, time/2, turnDirection);
  drive(speed, 5, driveDirection);
}

/* Name     : moveServo
Purpose     : sets the a specific servo to a specific position.
Parameters  : int port      - the port of the servo that should be moved
              int position  - the position to which the servo should be moved(0-2047)
              int speed     - the speed (0-100) at which the robot will turn
*/
void moveServo(int port, int position, int speed){
    int current_pos = get_servo_position(port);
    if(position < current_pos) {
        while(current_pos > position) {
            set_servo_position(port,current_pos);
            current_pos -= 10;
            msleep(speed);
        }
    }

    if(position > current_pos) {
        while(current_pos < position) {
            set_servo_position(port,current_pos);
            current_pos += 10;
            msleep(speed);
        }
    }
}

/* Name     : extendWheels
Purpose     : extends the support wheels.
Parameters  : int wheelPosition - the position to which the wheels are moved(0-2047). 0 = lowest; 1000 = driving up ramp; 1630 = highest;

*/
void moveWheels(int wheelPosition){
  moveServo(raise_robot, wheelPosition, 50);
}
