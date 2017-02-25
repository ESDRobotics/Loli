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

void drive(int speed, int distance, int direction);
//code
int main()
{
    set_servo_position(lift_arm, 1020);
    set_servo_position(raise_robot, 695);
    enable_servos();

    set_servo_position(lift_arm, 720);
    msleep(2000);
    while(get_servo_position(raise_robot)<695){
        set_servo_position(raise_robot, get_servo_position(raise_robot)+10);
        msleep(1000);
    }
    printf("apple");
    set_servo_position(raise_robot, 695);
    msleep(1000);
    printf("%i\n",accel_y());
    //drive(100,25,1);

    printf("banana");
    printf("%i\n",accel_y());
    msleep(100);
    while(get_servo_position(raise_robot)<160){
        set_servo_position(raise_robot, get_servo_position(raise_robot)+10);
        msleep(1000);
    }
    set_servo_position(raise_robot,160);
    //drive(100,20,1);
    printf("pear");
    ao();
    printf("%i\n",accel_y());
    //drive(50,35,1);
    ao();
    printf("%i\n",accel_y());
    //I think this is where we are driving up the ramp

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
    ao();
    printf("%ioff the ramp",accel_y());

    set_servo_position(lift_arm, 1430);
    while(get_servo_position(raise_robot)<900){
        set_servo_position(raise_robot, get_servo_position(raise_robot)+20);
        msleep(100);
    }
    set_servo_position(raise_robot,900);
    //drive(50,10,1);
    ao();
    set_servo_position(lift_arm,900);
    set_servo_position(raise_robot,160);
    msleep(3000);
    int count=0;
    while(count<20){
        motor(left_motor,50);
        motor(right_motor,50);
        msleep(100);
        while (analog (left_light) > 4010){
            motor (left_motor, 25);
            motor (right_motor, 50);
            msleep(25);
        }
        while (analog (right_light) > 4010){
            motor (left_motor, 50);
            motor (right_motor, 25);
            msleep(25);
        }
        count++;
        printf("blueberry");
    }
    //drive(75,60,1);
    ao();
    //drive(75,60,-1);
    ao();
    set_servo_position(lift_arm,850);
    motor(lift_claw,50);
    msleep(1000);
    ao();
    msleep(1000);
    set_servo_position(open_claw, 1000);
    //drive(75,60,1);
    ao();
    set_servo_position(open_claw, 2000);
    motor(lift_claw,50);
    msleep(1000);
    ao();
    disable_servos();
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

void moveServo( into port, int position){

}
