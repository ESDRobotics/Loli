#include <kipr/botball.h>
//variable definitions
#define left_motor 0
#define right_motor 1
#define lift_arm 2//farthest is 1200, closest is 170
#define raise_robot 0//1630 is highest, 140 is lowest
#define lift_claw 3//-100 is highest, 2360 is lowest
#define open_claw 1//2000 is closed, 900 is open
#define  left_light 1
#define right_light 0
#define ticks 955.8
#define ticks_per_centimeter ticks/18
#define l_motor_factor .60
#define r_motor_factor 1
#define forward 1
#define backward -1
#define right -1
#define left 1

void driveUpTheRamp();
void twoStepTurn(int turnDirection, int driveDirection);
void turn(int speed, int time, int direction);
void drive(int speed, int distance, int direction);




int main()
{


    /*
    printf("%i\n",accel_y());
    //drive(50,35,1);
    ao();
    printf("%i\n",accel_y());
    //I think this is where we are driving up the ramp
    drive(100, 20, forward);
    driveUpTheRamp();
    drive(100, 20, forward);

    */
    //drive on to the ramp
    drive(75, 20, forward);
    //call the ramp method
    driveUpTheRamp();
    twoStepTurn(right, forward);
    // initial two stage turn procedure



}
//method definitions
void drive(int speed, int distance, int direction){
    int tick_distance = ticks_per_centimeter * distance;
	clear_motor_position_counter(left_motor);
	while (fabs(get_motor_position_counter(left_motor)) < tick_distance){
		motor (left_motor, (int)(speed*direction*l_motor_factor));
		motor (right_motor, (int)(speed*direction));
	}
	msleep(0);
}


/*
Purpose : takes the robot up the ramp with what may as well be jamaican voodoo. I need to go back and find out how this works.
*/
void driveUpTheRamp(){
  while(accel_y()<110){
      if (analog (left_light) > 4000){
          motor (left_motor, 25);
          motor (right_motor, 50);
          msleep(10);
          printf("peach\tleft: %i",analog(left_light));
          printf("accel_y: %i", accel_y);
          if(accel_y()>0)
              break;
      }
      else if (analog (right_light) > 4000){
          motor (left_motor, 50);
          motor (right_motor, 25);
          msleep(10);
          printf("plum\tright: %i",analog(right_light));
          if(accel_y()>0)
              break;
      }
      else{
          motor(left_motor,60);
        motor(right_motor,100);
        msleep(10);
          printf("strawberry");
          printf("\taccel_y: %i", accel_y);

      }
}

}


/*
Purpose : executes a turn acording to the parameters
Parameters :  speed     - the speed (0-100) at which the robot will turn
              time      - the time that the robot will turn in milliseconds. Thsi controlls how for the robot turns.
              direction - the direction that the robot will turn. Pass in either left OR right.

*/

void turn(int speed, int time, int direction){
  motor (left_motor, -direction*speed*l_motor_factor);
  motor (right_motor, direction*speed*r_motor_factor);
  msleep(time);
  ao();


}

/*
Purpose : executes a  90 degree turn in two parts
Parameters :  speed         - the speed (0-100) at which the robot will turn
              time          - the time that the robot will turn in milliseconds. Thsi controlls how for the robot turns.
              turnDirection - the direction that the robot will turn. Pass in either left OR right.
              driveDirection- the direction that the robot will drive during the turn.
*/
void twoStepTurn(int speed, int time; int turnDirection, int driveDirection){
  turn(speed, time/2, turnDirection);
  drive(75, 5, driveDirection);
  turn(75, time/2, turnDirection);
  drive(speed, 5, driveDirection);
}

/* to be completed later

void moveServo( into port, int position){

}
*/
